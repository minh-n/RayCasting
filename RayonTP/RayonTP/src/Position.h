/*
 * Position.h
 *
 *  Created on: Nov 29, 2017
 *      Author: hnguye5
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {


private:
	int x;
	int y;
	int z;

public:
	Position();
	Position(int x, int y, int z);
	virtual ~Position();
};

#endif /* POSITION_H_ */
