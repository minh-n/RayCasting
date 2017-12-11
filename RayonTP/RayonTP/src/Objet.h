/*
 * Objet.h
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#ifndef OBJET_H_
#define OBJET_H_
#include "Vecteur.h"

/**
 * OBJET
 */

class Objet {

private :

	Position position;
	Couleur couleur;

public:

	Objet();

	Objet(Position pos, Couleur coul) : position(pos), couleur(coul){};


	Objet(Position p);

	virtual ~Objet();

	const Position& getPosition() const {
		return position;
	}

	void setPosition(const Position& pos) {
		this->position = pos;
	}

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}
};


#endif /* OBJET_H_ */
