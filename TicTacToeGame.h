// TicTacToeGame.h
// Nathan Damon
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
	TicTacToeGame();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void drawing();

	void loadSprites()
	{
		_boardBorder.Load("./Sprites/BoardBorder.png");
		_boardTileBackground.Load("./Sprites/TileBackground.png");
		_boardOTile.Load("./Sprites/OTile.png");
		_boardXTile.Load("./Sprites/XTile.png");
	}

	// Buttons
	void buttonSetup()
	{
		std::unique_ptr<BoardButton> boardButton = std::make_unique<BoardButton>();
		boardButton->setDimensions(GetScreenSize() * 70 / 100);
		boardButton->setDecal(_boardBorder.Decal());
		boardButton->setTileDecal(_boardTileBackground.Decal());
		boardButton->setODecal(_boardOTile.Decal());
		boardButton->setXDecal(_boardXTile.Decal());
		boardButton->center(GetScreenSize());

		_buttons.push_back(std::move(boardButton));

		auto buttonPtr = _buttons.back().get();
		(dynamic_cast<BoardButton*>(buttonPtr))->setBoard(&_testBoard);
		auto boardButtonCallback = [buttonPtr] {std::cout << (dynamic_cast<BoardButton*>(buttonPtr))->getClickedTile({ 5, 5 }) << std::endl; };
		_buttons.back()->setCallback(boardButtonCallback);


		// Simple adhoc button test

		Button button({ 0, 0 }, { 30, 30 });
		button.setDecal(_boardBorder.Decal());
		button.alignBottomRight(GetScreenSize());
		button.setCallback([] { std::cout << "B1 Is Pressed!" << std::endl; });
		_buttons.push_back(std::make_unique<Button>(button));

		Button button2({ 0, 0 }, { 5, 5 });
		button2.alignTopRight(GetScreenSize());
		// [&] captures all variables for use in lambda (note items that will be out of scope)
		button2.setCallback([&] { std::cout << "B2 Is Pressed!" << std::endl;
		_buttons[1]->alignTopLeft();
		_buttons[1]->setCallback([&]
			{
				std::cout << "B1 Is Pressed!" << std::endl;
				_buttons[2]->alignBottomLeft(GetScreenSize());
			});
			});
		_buttons.push_back(std::make_unique<Button>(button2));

		std::cout << "Button count: " << _buttons.size() << std::endl;
	}
	void drawButtons()
	{
		for (auto& button : _buttons)
		{
			if (button->isHidden() == false)
				button->drawSelf(this);
		}
	}
	void checkButtons()
	{
		if (GetMouse(0).bReleased)
			for (auto& button : _buttons)
			{
				if (button->isActive())
					if (button->isPressed(GetMousePos()))
						_redrawScreen = true;
			}
	}

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