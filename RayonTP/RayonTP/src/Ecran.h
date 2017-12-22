/*
 * Ecran.h
 *
 *  Created on: Dec 11, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef ECRAN_H_
#define ECRAN_H_
#include "Vecteur.h"
#include <vector>
#include <cmath>
#include <algorithm>    // std::swap

/**
 * PIXEL
 */
class Pixel
{
private:
	Position position;
	Couleur couleur;
public:
        Pixel();
        Pixel(Pixel const& p)
        {
        	position = p.position;
        	couleur = p.couleur;
        }

        Pixel(Position p, Couleur c);

        ~Pixel();


    Pixel& operator=(Pixel const& p)
    {


    	position = p.position;
    	couleur = p.couleur;
    	return *this;
    }


	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}

	const Position& getPosition() const {
		return position;
	}

	void setPosition(const Position& position) {
		this->position = position;
	}
};


/**
 * ECRAN
 */


class Ecran {

private:

	Position tlc;
	Position trc;
	Position blc;
	Position brc;

	int resHorizontale;
	int resVerticale;
/**
 * TODO : tableau
 */

	std::vector<std::vector<Pixel>> pixels;



public:
	Ecran(int res);
	Ecran();

	virtual ~Ecran();

	const Position& getBlc() const {
		return blc;
	}

	void setBlc(const Position& blc) {
		this->blc = blc;
	}

	int getResHorizontale() const {
		return resHorizontale;
	}

	void setResHorizontale(int resHor) {
		this->resHorizontale = resHor;
	}

	const Position& getTlc() const {
		return tlc;
	}

	void setTlc(const Position& tlc) {
		this->tlc = tlc;
	}

	const Position& getTrc() const {
		return trc;
	}

	void setTrc(const Position& trc) {
		this->trc = trc;
	}

	const Position& getBrc() const {
		return brc;
	}

	void setBrc(const Position& brc) {
		this->brc = brc;
	}

	void creationBrc() //calcul du quatrieme point a partir des trois autres
	{
		int x = trc.getX() - tlc.getX() + blc.getX();
		int y = trc.getY() - tlc.getY() + blc.getY();
		int z = trc.getZ() - tlc.getZ() + blc.getZ();
		brc.setX(x);
		brc.setY(y);
		brc.setZ(z);
	}

	void calculResVer() //calcul resolution verticale
	{

		int longueurHorizontale = sqrt(
				((brc.getX() - blc.getX())^2)
				+ ((brc.getY() - blc.getY())^2)
				+ ((brc.getZ() - blc.getZ())^2));

		int longueurVerticale = sqrt(
				((tlc.getX() - blc.getX())^2)
				+ ((tlc.getY() - blc.getY())^2)
				+ ((tlc.getZ() - blc.getZ())^2));

		resVerticale = (resHorizontale/longueurHorizontale)*longueurVerticale;
		
		initPixels(); //initialisation du tableau de pixels

	}

	void initPixels();

	int getResVerticale() const {
		return resVerticale;
	}

	void setResVerticale(int resVerticale) {
		this->resVerticale = resVerticale;
	}

	const std::vector<std::vector<Pixel> >& getPixels() const {
		return pixels;
	}

	void setPixels(const std::vector<std::vector<Pixel> >& pixels) {
		this->pixels = pixels;
	}
};







#endif /* ECRAN_H_ */
