// main.cpp
// Nathan Damon & Samuel Gallapher
// 2022-09-30
// The main.cpp file for tic-tac-toe games

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Button.h"

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

		_redrawScreen = false;
	}


	// Buttons
	void buttonSetup()
	{
		// Simple adhoc button test

		Button button({ 0, 0 }, { 50, 20 });
		button.center(this->GetScreenSize());
		button.setCallback([] { std::cout << "B1 Is Pressed!" << std::endl; });
		_buttons.push_back(button);

		Button button2({ 0, 0 }, { 30, 70 });
		button2.centerHorizontally(this->GetScreenSize());
		// [&] captures all variables for use in lambda (note items that will be out of scope)
		button2.setCallback([&] { std::cout << "B2 Is Pressed!" << std::endl;
		_buttons[0].setPosition(_buttons[0].getPosition() - olc::vi2d{ 5,5 });
			});
		_buttons.push_back(button2);

		std::cout << "Button count: " << _buttons.size() << std::endl;
	}
	void drawButtons()
	{
		for (auto &button : _buttons)
		{
			if (button.isActive())
				button.drawSelf(*this);
		}
	}
	void checkButtons()
	{
		if (GetMouse(0).bReleased)
			for (auto &button : _buttons)
			{
				if (button.isActive())
					if (button.isPressed(GetMousePos()))
						_redrawScreen = true;
			}
	}

	bool _redrawScreen = true;
	std::vector<Button> _buttons = std::vector<Button>();
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