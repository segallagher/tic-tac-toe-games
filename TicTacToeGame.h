// TicTacToeGame.h
// Samuel Gallagher
// 2023-10-01
// Header file for TicTacToeGame class

#ifndef TicTacToeGame_HPP
#define TicTacToeGame_HPP

#include "olcPixelGameEngine.h"
#include "Button.h"
#include "BoardButton.h"
#include "board.h"
#include <utility>

class TicTacToeGame : public olc::PixelGameEngine
{
public:
	TicTacToeGame();

public:
	// Called once at the start, so create things here
	bool OnUserCreate() override;
	// Called once per frame
	bool OnUserUpdate(float fElapsedTime) override;

	// Draws everything that needs to be drawn
	void drawing();
	// Loads the sprites for the game
	void loadSprites();

	// ######################
	// Board setup
	// ######################

	// Sets up TicTacToe Ultimate (3x3 boards)
	void ultimateBoardSetup(olc::v2d_generic<int> bigBoardDimensions = { 3, 3 }, olc::v2d_generic<int> smallBoardDimensions = { 3, 3 });
	// Sets up a single TicTacToe board
	void regularBoardSetup(olc::v2d_generic<int> boardDimensions = { 3, 3 });

	// Sets up the BoardButtons (called in board setup functions)
	void boardButtonSetup();

	// ######################
	// Buttons
	// ######################

	// Sets up the buttons
	void buttonSetup();
	// Draws the buttons
	void drawButtons();
	// Checks the buttons for clicking
	void checkButtons();

public:
	// ######################
	// Variables
	// ######################

	bool _redrawScreen = true;
	std::vector<std::unique_ptr<Button>> _regularButtons = std::vector<std::unique_ptr<Button>>();
	std::vector<std::unique_ptr<BoardButton>> _boardButtons = std::vector<std::unique_ptr<BoardButton>>();

	olc::Renderable _boardBorder;
	olc::Renderable _boardTileBackground;
	olc::Renderable _boardOTile;
	olc::Renderable _boardXTile;

	Board _board;
};

#endif // !TicTacToeGame_HPP