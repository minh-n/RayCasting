/*
 * Ecran.h
 *
 *  Created on: Dec 11, 2017
 *      Author: hien-minh.nguyen
 */

#ifndef ECRAN_H_
#define ECRAN_H_
#include "Vecteur.h"

/**
 * ECRAN
 */

class Ecran {

private:

	Position tlc;
	Position trc;
	Position blc;
	Position brc;

	int resolution;

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

	int getResolution() const {
		return resolution;
	}

	void setResolution(int resolution) {
		this->resolution = resolution;
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

	void creationBrc()
	{
		int x = trc.getX() - tlc.getX() + blc.getX();
		int y = trc.getY() - tlc.getY() + blc.getY();
		int z = trc.getZ() - tlc.getZ() + blc.getZ();
		brc.setX(x);
		brc.setY(y);
		brc.setZ(z);



	}
};

#endif /* ECRAN_H_ */
