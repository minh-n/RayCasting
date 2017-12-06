/*
 * Parser.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hien-minh.nguyen
 */

#include "Parser.h"
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
int Parser::lecture(Ecran &ecran, Scene &scene) {

    int positionFichier = 0;

    ifstream fichier("readme.txt", ios::in); //c_str() pour passer fiojk

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
                if(!(ajoutDansScene(positionFichier, newParse, ecran, scene)))
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



bool Parser::ajoutDansScene(const int positionFichier, const vector<string> &parsedString, Ecran &e, Scene &scene)
{
	if(positionFichier < 1)
	{
		cerr << "Erreur position fichier" << endl;
		return false;
	}
	switch (positionFichier) {

		case 1: //1 : camera

			if(parsedString.size() != 3)
			{
		    	cerr << "Erreur donnee : camera." << endl;
		    	return false;
			}
			else
			{
				Position *p;
				p = new Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));
				Camera *c;
				c = new Camera(*p);

				scene.setCamera(*c);

				cout << "camera : ";
				cout << scene.getCamera().getPos().getX() << " " << scene.getCamera().getPos().getY() << " " << scene.getCamera().getPos().getZ() << "\n\n";
			}
			break;

		case 2:	//2 : tlc


			if(parsedString.size() != 3)
			{
		    	cerr << "Erreur donnee : TLC." << endl;
		    	return false;
			}
			else
			{
				Position *p;
				p = new Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


				e.setTlc(*p);
				scene.setEcran(e);

				cout << "topLeftScreen : ";
				cout << scene.getEcran().getTlc().getX() << " " << scene.getEcran().getTlc().getY() << " " << scene.getEcran().getTlc().getZ() << "\n\n";
			}

			break;

		case 3:	//3 : trc
			if(parsedString.size() != 3)
				{
			    	cerr << "Erreur donnee : TRC." << endl;
			    	return false;
				}
				else
				{
					Position *p;
					p = new Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


					e.setTrc(*p);
					scene.setEcran(e);

					cout << "topRightScreen : ";
					cout << scene.getEcran().getTrc().getX() << " " << scene.getEcran().getTrc().getY() << " " << scene.getEcran().getTrc().getZ() << "\n\n";
				}
			break;

		case 4:	//4 : blc

			if(parsedString.size() != 3)
				{
			    	cerr << "Erreur donnee : BLC." << endl;
			    	return false;
				}
				else
				{
					Position *p;
					p = new Position(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));


					e.setBlc(*p);
					scene.setEcran(e);

					cout << "bottomLeftScreen : ";
					cout << scene.getEcran().getBlc().getX() << " " << scene.getEcran().getBlc().getY() << " " << scene.getEcran().getBlc().getZ() << "\n\n";
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
				e.setResolution(atoi(parsedString[0].c_str()));

				scene.setEcran(e);

				cout << "resolution : ";
				cout << scene.getEcran().getResolution() << "\n\n";
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
					Couleur *c;
					c = new Couleur(atoi(parsedString[0].c_str()),atoi(parsedString[1].c_str()),atoi(parsedString[2].c_str()));

					scene.setBgColor(*c);

					cout << "background color : ";
					cout << scene.getBgColor().getR() << " " << scene.getBgColor().getG() << " " << scene.getBgColor().getB() << "\n\n";
				}
			break;
		case 7: //7 : light position & light color

			/**
			 * TODO
			 */

			break;

		case 8: //8 : sphere 1

			/**
			 * TODO
			 *
			 */
			break;

		case 9:	//9 : sphere 2

			cout << "sphere2 position : ";
			cout << parsedString[1] << " " << parsedString[2] << " " << parsedString [3];
			cout << ", sphere2 color : ";
			cout << parsedString[5] << " " << parsedString[6] << " " << parsedString [7] <<
					"\n\t\tref = " << parsedString[8] << ", radius = " << parsedString[4] << "\n\n";
//shankar
			break;

		case 10: //10 : sphere 3

			cout << "sphere3 position : ";
			cout << parsedString[1] << " " << parsedString[2] << " " << parsedString [3];
			cout << ", sphere3 color : ";
			cout << parsedString[5] << " " << parsedString[6] << " " << parsedString [7] <<
					"\n\t\tref = " << parsedString[8] << ", radius = " << parsedString[4] << "\n\n";

			break;

		default:
	    	cerr << "Fichier incompatible." << endl;
			break;
	}






	return true;

}





