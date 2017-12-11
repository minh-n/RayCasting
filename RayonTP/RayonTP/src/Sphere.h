/*
 * Sphere.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "Objet.h"
#include <iostream>

class Sphere : public Objet{

private :
	double reflection;
	double radius;
public:
	Sphere();
	Sphere(Position pos, Couleur coul, double ref, double rad) : Objet(pos, coul), reflection(ref), radius(rad){};

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

	void afficher() const
	{
		std::cout << "Sphere position : ";

		std::cout << Objet::getPosition().getX()
				  << " " <<  Objet::getPosition().getY() << " "
				  <<  Objet::getPosition().getZ() << std::endl;

		std::cout << "Sphere couleur : ";

		std::cout <<  Objet::getCouleur().getR() << " "
						<<   Objet::getCouleur().getG() << " "
						<<   Objet::getCouleur().getB() << std::endl;


		std::cout << "reflec = " <<  getReflection()
					<< ", radius = " << getRadius() << "\n\n" << std::endl;
	}
};


#endif /* SPHERE_H_ */
