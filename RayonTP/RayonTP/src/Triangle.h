/*
 * Triangle.h
 *
 *  Created on: 30 déc. 2017
 *      Author: Adrien
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Objet.h"

class Triangle : public Objet{
private :
	Position3D pointA;
	Position3D pointB;
	Position3D pointC;

public:
	Triangle() : Objet(){};

	Triangle(Couleur coul, double ref, Position3D ptA, Position3D ptB, Position3D ptC) : Objet(coul, ref), pointA(ptA), pointB(ptB), pointC(ptC){};

	virtual ~Triangle();

	void afficher() const
	{
		std::cout << "Triangle position A: " << pointA;
		std::cout << "Triangle position B: " << pointB;
		std::cout << "Triangle position C: " << pointC;
		std::cout << "Triangle couleur : " << couleur;
		std::cout << "reflec = " <<  reflection << std::endl;
	};

	//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
	//retourne null si il n'y a pas d'intersection
	std::shared_ptr<Position3D> intersection(const Position3D& posSource, const Position3D& posDir) const;

	//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
	double calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const;

	//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
	Position3D calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const;

	//renvoie un point d'intersection entre la droite posSource-posDir et le plan ABC
	std::shared_ptr<Position3D> intersectionPlan(const Position3D& posSource, const Position3D& posDir) const;

	//renvoie un vecteur normal au plan ABC et passant par le point posSource
	Position3D vectNormal(const Position3D& surface) const;
};




#endif /* TRIANGLE_H_ */
