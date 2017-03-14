package com.eluke.checkers;

public class Coordinate {
	private final int row;
	private final int col;
	public int getRow() {
		return row;
	}
	public int getCol() {
		return col;
	}
	@Override
	public String toString() {
		return "(" + row + ", " + col + ")";
	}
	public Coordinate(int row, int col) {
		this.row = row;
		this.col = col;
	}
	
	public static Coordinate extending(Coordinate c1, Coordinate c2) {
		int newRow = (c2.getRow()-c1.getRow()) + c2.getRow(); 
		int newCol = (c2.getCol()-c1.getCol()) + c2.getCol(); 
		return new Coordinate(newRow, newCol);
	}
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + col;
		result = prime * result + row;
		return result;
	}
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Coordinate other = (Coordinate) obj;
		if (col != other.col)
			return false;
		if (row != other.row)
			return false;
		return true;
	}
	
}
