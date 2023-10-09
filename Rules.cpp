// Rules.cpp
// Samuel Gallagher
// 2023-10-08
// Source file for Rules.h

#include "Rules.h"

bool score(GameMode ruleset, std::vector<std::vector<TileType>> board) {
	return true;
	if (ruleset == GameMode::nRow) {
		return _nRow(board, 3);	// HARDCODED VALUE ALERT, find a way to pass n in
	}

}

bool _nRow(std::vector<std::vector<TileType>> board, int length) {
	// Iterate over rows
	for (int i = 0; i < board.size(); i++) {
		// Iterate over indices
		for (int j = 0; j < board.at(i).size(); j++) {
			TileType tileValue = board.at(i).at(j);

			if (_checkContinuous(i, j, board, tileValue, length)) {
				return true;
			}
		}
	}
	return false;
}

bool _checkContinuous(int row, int column, std::vector<std::vector<TileType>> board, TileType tileValue, int length) {
	std::vector<std::vector<int>> directions{
		{-1,-1}, {0,-1}, {1,-1},
		{-1,0}, {1,0},
		{-1,1}, {0,1}, {1,1}
	};
	for (auto dir : directions) {
		for (int i = 0; i < length; i++) {
			std::cout << tileValue << " ";
			if (board.at(i * dir[0] + row).at(i * dir[1] + column) != tileValue) {
				std::cout << std::endl;
				break;
			}
			if (i == length - 1) {
				return true;
			}
		}
	}
	return false;
}