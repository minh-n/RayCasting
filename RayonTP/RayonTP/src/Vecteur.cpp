/*
 * Vecteur.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#include "Vecteur.h"



/**
 * POSITION
 */
Position::Position(){
	x = 0;
	y = 0;
	z = 0;
	// TODO Auto-generated constructor stub

}
Position::Position(double x, double y, double z) : x(x), y(y), z(z) {
	// TODO Auto-generated constructor stub

}

Position::Position(const Position &source){
	x = source.x;
	y = source.y;
	z = source.z;
	// TODO Auto-generated constructor stub

}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

/**
 * SURCHARGE OPERATEURS
 */

Position Position::operator* (const double& i) const {
	return Position(i*x, i*y, i*z);
}

Position Position::operator* (const Position& p) const {
	return Position(p.x*x, p.y*y, p.z*z);
}

Position Position::operator- (const Position& p) const {
	return Position(x - p.x, y - p.y, z - p.z);
}

Position Position::operator+ (const Position& p) const {
	return Position(x + p.x, y + p.y, z + p.z);
}

Position& Position::operator-= (const Position& p){
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

Position& Position::operator+= (const Position& p){
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

Position& Position::operator = (const Position& p){
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

double Position::dot(const Position& p) const {
	return p.x*x + p.y * y + p.z * z;
}

Position Position::cross(const Position& p) const{
	double xn = y*p.z - z*p.y;
	double yn = z*p.x - x*p.z;
	double zn = x*p.y - y*p.x;
	return Position(xn, yn, zn);
}


Couleur Couleur::operator+ (const Couleur& c) const
{
	int red = r + c.r;
	if(red > 255){red = 255;}
	int green = g + c.g;
	if(green > 255){green = 255;}
	int blue = b + c.b;
	if(blue > 255){blue = 255;}

	return Couleur(red, green, blue);
}










/**
 * COULEUR
 */

Couleur::Couleur(){
	r = 0;
	g = 0;
	b = 0;
	// TODO Auto-generated constructor stub

}
Couleur::Couleur(int r, int g, int b) : r(r), g(g), b(b) {
	// TODO Auto-generated constructor stub

}

Couleur::Couleur(const Couleur &source){
	r = source.r;
	g = source.g;
	b = source.b;
	// TODO Auto-generated constructor stub

}

Couleur::~Couleur() {
	// TODO Auto-generated destructor stub
}


