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
int Parser::lecture(Source& source, Ecran& ecran, Scene& scene) {

    int positionFichier = 0;

    std::ifstream fichier("MinhScene.txt", std::ios::in);

    std::cout << "Lancement parser.......................\n";
    if(fichier)
    {
    	std::cout << "Fichier charge. Debut de la lecture du fichier !\n\n";
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

                if(!(ajoutDansScene(positionFichier, newParse, source, ecran, scene)))
                {
                	std::cerr << "Type de fichier incompatible." << std::endl;
                	return -1;
                }
        	}
    	}
    	fichier.close();
    }

    else
    {
    	std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    	return -1;
    }
    return 0; //0 si pas de bug

}


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



bool Parser::ajoutDansScene(const int positionFichier, const std::vector<std::string> &parsedString, Source& source, Ecran& e, Scene& scene)
{
	int nbObjet = 0;

	if(positionFichier < 1)
	{
		std::cerr << "Erreur position fichier" << std::endl;
		return false;
	}

	if (positionFichier >= 8)
	{
		nbObjet = positionFichier - 8;

		if(parsedString.size() != 9)
		{
			std::cerr << "Erreur donnee : Ajout objet." << std::endl;
			return false;
		}

		Position3D p;
		p = Position3D(atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()),atoi(parsedString[3].c_str()));

		Couleur c;
		c = Couleur(atoi(parsedString[5].c_str()),atoi(parsedString[6].c_str()),atoi(parsedString[7].c_str()));

		double ref = (atof(parsedString[8].c_str()));
		double rad = (atof(parsedString[4].c_str()));

		if(!(parsedString[0]).compare("sphere:"))
		{
			scene.addObjet(new Sphere(p, c, ref, rad));

			std::cout << "Sphere " << nbObjet << " : \n";
			scene.getNosObjets().at(nbObjet)->afficher();
		}
		else
		{
			std::cout << "Type de l'objet (" << parsedString[0] << ") non reconnu.";
		}

	}
	else
	{
		switch (positionFichier) {
			case 1: //1 : camera

				if(parsedString.size() != 3)
				{
					std::cerr << "Erreur donnee : Camera." << std::endl;
			    	return false;
				}
				else
				{
					Position3D p;
					/**
					 * TODO : mettre atoi exterieur
					 */
					p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					Camera cam = Camera(p);
					scene.setCamera(cam);

					std::cout << "camera : ";
					scene.getCamera().getPos().afficherPos();
					std::cout << "\n\n";
				}
				break;
			case 2:	//2 : tlc


				if(parsedString.size() != 3)
				{
					std::cerr << "Erreur donnee : TopLeftCenter." << std::endl;
			    	return false;
				}
				else
				{
					Position3D p;
					/**
					 * TODO : mettre atoi exterieur
					 */
					p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


					e.setTlc(p);
					scene.setEcran(e);

					std::cout << "topLeftScreen : ";
					scene.getEcran().getTlc().afficherPos();
					std::cout << "\n";
				}

				break;

			case 3:	//3 : trc
				if(parsedString.size() != 3)
					{
						std::cerr << "Erreur donnee : TopRightCenter." << std::endl;
				    	return false;
					}
					else
					{
						Position3D p;
						/**
						 * TODO : mettre atoi exterieur
						 */
						p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


						e.setTrc(p);
						scene.setEcran(e);

						std::cout << "topRightScreen : ";
						scene.getEcran().getTrc().afficherPos();
						std::cout << "\n";

					}
				break;

			case 4:	//4 : blc

				if(parsedString.size() != 3)
					{
						std::cerr << "Erreur donnee : BottomLeftCenter." << std::endl;
				    	return false;
					}
					else
					{
						Position3D p;
						/**
						 * TODO : mettre atoi exterieur
						 */
						p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						e.setBlc(p);
						scene.setEcran(e);

						std::cout << "bottomLeftScreen : ";
						scene.getEcran().getBlc().afficherPos();
						std::cout << "\n";

						/**
						 * Creation du quatrieme point (BottomRightCorner).
						 */

						e.creationBrc();
						scene.setEcran(e);

						std::cout << "bottomRightScreen : ";
						scene.getEcran().getBrc().afficherPos();
						std::cout << "\n\n";

					}
				break;

			case 5:	//5 : resol

				if(parsedString.size() != 1)
				{
					std::cerr << "Erreur donnee : resolution." << std::endl;
			    	return false;
				}
				else
				{
					e.setResHorizontale(atoi(parsedString[0].c_str()));
					e.calculResVer();
					scene.setEcran(e);

					std::cout << "resolution horizontale : ";
					std::cout << scene.getEcran().getResHorizontale() << std::endl;

					std::cout << "resolution verticale : ";
					std::cout << scene.getEcran().getResVerticale() << "\n\n" << std::endl;

				}
				break;

			case 6: //6 : bg color

				if(parsedString.size() != 3)
					{
						std::cerr << "Erreur donnee : background color." << std::endl;
				    	return false;
					}
					else
					{
						Couleur c;
						c = Couleur(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						scene.setBgColor(c);

						e.setResHorizontale(scene.getEcran().getResHorizontale());
						e.calculResVer();
						e.initCouleurBg(c);
						scene.setEcran(e);


						std::cout << "background color : ";
						scene.getBgColor().afficherCouleur();
						std::cout << "\n";
					}
				break;

			case 7: //7 : light position & light color

				if(parsedString.size() != 6)
				{
					std::cerr << "Erreur donnee : Light position & Light color." << std::endl;
					return false;
				}

				else
				{
					Position3D p;
					p = Position3D(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					Couleur c;
					c = Couleur(atoi(parsedString[3].c_str()),atoi(parsedString[4].c_str()),atoi(parsedString[5].c_str()));

					source.setPos(p);

					source.setCouleur(c);

					scene.setSource(source);

					std::cout << "Light position : ";
					scene.getSource().getPos().afficherPos();
					std::cout << "\n\n";

					std::cout << "Light couleur : ";
					scene.getSource().getCouleur().afficherCouleur();

					std::cout << "\n\n";

				}
				break;
			default:

				std::cerr << "Erreur parser : Fichier incompatible." << std::endl;
		}
	}


	return true;

}





