// Board.cpp
// Nathan Damon
// 2023-10-08
// Source file for Board (a class that will serve as the board for the game).

#include "board.h"

int Board::_turn = 0;
TileType Board::_currentTileType = TileType::O;

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

void Board::evaluateBoard()
{
	auto result = score(_ruleset, getBoardTilesAsTileType());
	
	if (result.first) {
		setParentTileState(result.second);
		setBoardToSingleTile(result.second);
		setActive(false);
	}
}

bool Board::attemptPlaceTile(int x, int y)
{
	if (isActive() == false)
		return false;

	if (x >= 0 && x < getBoardDimensions().x &&
		y >= 0 && y < getBoardDimensions().y)
	{
		if (_board[y][x].getChildBoard() != nullptr)
			return false;
		else
		{
			// Current tile
			if (_board[y][x].getState() != TileType::Empty)
				return false;

			_board[y][x].setState(getCurrentTileType());
			updateTileType(getRuleset());

			// Parent tile
			if(getParentTile() != nullptr && getParentTile()->getState() == TileType::Empty)
				getParentTile()->setState(TileType::GameInProgress);

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

std::vector<std::vector<TileType>> Board::getBoardTilesAsTileType()
{
	auto board_checkFormat = std::vector<std::vector<TileType>>(getBoardDimensions().y);
	for (int y = 0; y < getBoardDimensions().y; y++)
	{
		board_checkFormat[y] = std::vector<TileType>(getBoardDimensions().x);
		for (int x = 0; x < getBoardDimensions().x; x++)
		{
			board_checkFormat[y][x] = getTile(x, y)->getState();
		}
	}
	return board_checkFormat;
}

void Board::setBoardToSingleTile(TileType displayTile)
{
	// Avoid issues with deleting boards that are attatched to BoardButtons
	auto boardTilePtr = getTile(0, 0);
	if (boardTilePtr != nullptr && boardTilePtr->getChildBoard() != nullptr)
		return;

	setBoardDimensions({ 1, 1 });
	_board[0][0].setState(displayTile, false);
}
void Board::setBoardToSingleOnGameWin(bool setSingleOnGameWon)
{
	_setSingleOnGameWon = setSingleOnGameWon;
}

olc::v2d_generic<int> Board::getBoardDimensions()
{
	auto size = olc::v2d_generic<int>(0, int(_board.size()));
	if (size.y > 0)
		size.x = int(_board[0].size());
	return size;
}
void Board::setBoardDimensions(olc::v2d_generic<int> dimensions)
{
	dimensions = olc::v2d_generic<int>(std::max(1, dimensions.x), std::max(1, dimensions.y));
	_board = std::vector<std::vector<Tile>>(dimensions.y, std::vector<Tile>(dimensions.x, Tile(this)));
}
void Board::setUnderlyingBoard(std::vector<std::vector<Tile>> board)
{
	_board = board;
	for (auto& y : _board)
	{
		for (auto& x : y) 
		{
			x.setParentBoard(this);
		}
	}
}
std::vector<std::vector<Board::Tile>>& Board::getUnderlyingBoard()
{
	return _board;
}
void Board::resetBoard()
{
	for (auto& y : getUnderlyingBoard())
		for (auto& x : y)
			x = Tile(this);
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
TileType Board::getCurrentTileType()
{
	return _currentTileType;
}

Board::Tile* Board::getParentTile()
{
	return _parentTilePtr;
}
void Board::setParentTile(Tile* parentTile)
{
	_parentTilePtr = parentTile;
}
void Board::setParentTileState(TileType state)
{
	if (getParentTile() != nullptr)
		getParentTile()->setState(state);
}

void Board::setRuleset(GameMode ruleset)
{
	_ruleset = ruleset;
	initializeTileType(ruleset);
	for (auto& y : _board)
	{
		for (auto& x : y)
		{
			if(x.getChildBoard() != nullptr)
				x.getChildBoard()->setRuleset(getRuleset());
		}
	}
}
GameMode Board::getRuleset()
{
	return _ruleset;
}

void Board::setActive(bool isActive)
{
	_isActive = isActive;
	for (auto& y : getUnderlyingBoard())
		for (auto& x : y)
			if (x.getChildBoard() != nullptr)
				x.getChildBoard()->setActive(isActive);
				
}
bool Board::isActive()
{
	return _isActive;
}

// #############################################################################################
// Board::Tile
// #############################################################################################

Board::Tile::Tile(Board* parentBoard)
	: _parentBoard(parentBoard)
{
}
Board::Tile::Tile(const Tile& other)
{
	*this = other;
}
Board::Tile::~Tile()
{
}

Board::Tile& Board::Tile::operator=(const Tile& other)
{
	if (this == &other)
		return *this;

	_state = other._state;
	_parentBoard = other._parentBoard;

	if (other._childBoard == nullptr)
	{
		_childBoard = nullptr;
	}
	else
	{
		Board board(other._childBoard.get()->getBoardDimensions());
		board.setUnderlyingBoard(other._childBoard.get()->getUnderlyingBoard());
		_childBoard = std::make_unique<Board>(board);
	}

	return *this;
}

// Functions

TileType Board::Tile::getState()
{
	return _state;
}
void Board::Tile::setState(TileType state, bool evaluateParentBoard)
{
	_state = state;
	if (evaluateParentBoard &&
		getState() != TileType::Empty &&
		getState() != TileType::GameInProgress &&
		getParentBoard() != nullptr)
	{
		getParentBoard()->evaluateBoard();
	}
}

Board* Board::Tile::getParentBoard()
{
	return _parentBoard;
}
void Board::Tile::setParentBoard(Board* parentBoard)
{
	_parentBoard = parentBoard;
}
std::unique_ptr<Board>& Board::Tile::getChildBoard()
{
	return _childBoard;
}
void Board::Tile::setChildBoard(std::unique_ptr<Board>& board)
{
	if (board == nullptr)
	{
		_childBoard = nullptr;
	}
	else
	{
		_childBoard = std::move(board);
		_childBoard->setParentTile(this);
	}
}

