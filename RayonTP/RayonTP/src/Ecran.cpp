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

Pixel::Pixel(Position3D p, Couleur c) : position(p), couleur(c) {

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

//calcul du quatrieme point a partir des trois autres
void Ecran::creationBrc()
{
	double x = trc.getX() - tlc.getX() + blc.getX();
	double y = trc.getY() - tlc.getY() + blc.getY();
	double z = trc.getZ() - tlc.getZ() + blc.getZ();

	brc = Position3D(x, y, z);
}

//calcul la resolution verticale
void Ecran::calculResVer(const Couleur bgCouleur)
{
	double longueurHorizontale = Position3D::norme(blc, brc);
	double longueurVerticale = Position3D::norme(blc, tlc);

	resVerticale = (resHorizontale/ ((int)longueurHorizontale))*((int)longueurVerticale);
	initPixels(bgCouleur); //initialisation du tableau de pixels
}

//initialise le tableau de pixel et fait coorespondre la couleur de chaque pixel a la couleur de fond
void Ecran::initPixels(const Couleur bgCouleur)
{
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
				pixels[j][k].setCouleur(bgCouleur);
			}
		}
}
