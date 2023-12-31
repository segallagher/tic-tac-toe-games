// Rules.h
// Samuel Gallagher
// 2023-10-08
// Header file for rules class

#include <vector>
#include "TicTacToeGame.h"
#include <iostream>
#include <algorithm>

#ifndef RULES_HPP
#define RULES_HPP

enum GameMode
{
	nRow,
	notakto,
	endOfList // needed for gamemode changing
};

enum TileType
{
	Empty,
	GameInProgress,
	O,
	X
};

/// <summary>
/// checks if a board satisfies a win condition
/// </summary>
/// <param name="ruleset"> enum value from GameMode to choose rules </param>
/// <param name="board"> full board of tic-tac-toe </param>
/// <returns> true if win, false otherwise </returns>
std::pair<bool, TileType> score(GameMode ruleset, const std::vector<std::vector<TileType>> & board);

/// <summary>
/// score using the nRow rules
/// </summary>
/// <param name="board"> full tic-tac-toe board </param>
/// <param name="length"> length of continuous tileType needed to win </param>
/// <returns> true if win, false otherwise </returns>
std::pair<bool, TileType> _nRow(const std::vector<std::vector<TileType>> & board, int length);

/// <summary>
/// checks if there are "length" in a row of a single tileType
/// </summary>
/// <param name="row"> current tile row </param>
/// <param name="column"> current tile column </param>
/// <param name="board"> entire board </param>
/// <param name="tileValue"> type of tile to check for </param>
/// <param name="length"> continuous length of tiles to check for </param>
/// <returns> true if win, false otherwise </returns>
bool _checkContinuous(int row, int column, const std::vector<std::vector<TileType>> & board, TileType tileValue, int length);

// Returns the current ruleset as a string
std::string getGamemodeAsString(GameMode gamemode);

// Gets the current gamemode's rules text
std::string getGameRulesText(GameMode gamemode);

// Updates the current placeable tile to what it needs to be next
void updateTileType(GameMode gamemode);

// Sets the tile to be what it should be for the given gamemode
void initializeTileType(GameMode gamemode);

// Returns text for the on game win/lose display
std::string gameCompleteTitleString(GameMode gamemode);

#endif // !RULES_HPP