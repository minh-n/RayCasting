/*
 * Ecran.cpp
 *
 *  Created on: Dec 11, 2017
 *      Author: hien-minh.nguyen
 */

#include "Ecran.h"

/**
 * PIXEL
 */

Pixel::Pixel(){

}

Pixel::Pixel(Pixel const& pixel){
	this->position = pixel.position;
	this->couleur = pixel.couleur;
}

Pixel::Pixel(Position3D p, Couleur c) {
	this->position = p;
	this->couleur = c;
}

Pixel::~Pixel() {

}

Pixel& Pixel::operator=(Pixel const& p)
{
	this->position = p.position;
	this->couleur = p.couleur;

	return *this;
}

/**
 * ECRAN
 */

Ecran::Ecran() : resHorizontale(0), resVerticale(0){

}

Ecran::~Ecran() {

}

void Ecran::creationBrc()
{
	double x = trc.getX() - tlc.getX() + blc.getX();
	double y = trc.getY() - tlc.getY() + blc.getY();
	double z = trc.getZ() - tlc.getZ() + blc.getZ();
	brc.setX(x);
	brc.setY(y);
	brc.setZ(z);
}

void Ecran::calculResVer()
{
	double longueurHorizontale = sqrt(pow((brc.getX() - blc.getX()), 2)
			+ pow((brc.getY() - blc.getY()), 2)
			+ pow((brc.getZ() - blc.getZ()), 2));

	double longueurVerticale = sqrt(pow((tlc.getX() - blc.getX()), 2)
			+ pow((tlc.getY() - blc.getY()), 2)
			+ pow((tlc.getZ() - blc.getZ()),2));

	resVerticale = (resHorizontale/ ((int)longueurHorizontale))*((int)longueurVerticale);

	initPixels(); //initialisation du tableau de pixels
}

void Ecran::initPixels()
{
		//http://www.cplusplus.com/forum/articles/7459/
		pixels.resize(resVerticale);
		for (int i = 0; i < resVerticale; ++i)
		{
			pixels[i].resize(resHorizontale);
		}

		for (int j = 0; j < resVerticale; ++j)
		{
			for(int k = 0; k < resHorizontale; ++k)
			{
				pixels[j][k].setPosition(Position3D(
							tlc.getX() + ((double)j/resVerticale)*(trc.getX() - tlc.getX()) + ((double)k/resHorizontale)* (blc.getX() - tlc.getX()),
				            tlc.getY() + ((double)j/resVerticale)*(trc.getY() - tlc.getY()) + ((double)k/resHorizontale)* (blc.getY() - tlc.getY()),
				            tlc.getZ() + ((double)j/resVerticale)*(trc.getZ() - tlc.getZ()) + ((double)k/resHorizontale)* (blc.getZ() - tlc.getZ())));
			}
		}
}

void Ecran::initCouleurBg(Couleur c)
{
	for (int j = 0; j < resVerticale; ++j)
	{
		for(int k = 0; k < resHorizontale; ++k)
		{
			pixels[j][k].setCouleur(c);
		}
	}
}
