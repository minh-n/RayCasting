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

class Pixel {
private:
	Position3D position;
	Couleur couleur;

public:
	Pixel();
	Pixel(Position3D p, Couleur c);

	~Pixel();

	const Couleur& getCouleur() const {
		return couleur;
	}

	void setCouleur(const Couleur& couleur) {
		this->couleur = couleur;
	}

	const Position3D& getPosition() const {
		return position;
	}

	void setPosition(const Position3D& position) {
		this->position = position;
	}

	Pixel& operator=(Pixel const& p);
};



class Ecran {
friend class Scene;
private:
	Position3D tlc;
	Position3D trc;
	Position3D blc;
	Position3D brc;

	int resHorizontale;
	int resVerticale;

	std::vector<std::vector<Pixel>> pixels;

public:
	Ecran();

	virtual ~Ecran();

	const Position3D& getBlc() const {
		return blc;
	}

	const Position3D& getTlc() const {
		return tlc;
	}

	const Position3D& getTrc() const {
		return trc;
	}

	const Position3D& getBrc() const {
		return brc;
	}

	int getResHorizontale() const {
		return resHorizontale;
	}

	int getResVerticale() const {
		return resVerticale;
	}

	const std::vector<std::vector<Pixel> >& getPixels() const {
		return pixels;
	}

	void setBlc(const Position3D& blc) {
		this->blc = blc;
	}

	void setTlc(const Position3D& tlc) {
		this->tlc = tlc;
	}

	void setTrc(const Position3D& trc) {
		this->trc = trc;
	}

	void setBrc(const Position3D& brc) {
		this->brc = brc;
	}

	void setResHorizontale(int resHor) {
		this->resHorizontale = resHor;
	}

	//calcul du quatrieme point a partir des trois autres
	void creationBrc();

	//calcul la resolution verticale
	void calculResVer(const Couleur bgCouleur);

	//initialise le tableau de pixel et fait coorespondre la couleur de chaque pixel a la couleur de fond
	void initPixels(const Couleur bgCouleur);
};


#endif /* ECRAN_H_ */
