/*
 * Objet.h
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#ifndef OBJET_H_
#define OBJET_H_
#include "Vecteur.h"
#include <memory>

class Objet {
protected :
	Position3D position;
	Couleur couleur;
	double reflection;

public:

	Objet();

	Objet(Position3D pos, Couleur coul, double ref);

	virtual ~Objet();

	const Position3D& getPosition() const {
		return position;
	}

	const Couleur& getCouleur() const {
		return couleur;
	}

	double getReflection() const {
		return reflection;
	}

	virtual void afficher() const = 0;

	//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
	//retourne null si il n'y a pas d'intersection
	virtual std::shared_ptr<Position3D> intersection(const Position3D& posSource, const Position3D& posDir) const = 0;

	//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
	virtual double calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const = 0;

	//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
	virtual Position3D calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const = 0;
};



#endif /* OBJET_H_ */
