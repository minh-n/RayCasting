/*
 * Objet.cpp
 *
 *  Created on: 30 déc. 2017
 *      Author: Adrien
 */

#include "Objet.h"

Objet::Objet() : reflection(0){

}

Objet::Objet(Couleur coul, double ref) : couleur(coul), reflection(ref){

}

Objet::Objet(Position3D pos, Couleur coul, double ref) : position(pos), couleur(coul), reflection(ref){

}

Objet::~Objet(){

}
