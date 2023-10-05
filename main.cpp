// main.cpp
// Nathan Damon & Samuel Gallapher
// 2023-09-30
// The main.cpp file for tic-tac-toe games

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Button.h"
#include "BoardButton.h"
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

class TicTacToeGame : public olc::PixelGameEngine
{
public:
	TicTacToeGame()
	{
		sAppName = "Tic Tac Toe BIG";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		loadSprites();

		buttonSetup();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame

		// Only draw when we need to update
		if(_redrawScreen)
			drawing();

		// Other mechanics here
		checkButtons();

		return true;
	}

	void drawing()
	{
		// Clear the screen to given color
		Clear(olc::BLACK);

		drawButtons();

		//_redrawScreen = false;
	}

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
		auto boardButtonCallback = [buttonPtr] {std::cout << (dynamic_cast<BoardButton*>(buttonPtr))->getClickedTile({5, 5}) << std::endl; };
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
		for (auto &button : _buttons)
		{
			if (button->isHidden() == false)
				button->drawSelf(this);
		}
	}
	void checkButtons()
	{
		if (GetMouse(0).bReleased)
			for (auto &button : _buttons)
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


int main(int argc, char** argv)
{
	// Doctest Testing
	doctest::Context dtcontext;
	int dtresult = 0;
	dtcontext.applyCommandLine(argc, argv);
	dtcontext.setOption("no-breaks", true); // Don't break in the debugger when assertions fail

	dtresult = dtcontext.run();
	if (dtcontext.shouldExit()) // important - query flags (and --exit) rely on the user doing this
		return dtresult;		// propagate the result of the tests

	// End Doctest Testing

	TicTacToeGame game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();

	return dtresult;
}