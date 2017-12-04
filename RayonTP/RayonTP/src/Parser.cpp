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
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}


int Parser::lecture(Camera camera, Ecran ecran, Scene scene, Sphere s1, Sphere s2, Sphere s3) {

    int positionFichier = 0;

    ifstream fichier("readme.txt", ios::in);

    cout << "Lancement parser.......................\n";
    if(fichier)
    {
    	cout << "Fichier charge. Debut de la lecture du fichier !\n\n";
        string ligne;

    	while(getline(fichier, ligne)) //lecture d'une ligne a partir du stream fichier
    	{
           
        	if(ligne.at(0) == '#') //ignorer les commentaires
        	{
        		//fichier.ignore(numeric_limits<int>::max(), '\n');
        		continue;
        	}
        
        	else
        	{
        		positionFichier++;
                
                vector<string> newParse = parsing(ligne, ' ');
                ajoutDansScene(positionFichier, newParse, camera, ecran, scene, s1, s2, s3);
        	}
    	}
    	fichier.close();
    }

    else
    {
    	cerr << "Impossible d'ouvrir le fichier." << endl;
    }
    return 0; //0 si pas de bug

}


vector<string> Parser::parsing(const string &s, char delim)
{
	vector<string> stockage;

	string buff("");

	for(auto n:s)
	{
		if(n != delim) buff+=n; else
			if(n == delim && buff != "")
			{
				stockage.push_back(buff); buff = "";
			}
	}
	if(buff != "")
	{
		stockage.push_back(buff);
	}

	return stockage;
}



void Parser::ajoutDansScene(int positionFichier, vector<string> &parsedString, Camera camera, Ecran ecran, Scene scene, Sphere s1, Sphere s2, Sphere s3)
{


	switch (positionFichier) {
		case 1: //1 : camera

			cout << "camera : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] << "\n\n";

			break;

		case 2:	//2 : tlc

			cout << "topLeftScreen : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] << "\n";

			break;

		case 3:	//3 : trc

			cout << "topRightScreen : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] << "\n";
			break;

		case 4:	//4 : blc

			cout << "bottomLeftScreen : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] << "\n";

			break;

		case 5:	//5 : resol

			cout << "resolution : " << parsedString[0] << "\n\n";

			break;

		case 6: //6 : bg color

			cout << "background color : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] << "\n\n";

			break;

		case 7: //7 : light position & light color

			cout << "light source position : ";
			cout << parsedString[0] << " " << parsedString[1] << " " << parsedString [2] ;
			cout << ", light source color : ";
			cout << parsedString[3] << " " << parsedString[4] << " " << parsedString [5] << "\n\n";

			break;

		case 8: //8 : sphere 1

			cout << "sphere1 position : ";
			cout << parsedString[1] << " " << parsedString[2] << " " << parsedString [3];
			cout << ", sphere1 color : ";
			cout << parsedString[5] << " " << parsedString[6] << " " << parsedString [7] <<
					"\n\t\tref = " << parsedString[8] << ", radius = " << parsedString[4] << "\n\n";

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
			break;
	}








}





