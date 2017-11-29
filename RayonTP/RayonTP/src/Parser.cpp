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



    ifstream fichier("readme.txt", ios::in);


    if(fichier)
    {
    	cout << "Debut de la lecture du fichier !\n\n";
    	while(!(fichier.eof())) //boucle jusqu'à la fin du fichier
    	{
        	char c = fichier.get(); //lecture d'un caractere
        	if(c == '#') //ignorer les commentaires
        	{
        		fichier.ignore(numeric_limits<int>::max(), '\n');
        		cout << "comm detected !!!!!!!!!!!!\n";
        	}
        	else
        	{
        		cout << c;
        	}
    	}
    	fichier.close();
    }

    else
    {
    	cerr <<  "Impossible d'ouvrir le fichier" << endl;
    }

    return 0;

}
