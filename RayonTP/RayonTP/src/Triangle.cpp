/*
 * Triangle.cpp
 *
 *  Created on: 30 déc. 2017
 *      Author: Adrien
 */

#include "Triangle.h"

Triangle::~Triangle() {

}

//verifie si l'objet possede un point d'intersection avec la demi-droite represente par un point d'origine et un vecteur directeur
//retourne null si il n'y a pas d'intersection
std::shared_ptr<Position3D> Triangle::intersection(const Position3D& posSource, const Position3D& posDir) const{
	return nullptr;
}


//calcul la valeur du cos entre la normale par rapport au point de surface et la position de la source lumineuse
double Triangle::calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const{
	return 0.0;
}


//renvoie un point present sur la demi droite ayant comme origine le point de surface et comme vecteur directeur le rayon reflechi
Position3D Triangle::calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const{
	return Position3D();
}


