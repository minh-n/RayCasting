/*
 * Objet.h
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#ifndef OBJET_H_
#define OBJET_H_
#include "Vecteur.h"
#include <cmath>

/**
 * OBJET
 */

class Objet {

protected :
	Position position;
	Couleur couleur;
	double reflection;

public:

	Objet() : reflection(0){};

	Objet(Position pos, Couleur coul, double ref) : position(pos), couleur(coul), reflection(ref){};

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

	double getReflection() const {
		return reflection;
	}

	void setReflection(double reflection) {
		this->reflection = reflection;
	}

	virtual Position* intersection(const Position& pos1, const Position& pos2) const = 0;

	double calculCos(const Position& surface, const Position& sourceLumineuse) const;

	Position calculRayonReflechi(const Position& surface, const Position& sourceRayon) const;
};



#endif /* OBJET_H_ */
