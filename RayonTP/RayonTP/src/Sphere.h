/*
 * Sphere.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "Objet.h"

class Sphere : public Objet{
private :
	double radius;

public:
	Sphere() : Objet(), radius(0){};
	Sphere(Position3D pos, Couleur coul, double ref, double rad) : Objet(pos, coul, ref), radius(rad){};

	virtual ~Sphere();

	double getRadius() const {
		return radius;
	}

	void afficher() const
	{
		std::cout << "Sphere position : ";
		std::cout << position.getX()
				  << " " <<  position.getY() << " "
				  <<  position.getZ() << std::endl;
		std::cout << "Sphere couleur : ";
		std::cout <<  couleur.getR() << " "
						<<   couleur.getG() << " "
						<<   couleur.getB() << std::endl;
		std::cout << "reflec = " <<  reflection
					<< ", radius = " << radius << std::endl;
	}

	//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
	//retourne null si il n'y a pas d'intersection
	std::shared_ptr<Position3D> intersection(const Position3D& posSource, const Position3D& posDir) const;

	//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
	double calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const;

	//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
	Position3D calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const;
};


#endif /* SPHERE_H_ */
