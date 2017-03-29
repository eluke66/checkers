/*
 * CheckerTypes.h
 *
 *  Created on: Mar 27, 2017
 *      Author: luke
 */

#ifndef CHECKERTYPES_H_
#define CHECKERTYPES_H_

#include <list>
#include <memory>
class Move;

typedef std::shared_ptr<Move> MoveType;
typedef std::list<MoveType> Moves;

#endif /* CHECKERTYPES_H_ */
