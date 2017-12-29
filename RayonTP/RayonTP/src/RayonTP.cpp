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

	cout << "Debut setuptEcran.\n" << endl;
	scene->setupEcran();

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

//	/********** test calcul de position **********/
//	Position3D p = Position3D(1, 1, 1);
//	Position3D p2 = Position3D(2, 2, 2);
//
//	cout << "p:" << endl;
//	p.afficherPos();
//	cout << "p2:" << endl;
//	p2.afficherPos();
//
//	Position3D p3 = p2 - p;
//	cout << "p3:" << endl;
//	p3.afficherPos();
//
//	cout << "norme: " << Position3D::norme(p, p2) << endl;
//
//	Position3D vectUnitaire = Position3D::vectUnitaire(p, p2);
//	cout << "vect unitaire:" << endl;
//	vectUnitaire.afficherPos();


//	/********** test calcul de couleur **********/
//	Couleur c = Couleur(400, 256, 255);
//	Couleur c2 = Couleur(-1, -1, -1);
//	Couleur c3 = Couleur(10, 10, 10);
//
//	cout << "c:" << endl;
//	c.afficherCouleur();
//	cout << "c2:" << endl;
//	c2.afficherCouleur();
//
//	Couleur c4 = c + c3;
//	cout << "c4:" << endl;
//	c4.afficherCouleur();
//
//	Couleur c5 = c2 - c3;
//	cout << "c5:" << endl;
//	c5.afficherCouleur();

	return 0;
}

