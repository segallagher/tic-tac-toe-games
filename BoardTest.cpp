// BoardTest.cpp
// Nathan Damon
// 2023-10-08
// This source file contains the unit tests for class Board

#include "Board.h"
#include "Board.h" // Double-inclusion test
#include "doctest.h"

std::vector<std::vector<Board::Tile>> getTestTiles()
{
	auto newBoard = std::vector<std::vector<Board::Tile>>(3);
	newBoard[0] = std::vector<Board::Tile>(1);
	newBoard[0][0].setState(TileType::O);
	newBoard[1] = std::vector<Board::Tile>(3);
	newBoard[1][0].setState(TileType::X);
	newBoard[1][1].setState(TileType::GameInProgress);
	newBoard[1][2].setState(TileType::Empty);
	newBoard[2] = std::vector<Board::Tile>(1);
	newBoard[2][0].setState(TileType::X);
	return newBoard;
}

TEST_CASE("Board Constructors")
{
	{
		Board board;
		CHECK(board.getBoardDimensions().x == 3);
		CHECK(board.getBoardDimensions().y == 3);
	}
	{
		Board board({ 5, 4 });
		CHECK(board.getBoardDimensions().x == 5);
		CHECK(board.getBoardDimensions().y == 4);
	}
}

TEST_CASE("Tile Set/Get")
{
	Board board;
	auto tile = Board::getCurrentTileType();

	Board::setCurrentTileType(TileType::O);
	board.attemptPlaceTile(0, 0);
	Board::setCurrentTileType(TileType::X);
	board.attemptPlaceTile(0, 0);
	REQUIRE(board.getTile(0, 0) != nullptr);
	CHECK(board.getTile(0, 0)->getState() == tile);

	auto tile1 = Board::getCurrentTileType();
	board.attemptPlaceTile(1, 0);

	Board::setCurrentTileType(TileType::GameInProgress);
	auto tile2 = Board::getCurrentTileType();
	board.attemptPlaceTile(1, 1);

	Board::setCurrentTileType(TileType::O);
	auto tile3 = Board::getCurrentTileType();
	board.attemptPlaceTile(0, 1);


	REQUIRE(board.getTile(1, 0) != nullptr);
	CHECK(board.getTile(1, 0)->getState() == tile1);

	REQUIRE(board.getTile(1, 1) != nullptr);
	CHECK(board.getTile(1, 1)->getState() == tile2);

	REQUIRE(board.getTile(0, 1) != nullptr);
	CHECK(board.getTile(0, 1)->getState() == tile3);

	REQUIRE(board.getTile(0, 0) != nullptr);
	CHECK(board.getTile(0, 0)->getState() == tile);
}

TEST_CASE("Board Dimensions Changing")
{
	SUBCASE("Get/Set board dimensions")
	{
		Board board;
		CHECK(board.getBoardDimensions().x == 3);
		CHECK(board.getBoardDimensions().y == 3);

		board.setBoardDimensions({ 8, 5 });
		CHECK(board.getBoardDimensions().x == 8);
		CHECK(board.getBoardDimensions().y == 5);

		board.setBoardDimensions({ 1, 1 });
		CHECK(board.getBoardDimensions().x == 1);
		CHECK(board.getBoardDimensions().y == 1);

		board.setBoardDimensions({ 0, -2 });
		CHECK(board.getBoardDimensions().x == 1);
		CHECK(board.getBoardDimensions().y == 1);
	}

	SUBCASE("Set board to single tile")
	{
		Board board;
		board.setBoardDimensions({ 8, 5 });

		board.setBoardToSingleTile();
		CHECK(board.getBoardDimensions().x == 1);
		CHECK(board.getBoardDimensions().y == 1);

		board.setUnderlyingBoard(getTestTiles());
		board.setBoardToSingleTile();
		CHECK(board.getBoardDimensions().x == 1);
		CHECK(board.getBoardDimensions().y == 1);
		REQUIRE(board.getUnderlyingBoard().size() == 1);
		CHECK(board.getUnderlyingBoard()[0].size() == 1);
	}
}

