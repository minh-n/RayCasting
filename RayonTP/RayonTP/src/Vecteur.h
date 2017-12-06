/*
 * Vecteur.h
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef VECTEUR_H_
#define VECTEUR_H_

class Position {
private:
	int x;
	int y;
	int z;

public:
	Position();
	Position(int x, int y, int z);
	Position(const Position &source);

	virtual ~Position();
};



class Couleur {
private:
	int r;
	int g;
	int b;

public:
	Couleur();
	Couleur(int r, int g, int b);
	Couleur(const Couleur &source);

	virtual ~Couleur();
};
#endif /* VECTEUR_H_ */
