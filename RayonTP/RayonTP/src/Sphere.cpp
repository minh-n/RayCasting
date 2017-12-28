/*
 * Sphere.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Sphere.h"

Sphere::~Sphere() {

}


Position3D* Sphere::intersection(const Position3D& posSource, const Position3D& posDir) const
{
//	std::cout << "Calcul direction" << std::endl;
	Position3D dir = posDir - posSource;

	double xRayon = posSource.getX();
	double yRayon = posSource.getY();
	double zRayon = posSource.getZ();

	double xDir = dir.getX();
	double yDir = dir.getY();
	double zDir = dir.getZ();

	double xCentre = this->position.getX();
	double yCentre = this->position.getY();
	double zCentre = this->position.getZ();

//	std::cout << "Calcul coef" << std::endl;
	double a = pow(xDir, 2) + pow(yDir, 2) + pow(zDir, 2);
	double b = 2*(xDir*(xRayon - xCentre) + yDir*(yRayon - yCentre) + zDir*(zRayon - zCentre));
	double c = pow(xRayon-xCentre, 2) + pow(yRayon-yCentre, 2) + pow(zRayon-zCentre, 2) - pow(this->radius, 2);

//	std::cout << "Calcul delta" << std::endl;
	double delta = b*b - 4*a*c;
	double r1, r2, t;

	if (delta > 0) {
		r1 = (-b - sqrt(delta))/(2*a);
		r2 = (-b + sqrt(delta))/(2*a);

		if(r1 > 0)
		{
			if(r2 > 0) t = (r1 < r2) ? r1 : r2;
		}
		else if(r2 > 0)
		{
			t = r2;
		}
		else {
			return NULL;
		}
	}
	else if (delta == 0 ) {
		r1 = -b/(2*a);

		if(r1 > 0) {
			t = r1;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}

	return new Position3D(xRayon + t*xDir, yRayon + t*yDir, zRayon + t*zDir);
}
