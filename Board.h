// Board.h
// Nathan Damon
// 2023-10-08
// Template header file for Board (a class that will serve as the board for the game).

#include "TicTacToeGame.h"

#ifndef BOARD_HPP
#define BOARD_HPP

enum GameMode
{
	nRow
};

enum class TileType
{
	Empty,
	GameInProgress,
	O,
	X
};

class Board
{
public:

	// ##################################################
	// Tile struct - stores subboards and there state
	// ##################################################

	struct Tile {
		Tile(Board* parentBoard = nullptr);
		Tile(const Tile& other);
		~Tile();
		Tile& operator=(const Tile& other);

		// Gets the state of the tile
		TileType getState();
		// Sets the state of the tile and calls the parent board's evaluataion function
		void setState(TileType state, bool evaluateParentBoard = true);

		// Gets a pointer to the board that this tile is a part of
		Board* getParentBoard();
		// Sets the parent board for this tile
		void setParentBoard(Board* parentBoard);

		// Returns the pointer to the board within this tile
		std::unique_ptr<Board>& getChildBoard();
		// Sets the board within this tile
		void setChildBoard(std::unique_ptr<Board>& board);

	private:
		TileType _state = TileType::Empty;
		Board* _parentBoard = nullptr;
		std::unique_ptr<Board> _childBoard = nullptr;
	}; // End Tile struct

public:
	Board();
	Board(olc::v2d_generic<int> dimensions);
	~Board();

	// Calls the scoring functions for the board
	void evaluateBoard();

	// Attempts to place a tile at the x and y location
	bool attemptPlaceTile(int x, int y);
	// Attempts to place a tile at position
	bool attemptPlaceTile(olc::v2d_generic<int> position);
	// Gets a pointer to the tile at the x and y location
	Tile* getTile(int x, int y);
	// Gets a pointer to the tile at position
	Tile* getTile(olc::v2d_generic<int> position);

	// Returns the boards tiles in a formated state for scoring
	std::vector<std::vector<TileType>> getBoardTilesAsTileType();
	// Sets the board to a single tile
	void setBoardToSingleTile(TileType displayTile = TileType::Empty);
	// Determines if a board should be reduced to a single tile on game finished
	void setBoardToSingleOnGameWin(bool setSingleOnGameWon);

	// ###############################
	// Underlying board
	// ###############################

	// Returns the dimensions of the underlying vector of vectors
	olc::v2d_generic<int> getBoardDimensions();
	// Sets the tile dimensions of the board
	void setBoardDimensions(olc::v2d_generic<int> dimensions);
	// Sets the board based on another board
	void setUnderlyingBoard(std::vector<std::vector<Tile>> board);
	// Returns the underlying vector of vectors
	std::vector<std::vector<Tile>>& getUnderlyingBoard();
	// Sets all tiles to the Empty state
	void resetBoard();

	// ###############################
	// Turns
	// ###############################

	// Sets the turn counter
	static void setCurrentTurn(int turn);
	// Increases the turn counter by one
	static void incrementTurn();
	// Returns the current turn count
	static int getCurrentTurn();

	// ###############################
	// Tile
	// ###############################

	// Cycles the tile type between O and X
	static void cycleTileType();
	// Sets the current tile type
	static void setCurrentTileType(TileType tile);
	// Gets the current tile type
	static TileType getCurrentTileType();

	// Returns the tile that this board is in
	Tile* getParentTile();
	// Sets the parent tile that this board uses
	void setParentTile(Tile* parentTile);
	// Sets the state of the parent tile
	void setParentTileState(TileType state);

	// ###############################
	// Other
	// ###############################

	// Sets the board's used ruleset
	void setRuleset(GameMode ruleset);
	// Gets the board's ruleset
	GameMode getRuleset();

	// Sets the board to be active: if true, the board will receive inputs
	void setActive(bool isActive);
	// Returns true if the board is active
	bool isActive();

private:
	Tile* _parentTilePtr = nullptr;
	std::vector<std::vector<Tile>> _board;
	bool _isActive = true;
	bool _setSingleOnGameWon = true;

	GameMode _ruleset = nRow;

	static int _turn;
	static TileType _currentTileType;
}; // End Board class

#endif // !BOARD_HPP