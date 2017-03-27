/*
 * Coordinate.h
 *
 *  Created on: Mar 19, 2017
 *      Author: luke
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <boost/lexical_cast.hpp>
#include <string>

class Coordinate{
public:
	Coordinate(unsigned row, unsigned col) :
		row(row), col(col) {

	}
	Coordinate(const Coordinate &c) :
		row(c.row), col(c.col) {

	}
	const unsigned getCol() const {
		return col;
	}

	const unsigned getRow() const {
		return row;
	}
	operator std::string() const
	{
		return "(" + boost::lexical_cast<std::string>(row) + ", " + boost::lexical_cast<std::string>(col) + ")";  //  Or whatever...
	}
	bool operator==(const Coordinate &other) const {
		return row == other.row && col == other.col;
	}

	static Coordinate extending(const Coordinate &p1, const Coordinate &p2);
private:
	const unsigned row;
	const unsigned col;
};

inline Coordinate Coordinate::extending(const Coordinate& p1,
		const Coordinate& p2) {
	unsigned newRow = (p2.getRow()-p1.getRow()) + p2.getRow();
	unsigned newCol = (p2.getCol()-p1.getCol()) + p2.getCol();
	return Coordinate(newRow, newCol);
}

#endif /* COORDINATE_H_ */
