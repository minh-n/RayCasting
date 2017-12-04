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


int Parser::lecture() {

    int positionFichier = 0;

    ifstream fichier("readme.txt", ios::in);

    cout << "Parser lancement\n";
    if(fichier)
    {
    	cout << "Debut de la lecture du fichier !\n\n";
        string ligne;

    	while(getline(fichier, ligne)) //lecture d'une ligne
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
                
        		cout << newParse[0] << "\n";
        	}
    	}
    	fichier.close();
    }

    else
    {
    	cerr << "Impossible d'ouvrir le fichier" << endl;
    }
    return 0;

}


vector<string> Parser::parsing(const string &s, char delim)
{
	vector<string> stockage;

	string buff;

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









