/*
 * Objet.h
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#ifndef OBJET_H_
#define OBJET_H_
#include "Vecteur.h"


class Objet {
protected :
	Position3D position;
	Couleur couleur;
	double reflection;

public:

	Objet() : reflection(0){};

	Objet(Position3D pos, Couleur coul, double ref) : position(pos), couleur(coul), reflection(ref){};

	virtual ~Objet();

	virtual void afficher() const = 0;

	const Position3D& getPosition() const {
		return position;
	}

	void setPosition(const Position3D& pos) {
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

	virtual Position3D* intersection(const Position3D& posSource, const Position3D& posDir) const = 0;
	double calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const;
	Position3D calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const;
};



#endif /* OBJET_H_ */
