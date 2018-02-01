#pragma once
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class Token {
	string name;
	float value;
	int id;
public:
	Token(string s, float f, int i) :name(s), value(f), id(i) {}
	float getValue() { return value; }
	string getName() { return name; }
	int getId() { return id; }
};
class Port {
	Token *token;
	bool Ready = false;
public:
	Port() {}
	bool isReady() {
		return Ready;
	}
	void beReady() { Ready = true; }
	Token* getToken() { return token; }
	void setToken(Token *t) { token = t; }
};
class Operation {
protected:
	vector <Port*> inputPorts;
	vector <Port*> outputPorts;
	int delay;
	int id;
public:
	Operation(int t,int id) :delay(t),id(id){}
	int getId() { return id; }
	virtual void execute() = 0;
	bool isReady() {
		bool ready = true;
		for (unsigned int i = 0; i < inputPorts.size(); i++)
			if (!(inputPorts[i]->isReady())) ready = false;
		return ready;
	}
};

class add :public Operation {
public:
	add(int t, Port* p1, Port* p2) :Operation(t,1001) {            //           1001 ID OD ADD
		inputPorts.push_back(p1);
		inputPorts.push_back(p2);
	}
	void execute() {
		if (!this->isReady()) return;      // ovde dodaj exception!!!
		else {
			Token* t = new Token(inputPorts[0]->getToken()->getName() + "+" + inputPorts[1]->getToken()->getName(), inputPorts[0]->getToken()->getValue() + inputPorts[1]->getToken()->getValue(), this->getId());
			Port* p = new Port();
			p->setToken(t);
			p->beReady();
			outputPorts.push_back(p);
		}
	}
	};
class multiply :public Operation {
public:
	multiply(int t, Port* p1, Port* p2) :Operation(t, 1002) {      //           1002 ID OD	MULTIPLY
		inputPorts.push_back(p1);
		inputPorts.push_back(p2);
	}
	void execute() {
		if (!this->isReady()) return;      // ovde dodaj exception!!!
		else {
			Token* t = new Token(inputPorts[0]->getToken()->getName() + "*" + inputPorts[1]->getToken()->getName(), inputPorts[0]->getToken()->getValue() * inputPorts[1]->getToken()->getValue(), this->getId());
			Port* p = new Port();
			p->setToken(t);
			p->beReady();
			outputPorts.push_back(p);
		}
	}
};

class power :public Operation {
public:
	power(int t, Port* p1, Port* p2) :Operation(t, 1003) {         //           1003 ID OD	POWER
		inputPorts.push_back(p1);
		inputPorts.push_back(p2);
	}
	void execute() {
		if (!this->isReady()) return;      // ovde dodaj exception!!!
		else {
			Token* t = new Token(inputPorts[0]->getToken()->getName() + "^" + inputPorts[1]->getToken()->getName(), pow(inputPorts[0]->getToken()->getValue(), inputPorts[1]->getToken()->getValue()), this->getId());
			Port* p = new Port();
			p->setToken(t);
			p->beReady();
			outputPorts.push_back(p);
		}
	}
};

