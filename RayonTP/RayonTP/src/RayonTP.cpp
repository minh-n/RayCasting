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


	Position posSource;
	Position posCam;
	int resolution = 400;


	Source s(posSource);
	Camera c(posCam);
	Ecran e(resolution);
	Scene scene(s, c, e);

	Sphere s1, s2, s3;
	Parser *p = new Parser();

	int b = p->lecture(c, e, scene, s1, s2, s3);

	cout << "Lecture finie ! Resultat : " << b  << " (0 si pas de bug)"<< endl; // prints !!!Hello World!!!

	delete(p);










	return 0;
}
