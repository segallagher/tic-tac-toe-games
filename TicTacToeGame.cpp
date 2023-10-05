// TicTacToeGame.cpp
// Samuel Gallagher
// 2023-10-01
// Source file for TicTacToeGame class

#include "TicTacToeGame.h"


// ###########################################################################################################################
// Constructors
// ###########################################################################################################################

TicTacToeGame::TicTacToeGame() 
{
	sAppName = "Tic Tac Toe BIG";
}

// ###########################################################################################################################
// Member functions
// ###########################################################################################################################

bool TicTacToeGame::OnUserCreate()
{
	// Called once at the start, so create things here
	loadSprites();

	buttonSetup();

	return true;
}

bool TicTacToeGame::OnUserUpdate(float fElapsedTime)
{
	// called once per frame

	// Only draw when we need to update
	if (_redrawScreen)
		drawing();

	// Other mechanics here
	checkButtons();

	return true;
}

void TicTacToeGame::drawing()
{
	// Clear the screen to given color
	Clear(olc::BLACK);

	drawButtons();

	//_redrawScreen = false;
}