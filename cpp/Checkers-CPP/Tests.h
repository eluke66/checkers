/*
 * Tests.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef TESTS_H_
#define TESTS_H_


#include "gtest/gtest.h"
#include "Board.h"
#include "Coordinate.h"
#include "Move.h"
#include <iostream>

#define ASSERT_EMPTY(lst) ASSERT_EQ(0, lst.size())
#define ASSERT_NULL(item) ASSERT_EQ(nullptr, (item))
#define ASSERT_PRESENT(item) ASSERT_NE(nullptr, (item))




#endif /* TESTS_H_ */