TEST_CASE("Underlying Board Get/Set")
{
	Board board({ 3, 3 });

	for (auto& y : board.getUnderlyingBoard())
	{
		for (auto& x : y)
		{
			CHECK(x.getState() == TileType::Empty);
			CHECK(x.getChildBoard() == nullptr);
		}
	}

	SUBCASE("Get/Set underlying board")
	{		
		board.setUnderlyingBoard(getTestTiles());
		auto& b = board.getUnderlyingBoard();
		REQUIRE(b.size() != 0);
		for (size_t i = 0; i < b.size(); i++)
		{
			if (i == 0)
			{
				REQUIRE(b[i].size() > 0);
				CHECK(b[i][0].getState() == TileType::O);
				CHECK(b[i][0].getChildBoard() == nullptr);
			}
			else if (i == 1)
			{
				REQUIRE(b[i].size() > 2);
				CHECK(b[i][0].getState() == TileType::X);
				CHECK(b[i][0].getChildBoard() == nullptr);
				CHECK(b[i][1].getState() == TileType::GameInProgress);
				CHECK(b[i][1].getChildBoard() == nullptr);
				CHECK(b[i][2].getState() == TileType::Empty);
				CHECK(b[i][2].getChildBoard() == nullptr);
			}
			else
			{
				REQUIRE(b[i].size() > 0);
				CHECK(b[i][0].getState() == TileType::X);
				CHECK(b[i][0].getChildBoard() == nullptr);
			}
		}
	}
	SUBCASE("Board reset")
	{
		board.setUnderlyingBoard(getTestTiles());
		board.resetBoard();
		auto& b = board.getUnderlyingBoard();
		REQUIRE(b.size() != 0);
		for (size_t i = 0; i < b.size(); i++)
		{
			if (i == 0)
			{
				REQUIRE(b[i].size() > 0);
				CHECK(b[i][0].getState() == TileType::Empty);
				CHECK(b[i][0].getChildBoard() == nullptr);
			}
			else if (i == 1)
			{
				REQUIRE(b[i].size() > 2);
				CHECK(b[i][0].getState() == TileType::Empty);
				CHECK(b[i][0].getChildBoard() == nullptr);
				CHECK(b[i][1].getState() == TileType::Empty);
				CHECK(b[i][1].getChildBoard() == nullptr);
				CHECK(b[i][2].getState() == TileType::Empty);
				CHECK(b[i][2].getChildBoard() == nullptr);
			}
			else
			{
				REQUIRE(b[i].size() > 0);
				CHECK(b[i][0].getState() == TileType::Empty);
				CHECK(b[i][0].getChildBoard() == nullptr);
			}
		}
	}
}

TEST_CASE("Board Turns")
{
	CHECK(Board::getCurrentTurn() == 0);

	Board::setCurrentTurn(5);
	CHECK(Board::getCurrentTurn() == 5);

	Board::setCurrentTurn(10000);
	CHECK(Board::getCurrentTurn() == 10000);

	Board::incrementTurn();
	CHECK(Board::getCurrentTurn() == 10001);

	Board::incrementTurn();
	CHECK(Board::getCurrentTurn() == 10002);

	for (size_t i = 0; i < 27; i++)
	{
		Board::incrementTurn();
	}
	CHECK(Board::getCurrentTurn() == 10002 + 27);
}

TEST_CASE("Board Parenting")
{
	std::unique_ptr<Board> board = std::make_unique<Board>();
	Board::Tile tile;
	CHECK(tile.getChildBoard() == nullptr);

	tile.setChildBoard(board);
	REQUIRE(tile.getChildBoard() != nullptr);
	CHECK(tile.getChildBoard()->getParentTile() == &tile);
}

TEST_CASE("Board Ruleset")
{
	Board board;
	board.setRuleset(GameMode::nRow);
	CHECK(board.getRuleset() == GameMode::nRow);
}