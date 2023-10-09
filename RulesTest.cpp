// RulesTest.cpp
// Samuel Gallagher
// 2023-10-08
// This source file contains the unit tests for class Rules


#include "Rules.h"
#include "Rules.h" // Double-inclusion test
#include "doctest.h"

TEST_CASE("Board Checks")
{
	

	// Test values
	std::vector<std::vector<TileType>> board{
		{TileType::X,TileType::X,TileType::X},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

}