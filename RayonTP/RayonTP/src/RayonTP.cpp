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
#include "Sphere.h"
#include "Vecteur.h"


using namespace std;

void testIntersection(){
	Ecran *ecran = new Ecran();
	Scene *scene = new Scene();
	Source *source = new Source();

	Parser *p = new Parser();

	p->lecture(source, ecran, scene);
	cout << "Lecture finie !" << endl;
	delete(p);

	cout << "\n\ntest affichage.\n" << endl;
	scene->afficher();

	cout << "Debut intersec.\n" << endl;
	scene->rayonTouche();

	scene->creationFichier();

	delete(ecran);
	delete(source);
	delete(scene);
}

int main() {

//	Ecran *ecran = new Ecran();
//	Scene *scene = new Scene();
//	Source *source = new Source();
//
//	Parser *p = new Parser();
//
//	p->lecture(source, ecran, scene);
//
//	cout << "Lecture finie !" << endl;
//
//	delete(p); //fin de la lecture du fichier.
//
//	cout << "\n\ntest affichage. Sphere 0 : \n" << endl;
//
//	scene->afficher();
//	scene->creationFichier();
//
//	delete(ecran);
//	delete(source);
//	delete(scene);

	testIntersection();

	return 0;
}

