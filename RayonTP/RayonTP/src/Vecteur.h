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

	double getY() const {
		return y;
	}

	double getZ() const {
		return z;
	}

	static double norme(const Position3D& pos1, const Position3D& pos2);
	static double scalaire(const Position3D& pos1, const Position3D& pos2);
	static Position3D vectUnitaire(const Position3D& pos1, const Position3D& pos2);
	static Position3D produitVectoriel(const Position3D& pos1, const Position3D& pos2);

	//retourne la position oppose
	void oppose();

	Position3D operator* (const double&) const;
	Position3D operator* (const Position3D& p) const;
	Position3D operator- (const Position3D& p) const;
	Position3D operator+ (const Position3D& p) const;
	Position3D& operator-= (const Position3D& p);
	Position3D& operator+= (const Position3D& p);
	Position3D& operator= (const Position3D& p);

	friend std::ostream& operator<<(std::ostream& os, const Position3D& pos);
};

bool operator==(Position3D const& pos1, Position3D const& pos2);

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

	int getG() const {
		return g;
	}

	int getR() const {
		return r;
	}

	//retourne la couleur d'une surface sans prendre en compte la reflexion
	static Couleur couleurSansReflexion(const double& cosAlpha, const Couleur& intersection, const Couleur& source);

	Couleur operator- (const Couleur& c) const;
	Couleur operator+ (const Couleur& c) const;
	Couleur& operator-= (const Couleur& c);
	Couleur& operator+= (const Couleur& c);
	Couleur& operator= (const Couleur& c);

	friend std::ostream& operator<<(std::ostream& os, const Couleur& c);
};


#endif /* VECTEUR_H_ */
