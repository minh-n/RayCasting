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

protected :

	Position position;
	Couleur couleur;

public:

	Objet();

	Objet(Position pos, Couleur coul) : position(pos), couleur(coul){};


	Objet(Position p);

	virtual ~Objet();

	virtual void afficher() const = 0;

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

	virtual Position* intersection(const Position& pos1, const Position& pos2) const = 0;
};



#endif /* OBJET_H_ */
