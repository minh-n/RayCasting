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

		std::vector<std::vector<double> > array2D;

		  // Set up sizes. (HEIGHT x WIDTH)
		  array2D.resize(resVerticale);
		  for (int i = 0; i < resVerticale; ++i)
		    array2D[i].resize(resHorizontale);

		  // Put some values in
		  array2D[1][2] = 6.0;
		  array2D[3][1] = 5.5;

		pixels.resize(resVerticale);
		for (int i = 0; i < resVerticale; ++i)
			pixels[i].resize(resHorizontale);

		Position p = Position(1,2,3);
		Position p2 = Position(100,20,55);

		Couleur c = Couleur(4,5,6);
		Couleur c2 = Couleur(4,50,60);

		Pixel a = Pixel(p, c);
		Pixel b = Pixel(p2, c2);

		pixels[1][2] = a;
		pixels[300][100] = b;

		std::cout << "size pixels table (seulement horizontale ?) : "
		 << pixels.size() << "\nTEST AFFICHE PIXEL" << std::endl;
		pixels[1][2].getCouleur().afficherCouleur();
		pixels[300][100].getPosition().afficherPos();
		//affichage ok

		//test impression pixels
		for (int j = 0; j < resVerticale; ++j)
		{
			for(int k = 0; k < resHorizontale; ++k)
			{
					Couleur c = Couleur(j+200, k+55, 5);
					pixels[j][k].setCouleur(c);				
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
