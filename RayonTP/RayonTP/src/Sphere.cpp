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


Position* Sphere::intersection(const Position& pos1, const Position& pos2) const
{
	bool contact = false;
	Position* surface = NULL;

	double xA = pos1.getX();
	double yA = pos1.getY();
	double zA = pos1.getZ();

	double xB = pos2.getX();
	double yB = pos2.getY();
	double zB = pos2.getZ();

	double xC = this->position.getX();
	double yC = this->position.getY();
	double zC = this->position.getZ();

	double r = this->radius;

	double a = (xB-xA)*(xB-xA) + (yB-yA)*(yB-yA) + (zB-zA)*(zB-zA);
	double b = 2*((xB-xA)*(xA-xC) + (yB-yA)*(yA-yC) + (zB-zA)*(zA-zC));
	double c = (xA-xC)*(xA-xC) + (yA-yC)*(yA-yC) + (zA-zC)*(zA-zC) - (r*r);

	double delta = b*b - 4*a*c;

	double r1, r2;
	double t;

	if (delta > 0){

		r1 = (-b - sqrt(delta))/(2*a);
		r2 = (-b + sqrt(delta))/(2*a);

		if(r1 < r2) {
			t = r1;
		}
		else {
			t = r2;
		}

		contact = true;
	}
	else if (delta == 0 ) {

		r1 = b/(2*a);
		t = r1;

		contact = true;
	}

	if(contact){
		surface = new Position(xA+t*(xB-xA), yA+t*(yB-yA), zA+t*(zB-zA));
	}

	return surface;
}
