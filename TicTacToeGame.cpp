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

	//ultimateBoardSetup();
	regularBoardSetup();
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

void TicTacToeGame::ultimateBoardSetup(olc::v2d_generic<int> bigBoardDimensions, olc::v2d_generic<int> smallBoardDimensions)
{
	_board.setBoardDimensions(bigBoardDimensions);
	for (size_t y = 0; y < _board.getBoardDimensions().y; y++)
	{
		for (size_t x = 0; x < _board.getBoardDimensions().x; x++)
		{
			std::unique_ptr<Board> smallBoard = std::make_unique<Board>(smallBoardDimensions);
			_board.getUnderlyingBoard()[y][x].setChildBoard(smallBoard);
		}
	}
	boardButtonSetup();
}
void TicTacToeGame::regularBoardSetup(olc::v2d_generic<int> boardDimensions)
{
	_board.setBoardDimensions(boardDimensions);
	boardButtonSetup();
}

void TicTacToeGame::boardButtonSetup()
{
	_boardButtons.clear();

	auto boardButtonSetup = [&](BoardButton* boardButtonPtr, olc::vi2d dimensions, Board* board) {
		boardButtonPtr->setDimensions(dimensions);
		boardButtonPtr->setDecal(_boardBorder.Decal());
		boardButtonPtr->setTileDecal(_boardTileBackground.Decal());
		boardButtonPtr->setODecal(_boardOTile.Decal());
		boardButtonPtr->setXDecal(_boardXTile.Decal());
		boardButtonPtr->center(this);

		boardButtonPtr->setBoard(board);
		auto boardButtonCallback = [boardButtonPtr] {
			boardButtonPtr->getBoard()->attemptPlaceTile(boardButtonPtr->getClickedTile());
			};
		boardButtonPtr->setCallback(boardButtonCallback);
		};
	// Board display
	auto superBoardDimensions = _board.getBoardDimensions();
	if (_board.getUnderlyingBoard()[0][0].getChildBoard() == nullptr)
	{
		std::unique_ptr<BoardButton> boardButton = std::make_unique<BoardButton>();
		_boardButtons.push_back(std::move(boardButton));
		auto boardButtonPtr = dynamic_cast<BoardButton*>(_boardButtons.back().get());

		auto boardScale = olc::vi2d(GetScreenSize().x * 700 / 1000, GetScreenSize().y * 700 / 1000);
		boardButtonSetup(boardButtonPtr, boardScale, &_board);
	}
	else
	{
		for (int y = 0; y < superBoardDimensions.y; y++)
		{
			for (int x = 0; x < superBoardDimensions.x; x++)
			{
				std::unique_ptr<BoardButton> boardButton = std::make_unique<BoardButton>();
				_boardButtons.push_back(std::move(boardButton));
				auto boardButtonPtr = dynamic_cast<BoardButton*>(_boardButtons.back().get());

				auto boardScale = olc::vi2d(GetScreenSize().x * (700 / superBoardDimensions.x) / 1000, GetScreenSize().y * (700 / superBoardDimensions.y) / 1000);
				boardButtonSetup(boardButtonPtr, boardScale, _board.getUnderlyingBoard()[y][x].getChildBoard().get());

				// Top left position
				boardButtonPtr->setPosition(
					boardButtonPtr->getPosition() - olc::vi2d(
						boardButtonPtr->getDimensions().x,
						boardButtonPtr->getDimensions().y));

				// Offset into correct position
				boardButtonPtr->setPosition(
					boardButtonPtr->getPosition() + olc::vi2d(
						boardButtonPtr->getDimensions().x * x,
						boardButtonPtr->getDimensions().y * y));
			}
		}
	}

	// Outputs the number of buttons
	std::cout << "[DEBUG]: Button count: " << _regularButtons.size() + _boardButtons.size() << std::endl;
}

void TicTacToeGame::buttonSetup()
{
	_regularButtons.clear();

	// Request dimensions input button
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

			if (_board.getUnderlyingBoard()[0][0].getChildBoard() == nullptr)
			{
				_board.setBoardDimensions({ inX, inY });
			}
			else
			{
				auto superBoardDimensions = _board.getBoardDimensions();
				for (size_t y = 0; y < superBoardDimensions.y; y++)
				{
					for (size_t x = 0; x < superBoardDimensions.x; x++)
					{
						_board.getUnderlyingBoard()[y][x].getChildBoard()->setBoardDimensions({ inX, inY });
						_board.getUnderlyingBoard()[y][x].setState(TileType::Empty);
					}
				}
			}
			std::cout << "Board resized" << std::endl;
		});
	_regularButtons.push_back(std::make_unique<Button>(buttonSetBoardDimensions));

	// Change board type
	Button buttonSwapBoardType({ 0, 0 }, { 20, 20 });
	buttonSwapBoardType.setDecal(_boardXTile.Decal());
	buttonSwapBoardType.alignTopRight(this);
	buttonSwapBoardType.setPosition(buttonSwapBoardType.getPosition() + olc::vi2d(0, 25));
	buttonSwapBoardType.setCallback([&]
		{			
			// If a small board
			if (_board.getUnderlyingBoard()[0][0].getChildBoard() == nullptr)
			{
				// Set big board
				ultimateBoardSetup();
				std::cout << "Switched to Ultimate!:" << std::endl;
			}
			else
			{
				// Set small board
				regularBoardSetup();
				std::cout << "Switched to Regular!:" << std::endl;
			}
		});
	_regularButtons.push_back(std::make_unique<Button>(buttonSwapBoardType));


	// Outputs the number of buttons
	std::cout << "[DEBUG]: Button count: " << _regularButtons.size() + _boardButtons.size() << std::endl;
}
void TicTacToeGame::drawButtons()
{
	for (auto& button : _regularButtons)
	{
		if (button->isHidden() == false)
			button->drawSelf(this);
	}
	for (auto& button : _boardButtons)
	{
		if (button->isHidden() == false)
			button->drawSelf(this);
	}
}
void TicTacToeGame::checkButtons()
{
	if (GetMouse(0).bReleased)
	{
		for (auto& button : _regularButtons)
		{
			if (button->isActive())
				if (button->isPressed(GetMousePos()))
					_redrawScreen = true;
		}
		for (auto& button : _boardButtons)
		{
			if (button->isActive())
				if (button->isPressed(GetMousePos()))
					_redrawScreen = true;
		}
	}
}
