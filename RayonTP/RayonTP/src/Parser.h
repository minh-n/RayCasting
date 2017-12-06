/*
 * Parser.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <vector>
#include <string>
#include "Scene.h"
#include <string>

class Parser {

public:
	Parser();
	virtual ~Parser();
	int lecture(Camera camera, Ecran ecran, Scene scene, Sphere s1, Sphere s2, Sphere s3);

	void ajoutDansScene(int positionFichier, std::vector<std::string> &parsedString, Camera camera, Ecran ecran, Scene scene, Sphere s1, Sphere s2, Sphere s3);
	std::vector<std::string> parsing(const std::string &s, char delim);

};

#endif /* PARSER_H_ */
