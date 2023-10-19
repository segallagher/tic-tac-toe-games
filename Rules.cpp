// Rules.cpp
// Samuel Gallagher
// 2023-10-08
// Source file for Rules.h

#include "Rules.h"

std::pair<bool, TileType> score(const GameMode ruleset, const std::vector<std::vector<TileType>> & board) {
	if (ruleset == GameMode::nRow) {
		int length = board.size();
		if (length > 5) {
			length = 5;
		}
		return _nRow(board, length);	// HARDCODED VALUE ALERT, find a way to pass n in
	}

}

std::pair<bool, TileType> _nRow(const std::vector<std::vector<TileType>> & board, int length) {
	// Iterate over rows
	for (int i = 0; i < board.size(); i++) {
		// Iterate over indices
		for (int j = 0; j < board.at(i).size(); j++) {
			TileType tileValue = board.at(i).at(j);

			if (tileValue == TileType::Empty || tileValue == TileType::GameInProgress) {
				continue;
			}

			if (_checkContinuous(i, j, board, tileValue, length)) {
				return std::make_pair(true, tileValue);
			}
		}
	}
	return std::make_pair(false, TileType::Empty);
}

bool _checkContinuous(int row, int column, const std::vector<std::vector<TileType>> & board, const TileType tileValue, int length) {
	std::vector<std::vector<int>> directions{
		{-1,-1}, {0,-1}, {1,-1},
		{-1,0}, {1,0},
		{-1,1}, {0,1}, {1,1}
	};
	for (auto dir : directions) {
		for (int i = 0; i < length; i++) {
			int x = i * dir[0] + column;
			int y = i * dir[1] + row;

			if ((x >= 0 && x < board.at(0).size()) && (y >= 0 && y < board.size())) {
			}
			if ((x < 0 || x >= board.at(0).size()) || (y < 0 || y >= board.size()) || board.at(y).at(x) != tileValue) {
				break;
			}
			if (i == length - 1) {
				return true;
			}
		}
	}

	return false;
}

std::string getGamemodeAsString(GameMode gamemode)
{
	switch (gamemode)
	{
	case nRow:
		return "nRow";
	case endOfList:
		return "endOfList";
	default:
		return "No display";
	}
}

std::string getGameRulesText(GameMode gamemode)
{
	switch (gamemode)
	{
	case nRow:
		return
			"Get n (max of 5) of\n"
			"your tiles in a row\n"
			"to win a board.";
	default:
	case endOfList:
		return "Ruleset error: change gamemode";
	}
}

void updateTileType(GameMode gamemode)
{
	switch (gamemode)
	{
	case nRow:
		Board::cycleTileType();
		break;
	/*case natakto:
		Board::setCurrentTileType(TileType::X);
		break;*/
	default:
	case endOfList:
		Board::cycleTileType();
		break;	
	}
}

void initializeTileType(GameMode gamemode)
{
	switch (gamemode)
	{
	case nRow:
		Board::setCurrentTileType(TileType::O);
		break;
		/*case natakto:
			Board::setCurrentTileType(TileType::X);
			break;*/
	default:
	case endOfList:
		Board::setCurrentTileType(TileType::O);
		break;
	}
}
