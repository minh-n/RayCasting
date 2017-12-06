//============================================================================
// Name        : RayonTP.cpp
// Author      : Adrien & Minh
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Parser.h"
#include "Scene.h"
#include "Vecteur.h"

using namespace std;

int main() {



	Ecran *ecran = new Ecran();
	Scene *scene = new Scene();

	Sphere s1, s2, s3;
	Parser *p = new Parser();

	int b = p->lecture(*ecran, *scene);

	cout << "Lecture finie ! Resultat : " << b  << " (0 si pas de bug)"<< endl; // prints !!!Hello World!!!

	delete(p);










	return 0;
}
