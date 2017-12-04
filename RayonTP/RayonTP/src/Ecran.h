/*
 * Ecran.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef ECRAN_H_
#define ECRAN_H_
#include "Position.h"

class Ecran {

private:

	Position tlc;
	Position trc;
	Position blc;
	int resolution;

public:
	Ecran();
	virtual ~Ecran();

	int getResolution() const;
	Position getTlc() const;
	Position getTrc() const;
	Position getBlc() const;

	void setResolution(int r);
	void setTlc(Position p);
	void setTrc(Position p);
	void setBlc(Position p);
};

#endif /* ECRAN_H_ */
