// Board.h
// Nathan Damon
// 2023-10-08
// Template header file for Board (a class that will serve as the board for the game).

#include "board.h"

int Board::_turn = 0;
Board::TileType Board::_currentTileType = TileType::O;

// ###########################################################################################################################
// Constructors
// ###########################################################################################################################

Board::Board()
	: Board({ 3, 3 })
{

}
Board::Board(olc::v2d_generic<int> dimensions)
{
	setBoardDimensions(dimensions);
}
Board::~Board()
{
}

// ###########################################################################################################################
// Member functions
// ###########################################################################################################################

bool Board::attemptPlaceTile(int x, int y)
{
	if (_isBoardOfBoards)
		return false;
	else
	{
		if (x >= 0 && x < getBoardDimensions().x &&
			y >= 0 && y < getBoardDimensions().y)
		{
			_board[y][x]._value = getCurrentTileType();
			cycleTileType();
			return true;
		}
	}
	return false;
}
bool Board::attemptPlaceTile(olc::v2d_generic<int> position)
{
	return attemptPlaceTile(position.x, position.y);
}
Board::Tile* Board::getTile(int x, int y)
{
	if (x >= 0 && x < getBoardDimensions().x &&
		y >= 0 && y < getBoardDimensions().y)
	{
		return &(_board[y][x]);
	}
	else
	{
		return nullptr;
	}
}
Board::Tile* Board::getTile(olc::v2d_generic<int> position)
{
	return getTile(position.x, position.y);
}

void Board::setIsBoardOfBoards(bool isBoardOfBoards)
{
	_isBoardOfBoards = isBoardOfBoards;
}
bool Board::isBoardOfBoards()
{
	return _isBoardOfBoards;
}

void Board::setBoardToSingleTile()
{
	setBoardDimensions({ 1, 1 });
}
void Board::setBoardToSingleOnGameWin(bool setSingleOnGameWon)
{
	_setSingleOnGameWon = setSingleOnGameWon;
}

olc::v2d_generic<int> Board::getBoardDimensions()
{
	auto size = olc::v2d_generic<int>(0, _board.size());
	if (size.y > 0)
		size.x = _board[0].size();
	return size;
}
void Board::setBoardDimensions(olc::v2d_generic<int> dimensions)
{
	dimensions = olc::v2d_generic<int>(std::max(1, dimensions.x), std::max(1, dimensions.y));
	_board = std::vector<std::vector<Tile>>(dimensions.y);
	for (size_t i = 0; i < _board.size(); i++)
	{
		_board[i] = std::vector<Tile>(dimensions.x);
	}
}
void Board::setUnderlyingBoard(std::vector<std::vector<Tile>> board)
{
	_board = board;
}
std::vector<std::vector<Board::Tile>>& Board::getUnderlyingBoard()
{
	return _board;
}
void Board::resetBoard()
{
	for (auto& y : getUnderlyingBoard())
		for (auto& x : y)
			x = Tile();
}

void Board::setCurrentTurn(int turn)
{
	_turn = turn;
}
void Board::incrementTurn()
{
	setCurrentTurn(getCurrentTurn() + 1);
}
int Board::getCurrentTurn()
{
	return _turn;
}

void Board::cycleTileType()
{
	switch (getCurrentTileType())
	{
	case TileType::Empty:
		break;
	case TileType::GameInProgress:
		break;
	case TileType::O:
		setCurrentTileType(TileType::X);
		break;
	case TileType::X:
		setCurrentTileType(TileType::O);
		break;
	default:
		break;
	}
}
void Board::setCurrentTileType(TileType tile)
{
	_currentTileType = tile;
}
Board::TileType Board::getCurrentTileType()
{
	return _currentTileType;
}