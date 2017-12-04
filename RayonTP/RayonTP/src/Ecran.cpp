/*
 * Ecran.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#include "Ecran.h"


Ecran::Ecran() {
	// TODO Auto-generated constructor stub
}

Ecran::~Ecran() {
	// TODO Auto-generated destructor stub
}

Position Ecran::getTlc() const
{
	return tlc;
}

Position Ecran::getTrc() const
{
	return trc;
}

Position Ecran::getBlc() const
{
	return blc;
}

int Ecran::getResolution() const
{
	return resolution;
}

void Ecran::setTlc(Position p) { tlc = p;}
void Ecran::setTrc(Position p) { trc = p;}
void Ecran::setBlc(Position p) { blc = p;}
void Ecran::setResolution(int r) { resolution = r;}

