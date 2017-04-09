/*
 * Types.h
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#ifndef TYPES_H_
#define TYPES_H_

#define BLACK 0
#define RED 1
typedef char color_t;


typedef struct {
	char row;
	char col;
} Coordinate;

#define COORD(r,c) (Coordinate){.row = (r), .col = (c)}

#define EXTENDING_COORDINATE(p1, p2) \
		COORD(((p2.row-p1.row) + p2.row), ((p2.col-p1.col) + p2.col));

#define EQUAL_COORDS(c1, c2) \
		((c1).row == (c2).row && (c1).col == (c2).col)


#endif /* TYPES_H_ */
