/*
 * Parser.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hien-minh.nguyen
 */

#include "Parser.h"
#include "Scene.h"

Parser::Parser() {
}

Parser::~Parser() {
}

/**
 * Permet de lire un fichier et de passer ses donnees dans un objet Scene.
 */
int Parser::lecture(Scene& scene, Ecran& ecran, const std::string& nomFichier) {

	int positionFichier = 0;

	std::ifstream fichier(nomFichier, std::ios::in);

	std::cout << std::endl << "Lancement parser......................." << std::endl;
	if(fichier)
	{
		std::cout << "Fichier charge. Debut de la lecture du fichier !" << std::endl;
		std::string ligne;

		while(getline(fichier, ligne)) //lecture d'une ligne a partir du stream fichier
		{
			if(ligne ==  "") //ignorer les lignes vides (saut de ligne)
			{
				continue;
			}
			else if(ligne.at(0) == '#') //ignorer les commentaires
			{
				continue;
			}

			else
			{
				positionFichier++;

				std::vector<std::string> newParse = parsing(ligne, ' ');

				if(!(ajoutDansScene(positionFichier, newParse, scene, ecran)))
				{
					std::cerr << "Type de fichier incompatible." << std::endl;
					return -1;
				}
			}
		}

		std::cout << ".......................Fin du parser !" << std::endl << std::endl;
		fichier.close();

	}

	else
	{
		std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
		return -1;
	}
	return 0; //0 si pas de bug

}

//parse une ligne selon le deliminateur en parametre
std::vector<std::string> Parser::parsing(const std::string &s, char delim)
{
	std::vector<std::string> stockage;
	std::string buff("");

	for(char n:s)
	{
		if(n != delim)
		{
			buff+=n;
		}
		else
		{
			if(buff != "")
			{
				stockage.push_back(buff);
				buff = "";
			}
		}
	}
	if(buff != "")
	{
		stockage.push_back(buff);
	}

	return stockage;
}

//ajoute un element dans la scene
bool Parser::ajoutDansScene(const int positionFichier, const std::vector<std::string> &parsedString, Scene& scene, Ecran& ecran)
{
	if(positionFichier < 1)
	{
		std::cerr << "Erreur position fichier" << std::endl;
		return false;
	}

	//etape des objets tels que sphere ou triangle a ajouter
	if (positionFichier >= 8)
	{
		if(parsedString.size() == 0)
		{
			std::cerr << "Erreur donnee : Ajout objet." << std::endl;
			return false;
		}
		else
		{
			if((parsedString[0].compare("sphere:")) == 0 && parsedString.size() == 9)
			{
				Position3D p = Position3D(atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()),atoi(parsedString[3].c_str()));
				Couleur c = Couleur(atoi(parsedString[5].c_str()),atoi(parsedString[6].c_str()),atoi(parsedString[7].c_str()));

				double ref = (atof(parsedString[8].c_str()));
				double rad = (atof(parsedString[4].c_str()));

				std::shared_ptr<Objet> o(new Sphere(p, c, ref, rad));
				scene.addObjet(o);
			}
			else if((parsedString[0].compare("triangle:")) == 0 && parsedString.size() == 14)
			{
				Position3D p1 = Position3D(atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()),atoi(parsedString[3].c_str()));
				Position3D p2 = Position3D(atoi(parsedString[4].c_str()),atoi(parsedString[5].c_str()),atoi(parsedString[6].c_str()));
				Position3D p3 = Position3D(atoi(parsedString[7].c_str()),atoi(parsedString[8].c_str()),atoi(parsedString[9].c_str()));

				if((p1 == p2) || (p1 == p3) || (p2 == p3))
				{
					std::cerr << "Erreur ajout triangle : les points ne sont pas distincts" << std::endl;
					return false;
				}

				if(Position3D::vectUnitaire(p1, p2) == Position3D::vectUnitaire(p1, p3))
				{
					std::cerr << "Erreur ajout triangle : les points A, B et C sont alignes" << std::endl;
					return false;
				}

				Couleur c = Couleur(atoi(parsedString[10].c_str()),atoi(parsedString[11].c_str()),atoi(parsedString[12].c_str()));

				double ref = (atof(parsedString[13].c_str()));

				std::shared_ptr<Objet> o(new Triangle(c, ref, p1, p2, p3));
				scene.addObjet(o);
			}
			else
			{
				std::cerr << "Erreur donnee : ajout {" << parsedString[0] << "} impossible" << std::endl;
				return false;
			}
		}
	}
	//le reste
	else
	{
		switch (positionFichier) {
			//1 : camera
			case 1:
				if(parsedString.size() != 3)
				{
					std::cerr << "Erreur donnee : Camera." << std::endl;
			    	return false;
				}
				else
				{
					Position3D p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));
					scene.setCamera(Camera(p));
				}
				break;

			//2 : top left corner
			case 2:
				if(parsedString.size() != 3)
				{
					std::cerr << "Erreur donnee : TopLeftCenter." << std::endl;
			    	return false;
				}
				else
				{
					Position3D p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					ecran.setTlc(p);
					scene.setEcran(ecran);
				}
				break;

			//3 : top right corner
			case 3:
				if(parsedString.size() != 3)
					{
						std::cerr << "Erreur donnee : TopRightCenter." << std::endl;
				    	return false;
					}
					else
					{
						Position3D p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						ecran.setTrc(p);
						scene.setEcran(ecran);
					}
				break;

			//4 : bottom left corner
			case 4:
				if(parsedString.size() != 3)
					{
						std::cerr << "Erreur donnee : BottomLeftCenter." << std::endl;
				    	return false;
					}
					else
					{
						Position3D p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						ecran.setBlc(p);
						scene.setEcran(ecran);

						/**
						 * Creation du quatrieme point (BottomRightCorner).
						 */

						ecran.creationBrc();
						scene.setEcran(ecran);
					}
				break;

			//5 : resolution
			case 5:
				if(parsedString.size() != 1)
				{
					std::cerr << "Erreur donnee : resolution." << std::endl;
			    	return false;
				}
				else
				{
					ecran.setResHorizontale(atoi(parsedString[0].c_str()));
					scene.setEcran(ecran);
				}
				break;

			//6 : background color
			case 6:
				if(parsedString.size() != 3)
				{
					std::cerr << "Erreur donnee : background color." << std::endl;
					return false;
				}
				else
				{
					Couleur c = Couleur(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					ecran.calculResVer(c);
					scene.setEcran(ecran);
				}
				break;

			//7 : light position & light color
			case 7:
				if(parsedString.size() != 6)
				{
					std::cerr << "Erreur donnee : Light position & Light color." << std::endl;
					return false;
				}
				else
				{
					Position3D p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));
					Couleur c = Couleur(atoi(parsedString[3].c_str()),atoi(parsedString[4].c_str()),atoi(parsedString[5].c_str()));

					scene.setSource(Source(p, c));
				}
				break;
			default:
				std::cerr << "Erreur parser : Fichier incompatible." << std::endl;
		}
	}

	return true;
}





