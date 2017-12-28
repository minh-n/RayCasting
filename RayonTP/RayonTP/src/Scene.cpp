/*
 * Scene.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Scene.h"

/**
 * CAMERA
 */

Camera::Camera() {

}

Camera::Camera(Position3D p) {
	this->pos = p;
}

Camera::~Camera() {

}


/**
 * SOURCE
 */

Source::Source(){

}

Source::Source(Position3D p) : pos(p) {

}

Source::~Source() {

}


/**
 * SCENE
 */

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::afficher() const{
	for(unsigned int i = 0; i < nosObjets.size()-1; i++)
	{
		nosObjets[i]->afficher();
	}
}

void Scene::creationFichier()
	{
		 std::cout << "Creation du fichier..." << std::endl;
		 ofstream fichier;

		 fichier.open("sortie.ppm", std::ios::out | std::ios::trunc);

	     if(fichier)
	     {
	    	 std::cout << "Ecriture dans le fichier..." << std::endl;
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
//	Objet* tmp = NULL;
//	Position* pos = NULL;
//	Position* temp = NULL;
//	Couleur* c = new Couleur(0, 0, 0);
//
//	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
//	{
//		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
//		{
//			Position posCam = camera.getPos();
//			Position posPixel = ecran.getPixels()[i][j].getPosition();
//
////			cout << "Pos pixel: " << posPixel.getX() << ";" << posPixel.getY() << ";" << posPixel.getZ() << ";" << endl;
//
//			for(vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
//			{
// 				pos = (*it)->intersection(posCam, posPixel);
//
//				if(pos != NULL)
//				{
//					if(temp != NULL)
//					{
//						double d1 = sqrt(pow(camera.getPos().getX() - pos->getX(), 2)
//											+ pow(camera.getPos().getY() - pos->getY(), 2)
//											+ pow(camera.getPos().getZ() - pos->getZ(), 2));
//
//						double d2 = sqrt(pow(camera.getPos().getX() - temp->getX(), 2)
//											+ pow(camera.getPos().getY() - temp->getY(), 2)
//											+ pow(camera.getPos().getZ() - temp->getZ(), 2));
//
//						if(d1 < d2)
//						{
//							cout << "\nPixel[" << i << "][" << j << "] :" << endl;
//							tmp = *it;
//
//							temp = pos;
//						}
//
//					}
//					else
//					{
//						cout << "\nPixel[" << i << "][" << j << "] :" << endl;
//						tmp = *it;
//
//						temp = pos;
//					}
//				}
//			}
//
//			if(tmp != NULL)
//			{
//				c = recursive(tmp, posCam, *temp, c, 0);
//				ecran.pixels[i][j].setCouleur(*c);
//			}
//
//			tmp = NULL;
//			pos = NULL;
//			temp = NULL;
//	    }
//	}
//
//	delete c;
}

void Scene::setupEcranSansReflexion()
{
	Objet* tmp = NULL;
	Position3D* pos = NULL;
	Position3D* temp = NULL;

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = camera.getPos();
			Position3D posPixel = ecran.getPixels()[i][j].getPosition();

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
							tmp = *it;
							temp = pos;
						}

					}
					else
					{
						tmp = *it;
						temp = pos;
					}
				}
			}

			//sans reflexion
			if(tmp != NULL)
			{
				if(eclairageDirect(*temp, tmp))
				{
					double cos = abs(tmp->calculCos(*temp, source.getPos()));
					Couleur c = Couleur(cos*((tmp->getCouleur().getR())*source.getCouleur().getR()/255),
							cos*((tmp->getCouleur().getG())*source.getCouleur().getG()/255),
							cos*((tmp->getCouleur().getB())*source.getCouleur().getB()/255));
					ecran.pixels[i][j].setCouleur(c);
				}
				else
				{
					Couleur c = Couleur(0, 0, 0);
					ecran.pixels[i][j].setCouleur(c);
				}
			}

			tmp = NULL;
			pos = NULL;
			temp = NULL;
	    }
	}
}



bool Scene::eclairageDirect(const Position3D& pos, const Objet* objet)
{
	bool direct = true;
	Position3D posSource = source.getPos();
	Position3D* surface = NULL;

	double epsilon = 0.005;

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
				std::cout << "Intersection bloquant la source" << std::endl;
				surface->afficherPos();
				std::cout << "Objet :" << std::endl;
				(*it)->afficher();
				std::cout << "Position sans lumiere" << std::endl;
 				pos.afficherPos();
 				std::cout << "Objet :" << std::endl;
 				objet->afficher();
				direct = false;
			}
		}
	}

	return direct;
}

