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
	int reflection;

public:

	Objet();
	Objet(Position p, int ref);

	virtual ~Objet();

	const Position& getPos() const {
		return pos;
	}

	void setPos(const Position& pos) {
		this->pos = pos;
	}

	int getReflection() const {
		return reflection;
	}

	void setReflection(int reflection) {
		this->reflection = reflection;
	}

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}
};


#endif /* OBJET_H_ */
