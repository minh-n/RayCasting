/*
 * Sphere.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Sphere.h"

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}


Position3D* Sphere::intersection(const Position3D& pos1, const Position3D& pos2) const
{
	Position3D* surface = NULL;

	double xA = pos1.getX();
	double yA = pos1.getY();
	double zA = pos1.getZ();

	double xB = pos2.getX();
	double yB = pos2.getY();
	double zB = pos2.getZ();

	double xC = this->position.getX();
	double yC = this->position.getY();
	double zC = this->position.getZ();

	double a = (xB-xA)*(xB-xA) + (yB-yA)*(yB-yA) + (zB-zA)*(zB-zA);
	double b = 2*((xB-xA)*(xA-xC) + (yB-yA)*(yA-yC) + (zB-zA)*(zA-zC));
	double c = (xA-xC)*(xA-xC) + (yA-yC)*(yA-yC) + (zA-zC)*(zA-zC) - (radius*radius);

	double delta = b*b - 4*a*c;

	double r1, r2;

	if (delta > 0){

		r1 = (-b - sqrt(delta))/(2*a);
		r2 = (-b + sqrt(delta))/(2*a);

		Position3D* racine1 = new Position3D(xA+r1*(xB-xA), yA+r1*(yB-yA), zA+r1*(zB-zA));
		Position3D* racine2 = new Position3D(xA+r2*(xB-xA), yA+r2*(yB-yA), zA+r2*(zB-zA));

		double distance1 = sqrt(pow(racine1->getX() - pos1.getX(), 2)
				+ pow(racine1->getY() - pos1.getY(), 2)
				+ pow(racine1->getZ() - pos1.getZ(), 2));
		double distance2 = sqrt(pow(racine2->getX() - pos1.getX(), 2)
				+ pow(racine2->getY() - pos1.getY(), 2)
				+ pow(racine2->getZ() - pos1.getZ(), 2));

		surface = (distance1 < distance2) ? racine1 : racine2;

		delete racine1;
		delete racine2;
	}
	else if (delta == 0 ) {

		r1 = b/(2*a);

		surface = new Position3D(xA+r1*(xB-xA), yA+r1*(yB-yA), zA+r1*(zB-zA));
	}

	return surface;
}
