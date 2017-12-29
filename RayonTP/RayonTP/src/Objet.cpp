/*
 * Objet.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: adrien.lavillonniere
 */

#include "Objet.h"

/**
 * OBJET
 */

Objet::~Objet(){

}

double Objet::calculCosinusAlpha(const Position3D& surface, const Position3D& sourceLumineuse) const{

	if(surface == sourceLumineuse) return 1;

	Position3D vectNormale = surface - this->position;
	Position3D vectSource = sourceLumineuse - this->position;

	double scalaire = Position3D::scalaire(vectNormale, vectSource);

	double normeNormale = Position3D::norme(this->position, surface);
	double normeVectSource = Position3D::norme(surface, sourceLumineuse);

	return (scalaire/(normeNormale*normeVectSource));
}

//surface et sourceRayon doivent etre different !
Position3D Objet::calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const{

	Position3D vectRayon = Position3D::vectUnitaire(sourceRayon, surface);
	Position3D vectNormal = Position3D::vectUnitaire(this->position, surface);

	Position3D vectRefl = vectRayon - vectNormal*Position3D::scalaire(vectRayon, vectNormal)*2;

	return vectRefl + surface;

//	double x = -(surface.getX() + 2*(vectRayon.getX() - (vectRayon.getX()*vectNormal.getX())*vectNormal.getX()));
//	double y = -(surface.getY() + 2*(vectRayon.getY() - (vectRayon.getY()*vectNormal.getY())*vectNormal.getY()));
//	double z = -(surface.getZ() + 2*(vectRayon.getZ() - (vectRayon.getZ()*vectNormal.getZ())*vectNormal.getZ()));

//	return Position3D(x, y, z);
}
