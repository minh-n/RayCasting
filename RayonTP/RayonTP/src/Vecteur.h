/*
 * Vecteur.h
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef VECTEUR_H_
#define VECTEUR_H_
#include <iostream>
#include <cmath>

class Position3D {
private:
	double x;
	double y;
	double z;

public:
	Position3D();
	Position3D(double x, double y, double z);
	Position3D(const Position3D &position);

	~Position3D();

	double getX() const {
		return x;
	}

	void setX(const double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(const double y) {
		this->y = y;
	}

	double getZ() const {
		return z;
	}

	void setZ(const double z) {
		this->z = z;
	}

	void afficherPos() const{
		std::cout << "X = " << x << ", Y = " << y << ", Z =" << z << std::endl;;
	}

	double norme(const Position3D& p) const;

	Position3D operator* (const double&) const;

	Position3D operator* (const Position3D& p) const;

	Position3D operator- (const Position3D& p) const;

	Position3D operator+ (const Position3D& p) const;

	Position3D& operator-= (const Position3D& p);

	Position3D& operator+= (const Position3D& p);

	Position3D& operator= (const Position3D& p);
};


class Couleur {
private:
	int r;
	int g;
	int b;

public:
	Couleur();
	Couleur(int r, int g, int b);
	Couleur(const Couleur &couleur);

	~Couleur();

	int getB() const {
		return b;
	}

	void setB(const int b) {
		this->b = b;
	}

	int getG() const {
		return g;
	}

	void setG(const int g) {
		this->g = g;
	}

	int getR() const {
		return r;
	}

	void setR(const int r) {
		this->r = r;
	}

	void afficherCouleur() const{
		std::cout << "R = " << r << ", G = " << g << ", B = " << b << std::endl;
	}

	Couleur operator- (const Couleur& c) const;

	Couleur operator+ (const Couleur& c) const;

	Couleur& operator-= (const Couleur& c);

	Couleur& operator+= (const Couleur& c);

	Couleur& operator= (const Couleur& c);
};


#endif /* VECTEUR_H_ */
