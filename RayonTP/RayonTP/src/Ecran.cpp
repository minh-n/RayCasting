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

void Ecran::initPixels()
{


		//http://www.cplusplus.com/forum/articles/7459/

		pixels.resize(resVerticale);
		for (int i = 0; i < resVerticale; ++i)
			pixels[i].resize(resHorizontale);

		//test impression pixels
		for (int j = 0; j < resVerticale; ++j)
		{
			for(int k = 0; k < resHorizontale; ++k)
			{
				pixels[j][k].setPosition(Position(
							tlc.getX() + ((double)j/resVerticale)*(trc.getX() - tlc.getX()) + ((double)k/resHorizontale)* (blc.getX() - tlc.getX()),
				            tlc.getY() + ((double)j/resVerticale)*(trc.getY() - tlc.getY()) + ((double)k/resHorizontale)* (blc.getY() - tlc.getY()),
				            tlc.getZ() + ((double)j/resVerticale)*(trc.getZ() - tlc.getZ()) + ((double)k/resHorizontale)* (blc.getZ() - tlc.getZ())));
			}
		}

		/*
		 * TODO : Faire une fonction de normalisation des couleurs. 
		 * si getCouleur() > 255, alors on fait -255.
		 */
//		for (int j = 0; j < resVerticale; ++j)
//		{
//			for(int k = 0; j < resHorizontale; ++k)
//			{
//				if(pixels[j][k].getCouleur().getB() != 0)
//				{
//					pixels[j][k].getCouleur().afficherCouleur();
//					pixels[j][k].getPosition().afficherPos();
//				}
//
//			}
//		}

}


void Ecran::initCouleur(Couleur c)
{
	for (int j = 0; j < resVerticale; ++j)
	{
		for(int k = 0; k < resHorizontale; ++k)
		{
			pixels[j][k].setCouleur(c);
		}
	}
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
