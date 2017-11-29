/*
 * Objet.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef OBJET_H_
#define OBJET_H_
#include <vector>


class Objet {

private :

	std::vector<int> c;
	int bail;

public:
	virtual void getSize(int a) = 0;

	Objet();
	virtual ~Objet();

};

#endif /* OBJET_H_ */


