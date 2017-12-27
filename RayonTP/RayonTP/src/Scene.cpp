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

void Scene::setupEcran()
{
	Objet* tmp = NULL;
	Position* pos = NULL;
	Position* temp = NULL;
	Couleur* c = new Couleur(0, 0, 0);

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
							cout << "\nPixel[" << i << "][" << j << "] :" << endl;
							tmp = *it;
							c = recursive(tmp, posCam, *pos, c, 0);
							ecran.pixels[i][j].setCouleur(*c);

							temp = pos;
						}

					}
					else
					{
						cout << "\nPixel[" << i << "][" << j << "] :" << endl;
						tmp = *it;
						c = recursive(tmp, posCam, *pos, c, 0);
						ecran.pixels[i][j].setCouleur(*c);

						temp = pos;
					}
				}
			}

			pos = NULL;
			temp = NULL;
	    }
	}

	delete c;
}

void Scene::setupEcranSansReflexion()
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
							//sans reflexion
							if(eclairageDirect(*pos))
							{
								double cos = (*it)->calculCos(*pos, source.getPos());
								Couleur c = Couleur(cos*(((*it)->getCouleur().getR())*source.getCouleur().getR())/255,
										cos*(((*it)->getCouleur().getG())*source.getCouleur().getG())/255,
										cos*(((*it)->getCouleur().getB())*source.getCouleur().getB())/255);
								ecran.pixels[i][j].setCouleur(c);
							}
							else
							{
								Couleur c = Couleur(0, 0, 0);
								ecran.pixels[i][j].setCouleur(c);
							}

							temp = pos;
						}

					}
					else
					{

						//Sans reflexion
						if(eclairageDirect(*pos))
						{
							double cos = (*it)->calculCos(*pos, source.getPos());
							Couleur c = Couleur(cos*(((*it)->getCouleur().getR())*source.getCouleur().getR())/255,
									cos*(((*it)->getCouleur().getG())*source.getCouleur().getG())/255,
									cos*(((*it)->getCouleur().getB())*source.getCouleur().getB())/255);
							ecran.pixels[i][j].setCouleur(c);
						}
						else
						{
							Couleur c = Couleur(0, 0, 0);
							ecran.pixels[i][j].setCouleur(c);
						}

						temp = pos;
					}
				}
			}

			pos = NULL;
			temp = NULL;
	    }
	}
}



bool Scene::eclairageDirect(const Position& pos)
{
	bool direct = true;
	double epsilon = 0.005;
	Position posSource = source.getPos();

	Position* surface = NULL;

	for(vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
	{
		surface = (*it)->intersection(pos, posSource);

		if(surface != NULL)
		{
			double distance = sqrt(pow(surface->getX() - pos.getX(), 2)
					+ pow(surface->getY() - pos.getY(), 2)
					+ pow(surface->getZ() - pos.getZ(), 2));

			if(distance > epsilon)
			{
				direct = false;
			}
		}
	}

	return direct;
}

Couleur* Scene::eclairageAvecReflexion(const Objet& objet, const Objet& sourceSecondaire, const Position& pos)
{
	Couleur* c;

	if(eclairageDirect(pos))
	{
		double cos = objet.calculCos(pos, source.getPos());
		c = new Couleur((1-objet.getReflection())*cos*((objet.getCouleur().getR())*source.getCouleur().getR())/255 + objet.getReflection()*sourceSecondaire.getCouleur().getR(),
				(1-objet.getReflection())*cos*((objet.getCouleur().getG())*source.getCouleur().getG())/255 + objet.getReflection()*sourceSecondaire.getCouleur().getG(),
				(1-objet.getReflection())*cos*((objet.getCouleur().getB())*source.getCouleur().getB())/255 + objet.getReflection()*sourceSecondaire.getCouleur().getB());
	}
	else
	{
		c = new Couleur(objet.getReflection()*sourceSecondaire.getCouleur().getR(),
				objet.getReflection()*sourceSecondaire.getCouleur().getG(),
				objet.getReflection()*sourceSecondaire.getCouleur().getB());
	}

	return c;
}


Couleur* Scene::recursive(const Objet* objet, const Position& sourceRayon, const Position& surface, Couleur* c, int iteration)
{
	Objet* objetSource = NULL;
	Couleur* tmp = NULL;
	Position* incident = NULL;
	Position* temp = NULL;

	double epsilon = 0.05;

	if(iteration < 3)
	{
		Position reflechi = objet->calculRayonReflechi(surface, sourceRayon);

		for(vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
		{
			incident = (*it)->intersection(surface, reflechi);

			if(incident != NULL)
			{
				if(temp != NULL)
				{
					double distance = sqrt(pow(surface.getX() - incident->getX(), 2)
							+ pow(surface.getY() - incident->getY(), 2)
							+ pow(surface.getZ() - incident->getZ(), 2));

					if(distance > epsilon)
					{
						double d1 = sqrt(pow(camera.getPos().getX() - incident->getX(), 2)
								+ pow(camera.getPos().getY() - incident->getY(), 2)
								+ pow(camera.getPos().getZ() - incident->getZ(), 2));

						double d2 = sqrt(pow(camera.getPos().getX() - temp->getX(), 2)
								+ pow(camera.getPos().getY() - temp->getY(), 2)
								+ pow(camera.getPos().getZ() - temp->getZ(), 2));

						if(d1 < d2)
						{
							objetSource = *it;
							temp = incident;
						}
					}
				}
				else
				{
					double distance = sqrt(pow(surface.getX() - incident->getX(), 2)
							+ pow(surface.getY() - incident->getY(), 2)
							+ pow(surface.getZ() - incident->getZ(), 2));

					if(distance > epsilon)
					{
						objetSource = *it;
						temp = incident;
					}
				}
			}
		}

		if(objetSource != NULL)
		{
			iteration++;
			tmp = eclairageAvecReflexion(*objet, *objetSource, surface);
			c->setCouleur(*recursive(objetSource, surface, *temp, c, iteration) + *tmp);
		}
		else
		{
			if(eclairageDirect(*temp))
			{
				double cos = objet->calculCos(surface, source.getPos());
				Couleur cSource = Couleur(cos*((objet->getCouleur().getR())*source.getCouleur().getR())/255,
						cos*((objet->getCouleur().getG())*source.getCouleur().getG())/255,
						cos*((objet->getCouleur().getB())*source.getCouleur().getB())/255);
				c->setCouleur(cSource);
			}
			else
			{
				c->setB(0);
				c->setG(0);
				c->setR(0);
			}
		}
	}

	c->afficherCouleur();

	return c;
}
