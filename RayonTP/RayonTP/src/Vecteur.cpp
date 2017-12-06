/*
 * Vecteur.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#include "Vecteur.h"

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


