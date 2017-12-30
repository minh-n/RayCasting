/*
 * Vecteur.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: hien-minh.nguyen
 */

#include "Vecteur.h"


/**
 * POSITION3D
 */

Position3D::Position3D() : x(0), y(0), z(0){

}

Position3D::Position3D(double x, double y, double z) : x(x), y(y), z(z){

}

Position3D::Position3D(const Position3D &position){
	this->x = position.x;
	this->y = position.y;
	this->z = position.z;
}

Position3D::~Position3D() {

}

double Position3D::norme(const Position3D& pos1, const Position3D& pos2){
	return sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2));
}

double Position3D::scalaire(const Position3D& pos1, const Position3D& pos2){
	return (pos1.x*pos2.x + pos1.y*pos2.y + pos1.z*pos2.z);
}

Position3D Position3D::vectUnitaire(const Position3D& pos1, const Position3D& pos2){
	double n = Position3D::norme(pos1, pos2);
	Position3D vectUnitaire;

	if(n != 0)
	{
		vectUnitaire = (pos2 - pos1)*(1/n);
	}

	return vectUnitaire;
}

//retourne la position oppose
void Position3D::oppose(){
	this->x = -x;
	this->y = -y;
	this->z = -z;
}


/**
 * SURCHARGE OPERATEURS
 */

Position3D Position3D::operator* (const double& i) const {
	return Position3D(i*this->x, i*this->y, i*this->z);
}

Position3D Position3D::operator* (const Position3D& p) const {
	return Position3D(p.x*this->x, p.y*this->y, p.z*this->z);
}

Position3D Position3D::operator- (const Position3D& p) const {
	return Position3D(this->x - p.x, this->y - p.y, this->z - p.z);
}

Position3D Position3D::operator+ (const Position3D& p) const {
	return Position3D(this->x + p.x, this->y + p.y, this->z + p.z);
}

Position3D& Position3D::operator-= (const Position3D& p){
	this->x -= p.x;
	this->y -= p.y;
	this->z -= p.z;
	return *this;
}

Position3D& Position3D::operator+= (const Position3D& p){
	this->x += p.x;
	this->y += p.y;
	this->z += p.z;
	return *this;
}

Position3D& Position3D::operator = (const Position3D& p){
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	return *this;
}

bool operator==(Position3D const& pos1, Position3D const& pos2){
	bool comparaison = ((pos1.getX() == pos2.getX()) && (pos1.getY() == pos2.getY()) && (pos1.getZ() == pos2.getZ())) ? true : false;
	return comparaison;
}

std::ostream& operator<<(std::ostream& os, const Position3D& pos){
	os << "X = " << pos.getX() << ", Y = " << pos.getY() << ", Z =" << pos.getZ() << std::endl;
	return os;
}

/**
 * COULEUR
 */

Couleur::Couleur() : r(0), g(0), b(0){

}

Couleur::Couleur(int r, int g, int b){
	if(r > 255) r = 255;
	if(g > 255) g = 255;
	if(b > 255) b = 255;

	if(r < 0) r = 0;
	if(g < 0) g = 0;
	if(b < 0) b = 0;

	this->r = r;
	this->g = g;
	this->b = b;
}

Couleur::Couleur(const Couleur &couleur){
	this->r = couleur.r;
	this->g = couleur.g;
	this->b = couleur.b;
}

Couleur::~Couleur() {

}

//retourne la couleur d'une surface sans prendre en compte la reflexion
Couleur Couleur::couleurSansReflexion(const double& cosAlpha, const Couleur& intersection, const Couleur& source) {
	int red = ((int) (cosAlpha*((intersection.r*source.r)/255)));
	int green = ((int) (cosAlpha*((intersection.g*source.g)/255)));
	int blue = ((int) (cosAlpha*((intersection.b*source.b)/255)));

	return Couleur(red, green, blue);
}


/**
 * SURCHARGE OPERATEURS
 */

Couleur Couleur::operator- (const Couleur& c) const{
	int red = this->r - c.r;
	if(red < 0){red = 0;}
	int green =  this->g - c.g;
	if(green < 0){green = 0;}
	int blue =  this->b - c.b;
	if(blue < 0){blue = 0;}

	return Couleur(red, green, blue);
}

Couleur Couleur::operator+ (const Couleur& c) const
{
	int red = this->r + c.r;
	if(red > 255){red = 255;}
	int green =  this->g + c.g;
	if(green > 255){green = 255;}
	int blue =  this->b + c.b;
	if(blue > 255){blue = 255;}

	return Couleur(red, green, blue);
}

Couleur& Couleur::operator-= (const Couleur& c){
	*this - c;
	return *this;
}

Couleur& Couleur::operator+= (const Couleur& c){
	*this + c;
	return *this;
}

Couleur& Couleur::operator= (const Couleur& c){
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Couleur& c){
	os << "R = " << c.getR() << ", G = " << c.getG() << ", B = " << c.getB() << std::endl;
	return os;
}
