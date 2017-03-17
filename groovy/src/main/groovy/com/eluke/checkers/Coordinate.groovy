package com.eluke.checkers

import groovy.transform.Immutable

@Immutable
class Coordinate {
	int row
	int col
	
	public static Coordinate extending(Coordinate c1, Coordinate c2) {
		int newRow = (c2.getRow()-c1.getRow()) + c2.getRow();
		int newCol = (c2.getCol()-c1.getCol()) + c2.getCol();
		return new Coordinate(newRow, newCol);
	}
}
