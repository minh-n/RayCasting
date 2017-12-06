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
	double reflection;
	double radius;
public:
	Sphere();
	virtual ~Sphere();


	double getRadius() const {
		return radius;
	}

	void setRadius(double radius) {
		this->radius = radius;
	}

	double getReflection() const {
		return reflection;
	}

	void setReflection(double reflection) {
		this->reflection = reflection;
	}
};

#endif /* SPHERE_H_ */
