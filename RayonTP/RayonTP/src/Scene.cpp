/*
 * Scene.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Scene.h"
#include <iostream>


using namespace std;




/**
 * CAMERA
 */


Camera::Camera() {
	// TODO Auto-generated constructor stub
}

Camera::Camera(Position p) {
	// TODO Auto-generated constructor stub
	pos = p;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}













/**
 * SOURCE
 */

Source::Source(){

}
Source::Source(Position p) : pos(p) {

}

Source::~Source() {
	// TODO Auto-generated destructor stub
}











/**
 * SCENE
 */

Scene::Scene() {
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::creationFichier()
	{
		 cout << "Creation du fichier..." << endl;
		 ofstream fichier;

		 fichier.open("sortie.ppm", std::ios::out | std::ios::trunc);

	     if(fichier)
	     {
	        cout << "Ecriture dans le fichier..." << endl;
	        fichier << "P3\n" << this->getEcran().getResHorizontale() << " "
	        		<< this->getEcran().getResVerticale() << "\n255\n";

			std::vector<std::vector<Pixel>> pix;
			pix = this->getEcran().getPixels();

			//inverser Verticale et horizontale peut etre ?

	        for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	        {
      			for(int j = 0; j < this->getEcran().getResHorizontale(); j++){

      				fichier << pix[i][j].getCouleur().getR() << " "
      				<< pix[i][j].getCouleur().getG() << " "
      				<< pix[i][j].getCouleur().getB();

      				fichier << "\n";

            	}

	       	}
	     }
	     fichier.close();
	}

void Scene::rayonTouche(Ecran* e)
{

	std::vector<std::vector<Pixel>> pix;
	pix = e->getPixels();
	cout << "###########\nEcran e PIXEL 1 POSITION : " << endl;
	pix[1][2].getPosition().afficherPos();


	cout << "PIXEL 2 COULEUR 2 : " << endl;
		pix[300][100].getCouleur().afficherCouleur();

	cout << "\n\n\n" << endl;

}



