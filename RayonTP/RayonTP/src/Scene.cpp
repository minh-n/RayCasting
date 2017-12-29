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
	for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
	{
		(*it)->afficher();
	}
}

void Scene::creationFichier(const std::string& nomFichier)
{
	std::string ppm = nomFichier + ".ppm";

	std::cout << "Creation du fichier..." << std::endl;
	std::ofstream fichier;

	fichier.open(ppm, std::ios::out | std::ios::trunc);

	if(fichier)
	{
		std::cout << "Ecriture dans le fichier..." << std::endl;
		fichier << "P3\n" << this->getEcran().getResHorizontale() << " "
				<< this->getEcran().getResVerticale() << "\n255\n";

		std::vector<std::vector<Pixel>> pix;
		pix = this->getEcran().getPixels();

		for(int i = 0; i < this->getEcran().getResVerticale(); i++)
		{
			for(int j = 0; j < this->getEcran().getResHorizontale(); j++){

				fichier << pix[j][i].getCouleur().getR() << " "
						<< pix[j][i].getCouleur().getG() << " "
						<< pix[j][i].getCouleur().getB();

				fichier << "\n";
			}
		}
	}
	fichier.close();
}

void Scene::setupEcran()
{
	std::shared_ptr<Objet> objetRencontre = nullptr;
	std::shared_ptr<Position3D> pos = nullptr;
	std::shared_ptr<Position3D> tmp = nullptr;

	Couleur couleurRayon = Couleur();

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = camera.getPos();
			Position3D posPixel = ecran.getPixels()[i][j].getPosition();

			//std::cout << "Pixel[" << i << "][" << j << "]\n" << std::endl;

			for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
				pos = (*it)->intersection(posCam, posPixel);

				if(pos != nullptr)
				{
					if(tmp != nullptr)
					{
						double normeActuel = Position3D::norme(posCam, *pos);
						double normePrecedente = Position3D::norme(posCam, *tmp);

						if(normeActuel < normePrecedente)
						{
							tmp = pos;
							objetRencontre = *it;
						}
					}
					else
					{
						tmp = pos;
						objetRencontre = *it;
					}
				}
			}

			if(objetRencontre != nullptr)
			{
//				std::cout << "########### Debut iteration ###########" << std::endl;
				Couleur c = recursive(objetRencontre, posCam, *tmp, couleurRayon, 0);
				ecran.pixels[i][j].setCouleur(c);

				objetRencontre = nullptr;
				pos = nullptr;
				tmp = nullptr;
			}
		}
	}
}

void Scene::setupEcranSansReflexion()
{
	std::shared_ptr<Objet> objetRencontre = nullptr;
	std::shared_ptr<Position3D> pos = nullptr;
	std::shared_ptr<Position3D> tmp = nullptr;

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = this->camera.getPos();
			Position3D posPixel = this->ecran.getPixels()[i][j].getPosition();

//			std::cout << "Pixel[" << i << "][" << j << "]\n" << std::endl;

			for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
 				pos = (*it)->intersection(posCam, posPixel);

				if(pos != nullptr)
				{
//					std::cout << "Objet rencontre:" << std::endl;
//					(*it)->afficher();

					if(tmp != nullptr)
					{
						double normeActuel = Position3D::norme(posCam, *pos);
						double normePrecedente = Position3D::norme(posCam, *tmp);

						if(normeActuel < normePrecedente)
						{
							tmp = pos;
							objetRencontre = *it;
						}
					}
					else
					{
						tmp = pos;
						objetRencontre = *it;
					}
				}
			}

//			std::cout << "Sortie de la boucle" << std::endl;

			//sans reflexion
			if(objetRencontre != nullptr)
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

				objetRencontre = nullptr;
				pos = nullptr;
				tmp = nullptr;
			}
	    }
	}
}

bool Scene::eclairageDirect(const Position3D& posIncidence, const std::shared_ptr<Objet> objetSource)
{
	bool direct = true;
	Position3D posSource = this->source.getPos();
	std::shared_ptr<Position3D> collision = nullptr;

	double cosAlpha = objetSource->calculCosinusAlpha(posIncidence, this->source.getPos());

	if(cosAlpha >= 0)
	{
		for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
		{
			collision = (*it)->intersection(posIncidence, posSource);

			if(collision != nullptr && objetSource != *it)
			{
				{
					direct = false;
					break;
				}
			}
		}
	}
	else
	{
		direct = false;
	}

	return direct;
}

Couleur Scene::eclairageAvecReflexion(const std::shared_ptr<Objet> objet, const Couleur& rayonSpeculaire, const Position3D& posIncidence)
{
	Couleur couleurSource = this->source.getCouleur();
	Couleur couleurSurface = objet->getCouleur();
	Couleur pixel;

	double r = objet->getReflection();

//	std::cout << "rayon spec : " << std::endl;
//	rayonSpeculaire.afficherCouleur();

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


Couleur Scene::recursive(const std::shared_ptr<Objet> objetSource, const Position3D& sourceRayon, const Position3D& surface, Couleur couleurRayon, unsigned int iteration)
{
	std::shared_ptr<Objet> objetRencontre = nullptr;
	std::shared_ptr<Position3D> pos = nullptr;
	std::shared_ptr<Position3D> tmp = nullptr;

	Couleur temp;

	if(iteration < 4)
	{
		Position3D reflechi = objetSource->calculRayonReflechi(surface, sourceRayon);

		for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
		{
			pos = (*it)->intersection(surface, reflechi);

			if(pos != nullptr && (objetSource != *it))
			{
				if(tmp != nullptr)
				{
					double normeActuel = Position3D::norme(surface, *pos);
					double normePrecedente = Position3D::norme(surface, *tmp);

					if(normeActuel < normePrecedente)
					{
						tmp = pos;
						objetRencontre = *it;
					}
				}
				else
				{
					tmp = pos;
					objetRencontre = *it;
				}
			}
		}

		if(objetRencontre != nullptr)
		{
			couleurRayon = eclairageAvecReflexion(objetSource, recursive(objetRencontre, surface, *tmp, couleurRayon, iteration), surface);
		}
		else
		{
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
