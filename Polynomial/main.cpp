//Monika Wielgus
#include "Z2.h"
#include "Polynomial.h"
#include "Z2.cpp"
#include "Polynomial.cpp"
#include <iostream>
#include <sstream>

using namespace std;
int main(){
	Z2 x(3);
	Z2 y(2);
	Z2 z(2);
	Z2 array1[]={x,y}; //1,1,0
	Z2 array2[]={x}; //0,1
	Polynomial a(1,array1);
	Polynomial b(1,array1);

	cout << (a+b).toString("x") << endl;
	cout << a.toString("x") << endl;
	cout << a.toString("x")<< endl;
	Polynomial h;
	cin >> h;
	cout << h << endl;
	cout << h.toString("x") << endl;
}
