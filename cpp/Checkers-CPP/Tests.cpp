#include "gtest/gtest.h"

#include "SinglePiecesTests.cpp"
#include "KingPiecesTests.cpp"
#include "MoveRulesTests.cpp"
#include "GameTests.cpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
