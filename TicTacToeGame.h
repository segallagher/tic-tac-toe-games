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
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void drawing();
	void loadSprites();

	void bigBoardSetup(olc::v2d_generic<int> bigBoardDimensions, olc::v2d_generic<int> smallBoardDimensions);

	// Buttons
	void buttonSetup();
	void drawButtons();
	void checkButtons();

	bool _redrawScreen = true;
	std::vector<std::unique_ptr<Button>> _buttons = std::vector<std::unique_ptr<Button>>();

	olc::Renderable _boardBorder;
	olc::Renderable _boardTileBackground;
	olc::Renderable _boardOTile;
	olc::Renderable _boardXTile;

	Board _board;
};

#endif // !TicTacToeGame_HPP