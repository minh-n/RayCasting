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
Position::Position(int x, int y, int z) : x(x), y(y), z(z) {
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

Position Position::operator* (const double& xn) const {
	return Position(xn*x, xn*y, xn*z);
}

Position Position::operator* (const Position& v) const {
	return Position(v.x*x, v.y*y, v.z*z);
}

Position Position::operator- (const Position& v) const {
	return Position(x - v.x, y - v.y, z - v.z);
}

Position Position::operator+ (const Position& v) const {
	return Position(x + v.x, y + v.y, z + v.z);
}

Position& Position::operator-= (const Position& v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Position& Position::operator+= (const Position& v){
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Position& Position::operator = (const Position& v){
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}


double Position::dot(const Position& v) const {
	return v.x*x + v.y * y + v.z * z;
}

Position Position::cross(const Position& v) const{
	double xn = y*v.z - z*v.y;
	double yn = z*v.x - x*v.z;
	double zn = x*v.y - y*v.x;
	return Position(xn, yn, zn);
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


