#pragma once
#include"Operation.h"
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include<fstream>
#include<sstream>

struct Elem {
	string vred;
	string ime;
	Elem* levo;
	Elem* desno;
	Elem(string vr,string ime = "", Elem* le = nullptr, Elem* de = nullptr) :vred(vr), levo(le), desno(de),ime(ime) {}
};
int prioritet(string p) {
	if (p == "^")
		return 4;
	if (p == "*")
		return 3;
	if (p == "+")
		return 2;
	if (p == "=")
		return 1;
}
bool isOperation(string a) {
	if (a == "+" || a == "*" || a == "^" || a == "=")
		return true;
	else
		return false;
}

void konvertuj(string a, vector<Elem*>* v1) {
	char* niz = new char();
	string* bafer = new string();
	vector<Elem*> v2;
	for (int i = 0; i < a.length(); i++) {
		string d;
		d = a[i];
		if (!isOperation(d)) {
			Elem* novi = new Elem(d);
			v1->push_back(novi);
		}
		else
		{
			if (isOperation(d)) {
				if (v2.size() == 0) {
					Elem* novi = new Elem(d);
					v2.push_back(novi);
				}
				else {
					while ((prioritet(v2.back()->vred) >= prioritet(d)) && v2.size() != 0) {
						v1->push_back(v2.back());
						v2.pop_back();
						if (v2.size() == 0)break;
					}
					Elem* novi = new Elem(d);
					v2.push_back(novi);
				}

			}
		}

	}
	while (v2.size() != 0) {
		v1->push_back(v2.back());
		v2.pop_back();
	}
}

Elem* stvori_stablo(vector<Elem*>* v) {
	Elem *root;
	stack<Elem*> stek;
	root = v->back();
	stek.push(root);
	for (int i = v->size() - 2; i >= 0; i--) {
		string g = stek.top()->vred;
		string h = v->at(i)->vred;
		while (stek.top()->desno && stek.top()->levo) stek.pop();
		if (isOperation(v->at(i)->vred) && (stek.top()->desno == nullptr)) {
			stek.top()->desno = v->at(i);
			stek.push(v->at(i));
		}
		else
			if (isOperation(v->at(i)->vred) && (stek.top()->levo == nullptr)) { 
				stek.top()->levo = v->at(i);
				stek.push(v->at(i));
			}
		if (!isOperation(v->at(i)->vred)) {
			if (stek.top()->desno == nullptr) {
				stek.top()->desno = v->at(i);
			}
			else {
				if (stek.top()->levo == nullptr) {
					stek.top()->levo = v->at(i);
				}
			}
		}
	}
	return root;
}


void level_order(Elem* root, vector<Elem*>* v,int broj) {
	queue<Elem*> que;
	Elem* tn = root;
	if (!root) return;
	Elem *trenutni, *levi, *desni;
	que.push(tn);
	que.push(NULL);
	int b = 1;
	while (!que.empty())
	{
		trenutni = que.front();
		que.pop();
		if (trenutni != NULL)
		{
			v->push_back(trenutni);
			if (isOperation(v->back()->vred))
				v->back()->ime = "t" + to_string(broj--);
			if (!isOperation(v->back()->vred))
				v->back()->ime = v->back()->vred;
			levi = trenutni->levo;
			desni = trenutni->desno;
			if (levi) que.push(levi);
			if (desni) que.push(desni);
		}
		else
		{
			if (!que.empty())que.push(NULL);
		}
	}
}

int prebrojOp(vector<Elem*>* v) {
	int broj = 0;
	for (int i = 0; i < v->size(); i++)
		if (isOperation(v->at(i)->vred))
			broj++;
	return broj;
}

string prevediUImf(Elem* root,int broj) {
	string rez;
	queue<Elem*> que;
	Elem* tn = root;
	if (!root) return "";
	Elem *trenutni, *levi, *desni;
	que.push(tn);
	que.push(NULL);
	int b = 1;
	while (!que.empty())
	{
		trenutni = que.front();
		que.pop();
		if (trenutni != NULL)
		{
			//v->push_back(trenutni);
			
			if (trenutni->levo != nullptr && trenutni->desno != nullptr) {
				if (trenutni->vred == "=") {
					rez = to_string(broj--) + ": " + trenutni->vred + " " + trenutni->levo->ime + " " + trenutni->desno->ime + "\n" + rez;
				}
				else {
					rez = to_string(broj--) + ": " + trenutni->vred + " " + trenutni->ime + " " + trenutni->levo->ime + " " + trenutni->desno->ime + "\n" + rez;
				}
			}
			levi = trenutni->levo;
			desni = trenutni->desno;
			if (levi) que.push(levi);
			if (desni) que.push(desni);
		}
		else
		{
			if (!que.empty())que.push(NULL);
		}
	}
	std::cout << rez;
	return rez;
}

void compile(string fajl) {
	string linija;
	ifstream dat(fajl, ios::in);
	fajl.pop_back();
	fajl.pop_back();
	fajl.pop_back();
	fajl += "imf";
	ofstream imf(fajl, ios::out);
	if (!dat) cout << "Greska pri otvaranju txt fajla!";
	if (!imf) cout<<"Greska pri pravljenju imf fajla!";
	int d = 0, g = 0;
	while (getline(dat, linija))
	{
		vector<Elem*> v1;
		konvertuj(linija, &v1);
		Elem* root = stvori_stablo(&v1);
		vector<Elem*> v2;
		int b = prebrojOp(&v1);
		level_order(root, &v2, b+d);
		string rez;
		rez = prevediUImf(root, b + g);
		g += b;
		if(b!=1)
		d += --b;
		imf << rez;
	}
	dat.close();
	imf.close();
}