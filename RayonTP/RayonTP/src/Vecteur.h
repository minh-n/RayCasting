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
	double x;
	double y;
	double z;

public:
	Position();
	Position(double x, double y, double z);
	Position(const Position &source);

	virtual ~Position();

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	double getZ() const {
		return z;
	}

	void setZ(double z) {
		this->z = z;
	}

	void afficherPos() const{
		std::cout << " " << x << " " << y << " " << z << std::endl;;
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

	void setCouleur(const Couleur& couleur) {
		r = couleur.r;
		g = couleur.g;
		b= couleur.b;
	}

	void afficherCouleur() const{
		std::cout << " " << r << " " << g << " " << b << std::endl;
	}

	Couleur operator+ (const Couleur&) const;
};




#endif /* VECTEUR_H_ */
