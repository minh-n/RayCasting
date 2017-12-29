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

void Scene::afficher() {
	for(std::vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
	{
		(*it)->afficher();
	}
}

void Scene::creationFichier()
	{
		 std::cout << "Creation du fichier..." << std::endl;
		 std::ofstream fichier;

		 fichier.open("sortie2.ppm", std::ios::out | std::ios::trunc);

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
	Objet* objetRencontre = NULL;
	Position3D* pos = NULL;
	Position3D* tmp = NULL;

	Couleur couleurRayon = Couleur();

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = camera.getPos();
			Position3D posPixel = ecran.getPixels()[i][j].getPosition();

			//std::cout << "Pixel[" << i << "][" << j << "]\n" << std::endl;

			for(std::vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
				pos = (*it)->intersection(posCam, posPixel);

				if(pos != NULL)
				{
					if(tmp != NULL)
					{
						double normeActuel = Position3D::norme(posCam, *pos);
						double normePrecedente = Position3D::norme(posCam, *tmp);

						if(normeActuel < normePrecedente)
						{
							delete tmp;
							tmp = new Position3D(*pos);
							objetRencontre = *it;
						}
					}
					else
					{
						tmp = new Position3D(*pos);
						objetRencontre = *it;
					}

					delete pos;
				}
			}

			if(objetRencontre != NULL)
			{
				std::cout << "########### Debut iteration ###########" << std::endl;
				Couleur c = recursive(objetRencontre, posCam, *tmp, couleurRayon, 0);
				ecran.pixels[i][j].setCouleur(c);

				delete tmp;

				objetRencontre = NULL;
				pos = NULL;
				tmp = NULL;
			}
		}
	}
}

void Scene::setupEcranSansReflexion()
{
	Objet* objetRencontre = NULL;
	Position3D* pos = NULL;
	Position3D* tmp = NULL;

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = this->camera.getPos();
			Position3D posPixel = this->ecran.getPixels()[i][j].getPosition();

//			std::cout << "Pixel[" << i << "][" << j << "]\n" << std::endl;

			for(std::vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
 				pos = (*it)->intersection(posCam, posPixel);

				if(pos != NULL)
				{
//					std::cout << "Objet rencontre:" << std::endl;
//					(*it)->afficher();

					if(tmp != NULL)
					{
						double normeActuel = Position3D::norme(posCam, *pos);
						double normePrecedente = Position3D::norme(posCam, *tmp);

						if(normeActuel < normePrecedente)
						{
							delete tmp;
							tmp = new Position3D(*pos);
							objetRencontre = *it;
						}
					}
					else
					{
						tmp = new Position3D(*pos);
						objetRencontre = *it;
					}

					delete pos;
				}
			}

//			std::cout << "Sortie de la boucle" << std::endl;

			//sans reflexion
			if(objetRencontre != NULL)
			{
				if(eclairageDirect(*tmp, objetRencontre))
				{
					double cosAlpha = (objetRencontre->calculCosinusAlpha(*tmp, this->source.getPos()));
					Couleur c = Couleur::couleurSansReflexion(cosAlpha, objetRencontre->getCouleur(), this->source.getCouleur());
					ecran.pixels[i][j].setCouleur(c);
				}
				else
				{
					Couleur c = Couleur(0, 0, 0);
					ecran.pixels[i][j].setCouleur(c);
				}

				delete tmp;

				objetRencontre = NULL;
				pos = NULL;
				tmp = NULL;
			}
	    }
	}
}



bool Scene::eclairageDirect(const Position3D& posIncidence, const Objet* objetSource)
{
	bool direct = true;
	Position3D posSource = this->source.getPos();
	Position3D* collision = NULL;

//	double distanceLumiere = Position3D::norme(posIncidence, posSource);
	double cosAlpha = objetSource->calculCosinusAlpha(posIncidence, this->source.getPos());

	if(cosAlpha > 0)
	{
		for(std::vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
		{
			collision = (*it)->intersection(posIncidence, posSource);

			if(collision != NULL && objetSource != *it)
			{
//				double distanceCollision = Position3D::norme(posIncidence, *collision);
//
//				if(distanceCollision < distanceLumiere)
				{
					direct = false;
					break;
				}

				delete collision;
			}
		}
	}

	return direct;
}

Couleur Scene::eclairageAvecReflexion(const Objet* objet, const Couleur& rayonSpeculaire, const Position3D& posIncidence)
{
	Couleur couleurSource = this->source.getCouleur();
	Couleur couleurSurface = objet->getCouleur();
	Couleur pixel;

	double r = objet->getReflection();

	if(eclairageDirect(posIncidence, objet))
	{
		double cosinusAlpha = (objet->calculCosinusAlpha(posIncidence, this->source.getPos()));

		pixel = Couleur(((int) ((1 - r) * cosinusAlpha * ((couleurSource.getR()*couleurSurface.getR())/255) + r*rayonSpeculaire.getR())),
				((int) ((1 - r) * cosinusAlpha * ((couleurSource.getG()*couleurSurface.getG())/255) + r*rayonSpeculaire.getG())),
				((int) ((1 - r) * cosinusAlpha * ((couleurSource.getB()*couleurSurface.getB())/255) + r*rayonSpeculaire.getB())));
	}
	else
	{
		pixel = Couleur((int) r*rayonSpeculaire.getR(), (int) r*rayonSpeculaire.getG(), (int) r*rayonSpeculaire.getB());
	}

	return pixel;
}


Couleur Scene::recursive(const Objet* objetSource, const Position3D& sourceRayon, const Position3D& surface, Couleur couleurRayon, unsigned int iteration)
{
	Objet* objetRencontre = NULL;
	Position3D* pos = NULL;
	Position3D* tmp = NULL;

	Couleur temp;

	if(iteration < 4)
	{
		Position3D reflechi = objetSource->calculRayonReflechi(surface, sourceRayon);

		for(std::vector<Objet*>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
		{
			pos = (*it)->intersection(surface, reflechi);

			if(pos != NULL && (objetSource != *it))
			{
				if(tmp != NULL)
				{
					double normeActuel = Position3D::norme(surface, *pos);
					double normePrecedente = Position3D::norme(surface, *tmp);

					if(normeActuel < normePrecedente)
					{
						delete tmp;
						tmp = new Position3D(*pos);
						objetRencontre = *it;
					}
				}
				else
				{
					tmp = new Position3D(*pos);
					objetRencontre = *it;
				}

				delete pos;
			}
		}

		if(objetRencontre != NULL)
		{
			std::cout << "objet source : " << std::endl;
			objetSource->afficher();

			std::cout << "objet intersection : " << std::endl;
			objetRencontre->afficher();

			iteration++;

			std::cout << "reflexion" << std::endl;
			couleurRayon = eclairageAvecReflexion(objetSource, recursive(objetRencontre, surface, *tmp, couleurRayon, iteration), surface);

			delete tmp;
		}
		else
		{
			std::cout << "Pas de reflexion" << std::endl;
			couleurRayon = eclairageAvecReflexion(objetSource, Couleur(0, 0, 0), surface);
		}
	}
	else
	{
		couleurRayon = eclairageAvecReflexion(objetSource, Couleur(0, 0, 0), surface);
	}

//	std::cout << "iteration : " << iteration << std::endl;
//	couleurRayon.afficherCouleur();
	return couleurRayon;
}
