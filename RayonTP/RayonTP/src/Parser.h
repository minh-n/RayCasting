/*
 * Parser.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <cstdlib>
#include <limits>
#include "Scene.h"

class Parser {

public:
	Parser();

	~Parser();

	//parcours le fichier et ignore les commentaires/saut de ligne
	int lecture(Scene& scene, Ecran& ecran, const std::string& nomFichier);

	//ajoute un element dans la scene
	bool ajoutDansScene(const int positionFichier, const std::vector<std::string> &parsedString, Scene& scene, Ecran& ecran);

	//parse une ligne selon le deliminateur en parametre
	std::vector<std::string> parsing(const std::string &s, char delim);

};

#endif /* PARSER_H_ */
