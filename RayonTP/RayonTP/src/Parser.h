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

class Parser {

public:
	Parser();
	virtual ~Parser();
	int lecture();

	std::vector<std::string> parsing(const std::string &s, char delim);

};

#endif /* PARSER_H_ */
