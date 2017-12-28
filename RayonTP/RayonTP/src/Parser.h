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

	int lecture(Source *source, Ecran *ecran, Scene *scene);
	bool ajoutDansScene(const int positionFichier, const std::vector<std::string> &parsedString, Source *source,  Ecran *ecran, Scene *scene);
	std::vector<std::string> parsing(const std::string &s, char delim);

};

#endif /* PARSER_H_ */
