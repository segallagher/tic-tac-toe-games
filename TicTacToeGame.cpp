// TicTacToeGame.cpp
// Samuel Gallagher
// 2023-10-01
// Source file for TicTacToeGame class

#define OLC_PGE_APPLICATION
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
void TicTacToeGame::loadSprites()
{
	_boardBorder.Load("./Sprites/BoardBorder.png");
	_boardTileBackground.Load("./Sprites/TileBackground.png");
	_boardOTile.Load("./Sprites/OTile.png");
	_boardXTile.Load("./Sprites/XTile.png");
}

void TicTacToeGame::buttonSetup()
{
	// Board display
	auto superBoardDimensions = olc::vi2d(3, 3);
	for (size_t y = 0; y < superBoardDimensions.y; y++)
	{
		for (size_t x = 0; x < superBoardDimensions.x; x++)
		{
			std::unique_ptr<BoardButton> boardButton = std::make_unique<BoardButton>();
			boardButton->setDimensions({ GetScreenSize().x * (700 / superBoardDimensions.x) / 1000, GetScreenSize().y * (700 / superBoardDimensions.y) / 1000 });
			boardButton->setDecal(_boardBorder.Decal());
			boardButton->setTileDecal(_boardTileBackground.Decal());
			boardButton->setODecal(_boardOTile.Decal());
			boardButton->setXDecal(_boardXTile.Decal());
			boardButton->center(this);

			// Top left position
			boardButton->setPosition(
				boardButton->getPosition() - olc::vi2d(
					boardButton->getDimensions().x,
					boardButton->getDimensions().y));
			boardButton->setPosition(
				boardButton->getPosition() + olc::vi2d(
					boardButton->getDimensions().x * x,
					boardButton->getDimensions().y * y));

			_buttons.push_back(std::move(boardButton));

			auto buttonPtr = _buttons.back().get();
			(dynamic_cast<BoardButton*>(buttonPtr))->setBoard(&(_testBoardBig[y * superBoardDimensions.x + x]));
			auto boardButtonCallback = [buttonPtr] {std::cout << (dynamic_cast<BoardButton*>(buttonPtr))->getClickedTile() << std::endl; };
			_buttons.back()->setCallback(boardButtonCallback);
		}
	}
	/*std::unique_ptr<BoardButton> boardButton = std::make_unique<BoardButton>();
	boardButton->setDimensions(GetScreenSize() * 70 / 100);
	boardButton->setDecal(_boardBorder.Decal());
	boardButton->setTileDecal(_boardTileBackground.Decal());
	boardButton->setODecal(_boardOTile.Decal());
	boardButton->setXDecal(_boardXTile.Decal());
	boardButton->center(GetScreenSize());

	_buttons.push_back(std::move(boardButton));

	auto buttonPtr = _buttons.back().get();
	(dynamic_cast<BoardButton*>(buttonPtr))->setBoard(&_testBoard);
	auto boardButtonCallback = [buttonPtr] {std::cout << (dynamic_cast<BoardButton*>(buttonPtr))->getClickedTile() << std::endl; };
	_buttons.back()->setCallback(boardButtonCallback);*/

	// Request dimensions input
	Button buttonSetBoardDimensions({ 0, 0 }, { 20, 20 });
	buttonSetBoardDimensions.setDecal(_boardTileBackground.Decal());
	buttonSetBoardDimensions.alignTopRight(this);
	buttonSetBoardDimensions.setCallback([&]
		{
			int inX = 0;
			int inY = 0;
			std::cout << "New board dimensions:" << std::endl;
			std::cout << "x = ";
			std::cin >> inX;
			std::cout << "y = ";
			std::cin >> inY;

			// Set y
			if (_useBigBoard)
			{
				for (size_t y = 0; y < _testBoardBig.size(); y++)
				{
					_testBoardBig[y] = std::vector<std::vector<int>>(inY);
					for (size_t x = 0; x < _testBoardBig[0].size(); x++)
						_testBoardBig[y][x] = std::vector<int>(inX);
				}
			}
			else
			{
				_testBoard = std::vector<std::vector<int>>(inY);
				for (size_t i = 0; i < _testBoard.size(); i++)
				{
					// Set x
					_testBoard[i] = std::vector<int>(inX);
				}
			}

			std::cout << "Board resized" << std::endl;
		});
	_buttons.push_back(std::make_unique<Button>(buttonSetBoardDimensions));

	// Board randomizer
	Button buttonBoardRandomizer({ 0, 0 }, { 20, 20 });
	buttonSetBoardDimensions.setDecal(_boardOTile.Decal());
	buttonBoardRandomizer.alignTopRight(this);
	buttonBoardRandomizer.setPosition(buttonBoardRandomizer.getPosition() + olc::vi2d(0, 25));
	buttonBoardRandomizer.setCallback([&]
		{
			if (_useBigBoard)
				for (size_t z = 0; z < _testBoardBig.size(); z++)
					for (size_t y = 0; y < _testBoardBig[0].size(); y++)
						for (size_t x = 0; x < _testBoardBig[0][0].size(); x++)
							_testBoardBig[z][y][x] = rand() % 3;
			else
			{
				for (size_t y = 0; y < _testBoard.size(); y++)
					for (size_t x = 0; x < _testBoard[0].size(); x++)
						_testBoard[y][x] = rand() % 3;
			}

			std::cout << "Board Randomized!" << std::endl;
		});
	_buttons.push_back(std::make_unique<Button>(buttonBoardRandomizer));

	// Outputs the number of buttons
	std::cout << "[DEbug]: Button count: " << _buttons.size() << std::endl;
}
void TicTacToeGame::drawButtons()
{
	for (auto& button : _buttons)
	{
		if (button->isHidden() == false)
			button->drawSelf(this);
	}
}
void TicTacToeGame::checkButtons()
{
	if (GetMouse(0).bReleased)
		for (auto& button : _buttons)
		{
			if (button->isActive())
				if (button->isPressed(GetMousePos()))
					_redrawScreen = true;
		}
}
