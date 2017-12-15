/*
 * Parser.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hien-minh.nguyen
 */

#include "Parser.h"
#include "Scene.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;

Parser::Parser() {
}

Parser::~Parser() {
}



/**
 * Permet de lire un fichier et de passer ses donnees dans un objet Scene.
 */
int Parser::lecture(Source *source, Ecran *ecran, Scene *scene) {

    int positionFichier = 0;

    ifstream fichier("readme.txt", ios::in);

    cout << "Lancement parser.......................\n";
    if(fichier)
    {
    	cout << "Fichier charge. Debut de la lecture du fichier !\n\n";
        string ligne;

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
                
                vector<string> newParse = parsing(ligne, ' ');

                if(!(ajoutDansScene(positionFichier, newParse, source, ecran, scene)))
                {
                	cerr << "Type de fichier incompatible." << endl;
                	return -1;
                }
        	}
    	}
    	fichier.close();
    }

    else
    {
    	cerr << "Impossible d'ouvrir le fichier." << endl;
    	return -1;
    }
    return 0; //0 si pas de bug

}


vector<string> Parser::parsing(const string &s, char delim)
{
	vector<string> stockage;

	string buff("");

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



bool Parser::ajoutDansScene(const int positionFichier, const vector<string> &parsedString, Source *source, Ecran *e, Scene *scene)
{
	int nbObjet = 0;

	if(positionFichier < 1)
	{
		cerr << "Erreur position fichier" << endl;
		return false;
	}

	if (positionFichier >= 8)
	{
		nbObjet = positionFichier - 8;

		if(parsedString.size() != 9)
		{
			cerr << "Erreur donnee : Ajout objet." << endl;
			return false;
		}

		Position *p;
		p = new Position(atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()),atoi(parsedString[3].c_str()));

		Couleur *c;
		c = new Couleur(atoi(parsedString[5].c_str()),atoi(parsedString[6].c_str()),atoi(parsedString[7].c_str()));

		double ref = (atof(parsedString[8].c_str()));
		double rad = (atof(parsedString[4].c_str()));

		if(!(parsedString[0]).compare("sphere:"))
		{
			scene->addObjet(new Sphere(*p, *c, ref, rad));

			cout << "Sphere " << nbObjet << " : \n";
			scene->getNosObjets().at(nbObjet)->afficher();
		}
		else
		{
			cout << "Type de l'objet (" << parsedString[0] << ") non reconnu.";
		}

	}
	else
	{
		switch (positionFichier) {
			case 1: //1 : camera

				if(parsedString.size() != 3)
				{
			    	cerr << "Erreur donnee : Camera." << endl;
			    	return false;
				}
				else
				{
					Position p;
					/**
					 * TODO : mettre atoi exterieur
					 */
					p = Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));
					Camera *c;
					c = new Camera(p);

					scene->setCamera(*c);

					cout << "camera : ";
					scene->getCamera().getPos().afficherPos();
					cout << "\n\n";
				}
				break;
			case 2:	//2 : tlc


				if(parsedString.size() != 3)
				{
			    	cerr << "Erreur donnee : TopLeftCenter." << endl;
			    	return false;
				}
				else
				{
					Position p;
					/**
					 * TODO : mettre atoi exterieur
					 */
					p = Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


					e->setTlc(p);
					scene->setEcran(*e);

					cout << "topLeftScreen : ";
					scene->getEcran().getTlc().afficherPos();
					cout << "\n";
				}

				break;

			case 3:	//3 : trc
				if(parsedString.size() != 3)
					{
				    	cerr << "Erreur donnee : TopRightCenter." << endl;
				    	return false;
					}
					else
					{
						Position p;
						/**
						 * TODO : mettre atoi exterieur
						 */
						p = Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


						e->setTrc(p);
						scene->setEcran(*e);

						cout << "topRightScreen : ";
						scene->getEcran().getTrc().afficherPos();
						cout << "\n";

					}
				break;

			case 4:	//4 : blc

				if(parsedString.size() != 3)
					{
				    	cerr << "Erreur donnee : BottomLeftCenter." << endl;
				    	return false;
					}
					else
					{
						Position p;
						/**
						 * TODO : mettre atoi exterieur
						 */
						p = Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						e->setBlc(p);
						scene->setEcran(*e);

						cout << "bottomLeftScreen : ";
						scene->getEcran().getBlc().afficherPos();
						cout << "\n";

						/**
						 * Creation du quatrieme point (BottomRightCorner).
						 */

						e->creationBrc();
						scene->setEcran(*e);

						cout << "bottomRightScreen : ";
						scene->getEcran().getBrc().afficherPos();
						cout << "\n\n";

					}
				break;

			case 5:	//5 : resol

				if(parsedString.size() != 1)
				{
			    	cerr << "Erreur donnee : resolution." << endl;
			    	return false;
				}
				else
				{
					e->setResHorizontale(atoi(parsedString[0].c_str()));
					e->calculResVer();
					scene->setEcran(*e);

					cout << "resolution horizontale : ";
					cout << scene->getEcran().getResHorizontale() << endl;

					cout << "resolution verticale : ";
					cout << scene->getEcran().getResVerticale() << "\n\n" << endl;

				}
				break;

			case 6: //6 : bg color

				if(parsedString.size() != 3)
					{
				    	cerr << "Erreur donnee : background color." << endl;
				    	return false;
					}
					else
					{
						Couleur c;
						c = Couleur(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

						scene->setBgColor(c);

						cout << "background color : ";
						scene->getBgColor().afficherCouleur();
						cout << "\n";
					}
				break;

			case 7: //7 : light position & light color

				if(parsedString.size() != 6)
				{
					cerr << "Erreur donnee : Light position & Light color." << endl;
					return false;
				}

				else
				{
					Position *p;
					p = new Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					Couleur *c;
					c = new Couleur(atoi(parsedString[3].c_str()),atoi(parsedString[4].c_str()),atoi(parsedString[5].c_str()));

					source->setPos(*p);

					source->setCouleur(*c);

					scene->setSource(*source);

					cout << "Light position : ";
					scene->getSource().getPos().afficherPos();
					cout << "\n\n";

					cout << "Light couleur : ";
					scene->getSource().getCouleur().afficherCouleur();

					cout << "\n\n";

				}
				break;
			default:

		    	cerr << "Erreur parser : Fichier incompatible." << endl;
		}
	}


	return true;

}





