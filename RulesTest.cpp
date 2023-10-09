// RulesTest.cpp
// Samuel Gallagher
// 2023-10-08
// This source file contains the unit tests for class Rules


#include "Rules.h"
#include "Rules.h" // Double-inclusion test
#include "doctest.h"

TEST_CASE("Empty Board") {
	std::vector<std::vector<TileType>> board{
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);
}

TEST_CASE("Board Horizontal") {
	std::vector<std::vector<TileType>> board{
		{TileType::X,TileType::X,TileType::X},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::O,TileType::O,TileType::O},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::X,TileType::X,TileType::X}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::O,TileType::X,TileType::O},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

	board = {
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::O,TileType::X,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

	board = {
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::Empty},
		{TileType::X,TileType::Empty,TileType::X}
	};

	CHECK(score(GameMode::nRow, board) == false);
}

TEST_CASE("Board Vertical") {
	std::vector<std::vector<TileType>> board{
		{TileType::X,TileType::Empty,TileType::Empty},
		{TileType::X,TileType::Empty,TileType::Empty},
		{TileType::X,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::Empty,TileType::O,TileType::Empty},
		{TileType::Empty,TileType::O,TileType::Empty},
		{TileType::Empty,TileType::O,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::Empty,TileType::Empty,TileType::X},
		{TileType::Empty,TileType::Empty,TileType::X},
		{TileType::Empty,TileType::Empty,TileType::X}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::X,TileType::Empty,TileType::Empty},
		{TileType::X,TileType::Empty,TileType::Empty},
		{TileType::O,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

	board = {
		{TileType::Empty,TileType::O,TileType::Empty},
		{TileType::Empty,TileType::O,TileType::Empty},
		{TileType::Empty,TileType::X,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

	board = {
		{TileType::Empty,TileType::Empty,TileType::X},
		{TileType::Empty,TileType::Empty,TileType::O},
		{TileType::Empty,TileType::Empty,TileType::X}
	};

	CHECK(score(GameMode::nRow, board) == false);
}

TEST_CASE("Board Diagonal")
{
	std::vector<std::vector<TileType>> board{
		{TileType::X,TileType::Empty,TileType::Empty},
		{TileType::Empty,TileType::X,TileType::Empty},
		{TileType::Empty,TileType::Empty,TileType::X}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::Empty,TileType::Empty,TileType::O},
		{TileType::Empty,TileType::O,TileType::Empty},
		{TileType::O,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == true);

	board = {
		{TileType::X,TileType::Empty,TileType::O},
		{TileType::Empty,TileType::X,TileType::Empty},
		{TileType::O,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

	board = {
		{TileType::Empty,TileType::Empty,TileType::O},
		{TileType::Empty,TileType::X,TileType::Empty},
		{TileType::O,TileType::Empty,TileType::Empty}
	};

	CHECK(score(GameMode::nRow, board) == false);

}