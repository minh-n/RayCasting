/*
 * Sphere.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef SPHERE_H_
#define SPHERE_H_
#include "Objet.h"
#include "Scene.h"
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

		std::cout << position.getX()
				  << " " <<  position.getY() << " "
				  <<  position.getZ() << std::endl;

		std::cout << "Sphere couleur : ";

		std::cout <<  couleur.getR() << " "
						<<   couleur.getG() << " "
						<<   couleur.getB() << std::endl;


		std::cout << "reflec = " <<  reflection
					<< ", radius = " << radius << "\n\n" << std::endl;
	}

	Position* intersection(const Position& pos1, const Position& pos2) const;


};


#endif /* SPHERE_H_ */
