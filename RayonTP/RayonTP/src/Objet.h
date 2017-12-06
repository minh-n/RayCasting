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

	Position pos;
	Couleur couleur;

public:

	Objet();
	Objet(Position p, int ref);

	virtual ~Objet();


	virtual double getReflection() const;
	virtual double getRadius() const;

	const Position& getPos() const {
		return pos;
	}

	void setPos(const Position& pos) {
		this->pos = pos;
	}

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}
};


#endif /* OBJET_H_ */
