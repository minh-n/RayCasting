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

void Scene::afficher() const{
	for(unsigned int i = 0; i < nosObjets.size()-1; i++)
	{
		nosObjets[i]->afficher();
	}
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

void Scene::rayonTouche()
{
	Position* pos = NULL;
	Position* temp = NULL;

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position posCam = camera.getPos();
			Position posPixel = ecran.getPixels()[i][j].getPosition();

//			cout << "Pos pixel: " << posPixel.getX() << ";" << posPixel.getY() << ";" << posPixel.getZ() << ";" << endl;

			for(vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
 				pos = (*it)->intersection(posCam, posPixel);

				if(pos != NULL)
				{
					if(temp != NULL)
					{
						double d1 = sqrt(pow(camera.getPos().getX() - pos->getX(), 2)
											+ pow(camera.getPos().getY() - pos->getY(), 2)
											+ pow(camera.getPos().getZ() - pos->getZ(), 2));

						double d2 = sqrt(pow(camera.getPos().getX() - temp->getX(), 2)
											+ pow(camera.getPos().getY() - temp->getY(), 2)
											+ pow(camera.getPos().getZ() - temp->getZ(), 2));

						if(d1 < d2)
						{
							Couleur c = (*it)->getCouleur();
							ecran.pixels[i][j].setCouleur(c);
						}

					}
					else
					{
						Couleur c = (*it)->getCouleur();
						ecran.pixels[i][j].setCouleur(c);
					}

					temp = pos;
				}
			}

			pos = NULL;
			temp = NULL;
	    }
	}

	delete(pos);
	delete(temp);
}



