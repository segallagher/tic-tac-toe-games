// TicTacToeGame.h
// Samuel Gallagher
// 2023-10-01
// Header file for TicTacToeGame class

#pragma once

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Button.h"
#include "BoardButton.h"
#include <utility>

#ifndef TicTacToeGame_HPP
#define TicTacToeGame_HPP

class TicTacToeGame : public olc::PixelGameEngine
{
public:
	// Constructors
	TicTacToeGame();

	// Member Functions
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void drawing();

	void loadSprites();

	// Buttons
	void buttonSetup();
	void drawButtons();
	void checkButtons();

	// Member Variables

	bool _redrawScreen = true;
	std::vector<std::unique_ptr<Button>> _buttons = std::vector<std::unique_ptr<Button>>();

	olc::Renderable _boardBorder;
	olc::Renderable _boardTileBackground;
	olc::Renderable _boardOTile;
	olc::Renderable _boardXTile;

	// Testing board
	std::vector<std::vector<int>> _testBoard = {
		{ 1, 2, 1 },
		{ 1, 2, 0 },
		{ 1, 0, 2 }
	};
};

#endif // !TicTacToeGame_HPP