//Couleur* Scene::eclairageAvecReflexion(const Objet& objet, const Couleur& sourceSecondaire, const Position& pos)
//{
//	Couleur* c;
//
//	if(eclairageDirect(pos))
//	{
//		double cos = objet.calculCos(pos, source.getPos());
//		c = new Couleur((1-objet.getReflection())*cos*((objet.getCouleur().getR())*source.getCouleur().getR())/255 + objet.getReflection()*sourceSecondaire.getR(),
//				(1-objet.getReflection())*cos*((objet.getCouleur().getG())*source.getCouleur().getG())/255 + objet.getReflection()*sourceSecondaire.getG(),
//				(1-objet.getReflection())*cos*((objet.getCouleur().getB())*source.getCouleur().getB())/255 + objet.getReflection()*sourceSecondaire.getB());
//	}
//	else
//	{
//		c = new Couleur(objet.getReflection()*sourceSecondaire.getR(),
//				objet.getReflection()*sourceSecondaire.getG(),
//				objet.getReflection()*sourceSecondaire.getB());
//	}
//
//	return c;
//}
//
//
//Couleur* Scene::recursive(const Objet* objet, const Position& sourceRayon, const Position& surface, Couleur* c, int iteration)
//{
//	Objet* objetSource = NULL;
//	Couleur* tmp = NULL;
//	Position* incident = NULL;
//	Position* temp = NULL;
//
//	double epsilon = 0.05;
//
//	if(iteration < 3)
//	{
//		Position reflechi = objet->calculRayonReflechi(surface, sourceRayon);
//
//		for(vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
//		{
//			incident = (*it)->intersection(surface, reflechi);
//
//			if(incident != NULL)
//			{
//				if(temp != NULL)
//				{
//					double distance = sqrt(pow(surface.getX() - incident->getX(), 2)
//							+ pow(surface.getY() - incident->getY(), 2)
//							+ pow(surface.getZ() - incident->getZ(), 2));
//
//					if(distance > epsilon)
//					{
//						double d1 = sqrt(pow(camera.getPos().getX() - incident->getX(), 2)
//								+ pow(camera.getPos().getY() - incident->getY(), 2)
//								+ pow(camera.getPos().getZ() - incident->getZ(), 2));
//
//						double d2 = sqrt(pow(camera.getPos().getX() - temp->getX(), 2)
//								+ pow(camera.getPos().getY() - temp->getY(), 2)
//								+ pow(camera.getPos().getZ() - temp->getZ(), 2));
//
//						if(d1 < d2)
//						{
//							objetSource = *it;
//							temp = incident;
//						}
//					}
//				}
//				else
//				{
//					double distance = sqrt(pow(surface.getX() - incident->getX(), 2)
//							+ pow(surface.getY() - incident->getY(), 2)
//							+ pow(surface.getZ() - incident->getZ(), 2));
//
//					if(distance > epsilon)
//					{
//						objetSource = *it;
//						temp = incident;
//					}
//				}
//			}
//		}
//
//		if(objetSource != NULL)
//		{
//			iteration++;
//
//			tmp = eclairageAvecReflexion(*objet, *recursive(objetSource, surface, *temp, c, iteration), surface);
//			c->setCouleur(*tmp);
//
//		}
//		else
//		{
//			if(eclairageDirect(surface))
//			{
//				double cos = objet->calculCos(surface, source.getPos());
//				Couleur cSource = Couleur(cos*((objet->getCouleur().getR())*source.getCouleur().getR())/255,
//						cos*((objet->getCouleur().getG())*source.getCouleur().getG())/255,
//						cos*((objet->getCouleur().getB())*source.getCouleur().getB())/255);
//				c->setCouleur(cSource);
//			}
//			else
//			{
//				c->setB(0);
//				c->setG(0);
//				c->setR(0);
//			}
//		}
//	}
//	else
//	{
//		if(eclairageDirect(surface))
//		{
//
//			double cos = objet->calculCos(surface, source.getPos());
//			Couleur cSource = Couleur(cos*((objet->getCouleur().getR())*source.getCouleur().getR())/255,
//					cos*((objet->getCouleur().getG())*source.getCouleur().getG())/255,
//					cos*((objet->getCouleur().getB())*source.getCouleur().getB())/255);
//			c->setCouleur(cSource);
//		}
//		else
//		{
//			c->setB(0);
//			c->setG(0);
//			c->setR(0);
//		}
//	}
//
//	c->afficherCouleur();
//
//	return c;
//}
