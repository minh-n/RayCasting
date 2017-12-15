/*
 * Ecran.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: hien-minh.nguyen
 */

#include "Ecran.h"

/**
 * ECRAN
 */


Ecran::Ecran() {
	resHorizontale = 0;
	resVerticale = 0;

	// TODO Auto-generated constructor stub
}


Ecran::~Ecran() {
	// TODO Auto-generated destructor stub
}






/**
 * PIXEL
 */

Pixel::Pixel() {
}

Pixel::Pixel(Position p, Couleur c) {
	position = p;
	couleur = c;
}

Pixel::~Pixel() {
}
