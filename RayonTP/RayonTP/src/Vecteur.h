/*
 * Vecteur.h
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef VECTEUR_H_
#define VECTEUR_H_
#include <iostream>

class Position {
private:
	int x;
	int y;
	int z;

public:
	Position();
	Position(int x, int y, int z);
	Position(const Position &source);

	virtual ~Position();

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	int getZ() const {
		return z;
	}

	void setZ(int z) {
		this->z = z;
	}

	void afficherPos() const{
		std::cout << " " << x << " " << y << " " << z;
	}

	Position operator* (const double&) const;

	Position operator* (const Position&) const;

	Position operator- (const Position&) const;

	Position operator+ (const Position&) const;

	Position& operator-= (const Position&);

	Position& operator+= (const Position&);

	Position& operator= (const Position&);

	bool operator== (const Position&)const;

	double length() const;
	double length2() const;
	double dot(const Position&) const;

	Position cross(const Position&) const;
	Position& normalize();
	Position project(const Position&) const;








};



class Couleur {
private:
	int r;
	int g;
	int b;

public:
	Couleur();
	Couleur(int r, int g, int b);
	Couleur(const Couleur &source);

	virtual ~Couleur();

	int getB() const {
		return b;
	}

	void setB(int b) {
		this->b = b;
	}

	int getG() const {
		return g;
	}

	void setG(int g) {
		this->g = g;
	}

	int getR() const {
		return r;
	}

	void setR(int r) {
		this->r = r;
	}


	void afficherCouleur() const{
		std::cout << " " << r << " " << g << " " << b;
	}
};
#endif /* VECTEUR_H_ */
