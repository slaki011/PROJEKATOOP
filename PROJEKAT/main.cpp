#include"Compiler.h"
#include<iostream>
using namespace std;

int main() {
	string ime_fajla = "Program.txt";



	//string a = "z=2*x^3+x^5*y^3+5";
	//vector<Elem*> v1;
	//konvertuj(a, &v1);
	//cout << "Gotovo!";
	//Elem* root = stvori_stablo(&v1);
	//cout << "Gotovo2";
	//vector<Elem*> v2;
	//int b = prebrojOp(&v1);
	//level_order(root, &v2, b);
	//cout << "Gotovo3";
	//string rez = prevediUImf(root, b);
	compile(ime_fajla);
}