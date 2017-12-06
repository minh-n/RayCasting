/*
 * Objet.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#include "Objet.h"

/**
 * OBJET
 */

Objet::Objet() {
	reflection = 0;
	// TODO Auto-generated constructor stub

}

Objet::Objet(Position p, int ref) {
	// TODO Auto-generated constructor stub
	pos = p;
	reflection = ref;
}

Objet::~Objet() {
	// TODO Auto-generated destructor stub
}


