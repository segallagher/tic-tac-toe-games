// Board.h
// Nathan Damon
// 2023-10-08
// Template header file for Board (a class that will serve as the board for the game).

#include "TicTacToeGame.h"

#ifndef BOARD_HPP
#define BOARD_HPP

class Board
{
public:
	enum class TileType
	{
		Empty,
		GameInProgress,
		O,
		X
	};

	// ##################################################
	// Tile struct
	// ##################################################

	struct Tile {
		Tile()
		{

		}
		Tile(const Tile& other)
		{
			*this = other;
		}
		~Tile()
		{

		}
		Tile& operator=(const Tile& other)
		{
			if (this == &other)
				return *this;

			_value = other._value;

			if (other._board == nullptr)
			{
				_board = nullptr;
			}
			else
			{
				Board board(other._board.get()->getBoardDimensions());
				board.setUnderlyingBoard(other._board.get()->getUnderlyingBoard());
				_board = std::make_unique<Board>(board);
			}

			return *this;
		}
		TileType _value = TileType::Empty;
		std::unique_ptr<Board> _board = nullptr;
	}; // End Tile struct
public:
	Board();
	Board(olc::v2d_generic<int> dimensions);
	~Board();

	bool attemptPlaceTile(int x, int y);
	bool attemptPlaceTile(olc::v2d_generic<int> position);
	Tile* getTile(int x, int y);
	Tile* getTile(olc::v2d_generic<int> position);

	void setIsBoardOfBoards(bool isBoardOfBoards);
	bool isBoardOfBoards();

	void setBoardToSingleTile();
	void setBoardToSingleOnGameWin(bool setSingleOnGameWon);

	// Underlying board
	olc::v2d_generic<int> getBoardDimensions();
	void setBoardDimensions(olc::v2d_generic<int> dimensions);
	void setUnderlyingBoard(std::vector<std::vector<Tile>> board);
	std::vector<std::vector<Tile>>& getUnderlyingBoard();
	void resetBoard();

	// Turns
	void setCurrentTurn(int turn);
	void incrementTurn();
	int getCurrentTurn();

	// Tile
	void cycleTileType();
	void setCurrentTileType(TileType tile);
	TileType getCurrentTileType();

private:
	std::vector<std::vector<Tile>> _board;
	bool _setSingleOnGameWon = true;
	bool _isBoardOfBoards = false;

	static int _turn;
	static TileType _currentTileType;
}; // End Board class

#endif // !BOARD_HPP