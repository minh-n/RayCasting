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

	        for(int i = 0; i < this->getEcran().getResHorizontale(); i++)
	        {
      			for(int j = 0; j < this->getEcran().getResVerticale(); j++){

      				fichier << "10" << " 20" << " 100";
      				fichier << "\n";

            	}

	       	}
	     }
	     fichier.close();
	}





