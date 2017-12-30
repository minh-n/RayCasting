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

Camera::Camera(Position3D p) : pos(p){

}

Camera::~Camera() {

}


/**
 * SOURCE
 */

Source::Source(){

}

Source::Source(Position3D p, Couleur c) : pos(p), couleur(c){

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

	std::cout << "################ SCENE ################" << std::endl << std::endl;

	std::cout << "camera : ";
	camera.getPos().afficherPos();
	std::cout << std::endl;

	std::cout << "topLeftScreen : ";
	ecran.getTlc().afficherPos();

	std::cout << "topRightScreen : ";
	ecran.getTrc().afficherPos();

	std::cout << "bottomLeftScreen : ";
	ecran.getBlc().afficherPos();

	std::cout << "bottomRightScreen : ";
	ecran.getBrc().afficherPos();
	std::cout << std::endl;

	std::cout << "resolution horizontale : ";
	std::cout << ecran.getResHorizontale() << std::endl;

	std::cout << "resolution verticale : ";
	std::cout << ecran.getResVerticale() << std::endl << std::endl;

	std::cout << "background color : ";
	bgColor.afficherCouleur();
	std::cout << std::endl;

	std::cout << "Light position : ";
	source.getPos().afficherPos();

	std::cout << "Light couleur : ";
	source.getCouleur().afficherCouleur();

	std::cout << std::endl << "Objet dans la scene :" << std::endl << std::endl;

	int i = 1;

	for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
	{
		std::cout << "Objet " << i << std::endl;
		(*it)->afficher();
		std::cout << std::endl;
		i++;
	}

	std::cout << "################ FIN SCENE ################" << std::endl;
}

//cree un fichier .ppm correspond aux donnees de la scene
void Scene::creationFichier(const std::string& nomFichier)
{
	//initialisation du nom du fichier
	std::string ppm = "./output/" + nomFichier + ".ppm";

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

		std::cout << "...Fin de l'ecriture !" << std::endl;
		fichier.close();
		std::cout << "...Fichier {" << nomFichier << "} operationnel !" << std::endl;
	}
	else
	{
		std::cerr << "Impossible de creer le fichier de sortie !" << std::endl;
	}
}

//calcul la couleur avec reflexion de chaque pixel
void Scene::setupEcranAvecReflexion(const unsigned maxIteration)
{
	//Initialisation des pointeurs
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

			double distanceCamPixel = Position3D::norme(posCam, posPixel);

			for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
				pos = (*it)->intersection(posCam, posPixel);

				if(pos != nullptr)
				{
					double normeActuel = Position3D::norme(posCam, *pos);

					//verifie si le point d'intersection avec le nouveau objet est plus proche
					if(tmp != nullptr)
					{
						double normePrecedente = Position3D::norme(posCam, *tmp);

						//si oui et que le point est derriere l'ecran, on sauvegarde le point d'incidence et l'objet rencontre
						if(normeActuel < normePrecedente && normeActuel > distanceCamPixel)
						{
							tmp = pos;
							objetRencontre = *it;
						}
					}
					//verifie que le point soit derriere l'ecran par rapport a la camera
					else if(distanceCamPixel < normeActuel)
					{
						tmp = pos;
						objetRencontre = *it;
					}
				}
			}

			//Si un objet est rencontre, calcul la couleur du pixel actuel avec la reflexion
			if(objetRencontre != nullptr)
			{
				Couleur c = couleurAvecReflexionRecursive(objetRencontre, posCam, *tmp, couleurRayon, 0, maxIteration);
				ecran.pixels[i][j].setCouleur(c);

				//reinitialisation des pointeurs pour la prochaine iteration
				objetRencontre = nullptr;
				pos = nullptr;
				tmp = nullptr;
			}
		}
	}
}

//calcul la couleur sans reflexion de chaque pixel
void Scene::setupEcranSansReflexion()
{
	//Initialisation des pointeurs
	std::shared_ptr<Objet> objetRencontre = nullptr;
	std::shared_ptr<Position3D> pos = nullptr;
	std::shared_ptr<Position3D> tmp = nullptr;

	for(int i = 0; i < this->getEcran().getResVerticale(); i++)
	{
		for(int j = 0; j < this->getEcran().getResHorizontale(); j++)
		{
			Position3D posCam = this->camera.getPos();
			Position3D posPixel = this->ecran.getPixels()[i][j].getPosition();

			double distanceCamPixel = Position3D::norme(posCam, posPixel);

			for(std::vector<std::shared_ptr<Objet>>::iterator it=nosObjets.begin(); it!=nosObjets.end(); ++it)
			{
 				pos = (*it)->intersection(posCam, posPixel);

				if(pos != nullptr)
				{
					double normeActuel = Position3D::norme(posCam, *pos);

					//verifie si le point d'intersection avec le nouveau objet est plus proche
					if(tmp != nullptr)
					{
						double normePrecedente = Position3D::norme(posCam, *tmp);

						//si oui et que le point est derriere l'ecran, on sauvegarde le point d'incidence et l'objet rencontre
						if(normeActuel < normePrecedente && normeActuel > distanceCamPixel)
						{
							tmp = pos;
							objetRencontre = *it;
						}
					}
					//verifie que le point soit derriere l'ecran par rapport a la camera
					else if(distanceCamPixel < normeActuel)
					{
						tmp = pos;
						objetRencontre = *it;
					}
				}
			}

			////Si un objet est rencontre, calcul la couleur du pixel actuel sans la reflexion
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

				//reinitialisation des pointeurs pour la prochaine iteration
				objetRencontre = nullptr;
				pos = nullptr;
				tmp = nullptr;
			}
	    }
	}
}

//renvoie vrai si le point est eclaire directement par la source lumineuse, faux sinon
bool Scene::eclairageDirect(const Position3D& posIncidence, const std::shared_ptr<Objet> objetSource)
{
	bool direct = true;
	Position3D posSource = this->source.getPos();
	std::shared_ptr<Position3D> collision = nullptr;

	double cosAlpha = objetSource->calculCosinusAlpha(posIncidence, this->source.getPos());

	//si le rayon vers la source ne passe pas par l'objet
	if(cosAlpha >= 0)
	{
		//on verifie que le rayon ne rencontre pas un autre objet
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

//renvoie une couleur selon la formule avec reflexion
Couleur Scene::eclairageAvecReflexion(const std::shared_ptr<Objet> objet, const Couleur& rayonSpeculaire, const Position3D& posIncidence)
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

//renvoie recursivement une couleur selon la formule avec reflexion
Couleur Scene::couleurAvecReflexionRecursive(const std::shared_ptr<Objet> objetSource, const Position3D& sourceRayon, const Position3D& surface, Couleur couleurRayon, unsigned int iteration, const unsigned maxIteration)
{
	//Initialisation des pointeurs
	std::shared_ptr<Objet> objetRencontre = nullptr;
	std::shared_ptr<Position3D> pos = nullptr;
	std::shared_ptr<Position3D> tmp = nullptr;

	Couleur temp;

	if(iteration < maxIteration)
	{
		Position3D reflechi = objetSource->calculRayonReflechi(surface, sourceRayon);

		//on verifie si le rayon reflechi rencontre un objet
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

		//si on rencontre un objet, on fait appel a la methode recursive en tant que parametre pour la couleur du rayon speculaire
		if(objetRencontre != nullptr)
		{
			iteration++;
			couleurRayon = eclairageAvecReflexion(objetSource, couleurAvecReflexionRecursive(objetRencontre, surface, *tmp, couleurRayon, iteration, maxIteration), surface);
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

	return couleurRayon;
}



