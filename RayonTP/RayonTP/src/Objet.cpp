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

double Objet::calculCos(const Position3D& surface, const Position3D& sourceLumineuse) const{
	double scalaire = ((position.getX() - surface.getX()) * (sourceLumineuse.getX() - surface.getX())
			+ (position.getY() - surface.getY()) * (sourceLumineuse.getY() - surface.getY())
			+ (position.getZ() - surface.getZ()) * (sourceLumineuse.getZ() - surface.getZ()));

	double normeN = sqrt(pow(position.getX() - surface.getX(), 2)
			+ pow(position.getY() - surface.getY(), 2)
			+ pow(position.getZ() - surface.getZ(), 2));

	double normeR = sqrt(pow(sourceLumineuse.getX() - surface.getX(), 2)
			+ pow(sourceLumineuse.getY() - surface.getY(), 2)
			+ pow(sourceLumineuse.getZ() - surface.getZ(), 2));

	return (scalaire/(normeN*normeR));
}


Position3D Objet::calculRayonReflechi(const Position3D& surface, const Position3D& sourceRayon) const
{
	double xA = surface.getX();
	double yA = surface.getY();
	double zA = surface.getZ();

	double xB = sourceRayon.getX();
	double yB = sourceRayon.getY();
	double zB = sourceRayon.getZ();

	double xC = this->position.getX();
	double yC = this->position.getY();
	double zC = this->position.getZ();

	double normeR = sqrt(pow(xB-xA, 2) + pow(yB-yA, 2) + pow(zB-zA, 2));
	Position3D r = Position3D((xB-xA)/normeR, (yB-yA)/normeR, (zB-zA)/normeR);

	double normeN = sqrt(pow(xC-xA, 2) + pow(yC-yA, 2) + pow(zC-zA, 2));
	Position3D n = Position3D((xC-xA)/normeN, (yC-yA)/normeN, (zC-zA)/normeN);

	double x = xA + (r.getX() - 2*(r.getX()*n.getX())*n.getX());
	double y = yA + (r.getY() - 2*(r.getY()*n.getY())*n.getY());
	double z = zA + (r.getZ() - 2*(r.getZ()*n.getZ())*n.getZ());

	Position3D p = Position3D(x, y, z);

	return p;
}
