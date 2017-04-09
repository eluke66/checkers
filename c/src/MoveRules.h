/*
 * MoveRules.h
 *
 *  Created on: Mar 31, 2017
 *      Author: luke
 */

#ifndef MOVERULES_H_
#define MOVERULES_H_


struct Piece;
struct Board;
extern Move addSimpleMove(Board * board, Piece *piece, Coordinate from, Coordinate to);
extern Move addJumpMove(Board *board, Piece *piece, Coordinate from, Coordinate to);
extern Move addMultiJumpMove(Board *board, Piece *piece, Coordinate from, Coordinate to, Move *previousMove);
extern Moves getMovesForColor(color_t color, Board *board);

#endif /* MOVERULES_H_ */
