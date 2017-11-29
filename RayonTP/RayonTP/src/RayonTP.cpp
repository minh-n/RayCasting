//============================================================================
// Name        : RayonTP.cpp
// Author      : Adrien & Minh
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Parser.h"
using namespace std;


//test
int main() {

	Parser *p = new Parser();

	int b = p->lecture();

	delete(p);

	cout << "lecuttrere" << b << endl; // prints !!!Hello World!!!

	return 0;
}
