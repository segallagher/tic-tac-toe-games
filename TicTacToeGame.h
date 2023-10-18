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

#define DEBUG

class TicTacToeGame : public olc::PixelGameEngine
{
	enum class ButtonSet
	{
		MainMenu,
		OptionsMenu,
		Gameplay
	};

public:
	TicTacToeGame();

public:
	// Called once at the start, so create things here
	bool OnUserCreate() override;
	// Called once per frame
	bool OnUserUpdate(float fElapsedTime) override;

	void startGame();

	// Loads the sprites for the game
	void loadSprites();
	// Draws everything that needs to be drawn
	void drawing();

	// Displays game win
	void drawGameWinner();

	// Displays text
	void drawPopup();
	// Sets the text for the popup
	void setPopup(std::string title, std::string text);

	// Gets the current gamemode's rules text
	std::string getGameRulesText();

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
	// Menus
	// ######################

	// Sets the current menu/items to display
	void setMenu(ButtonSet buttonSet);
	// Sets up the main menu buttons
	void mainMenuButtonSetup();
	// Sets up the options menu buttons
	void optionsMenuButtonSetup();
	// Sets up the gameplay buttons
	void gameplayButtonSetup();

	// ######################
	// Buttons
	// ######################

	// Sets up the buttons
	void buttonSetup();
	// Draws the menu and button items
	void drawMenuItems();
	// Draws the given buttons
	void drawButtons(std::vector<std::unique_ptr<Button>>& buttons);
	void drawButtons(std::vector<std::unique_ptr<BoardButton>>& buttons);
	// Checks the buttons for clicking
	void checkButtons();
	bool checkButtons(std::vector<std::unique_ptr<Button>>& buttons);
	bool checkButtons(std::vector<std::unique_ptr<BoardButton>>& buttons);

	// Sets given buttons to the specified active state
	void setButtonsActive(std::vector<std::unique_ptr<Button>>& buttons, bool active);

	// ######################
	// Options functions
	// ######################

	// Gets the current ruleset as a string
	std::string getRulesetAsString(GameMode ruleset);
	// Draws the text display for the main menu
	void drawMainMenuDetails();
	// Draws the text display for the options menu
	void drawOptionsMenuDetails();

	// Sets the board's size
	void setOptionsBoardSize(int size);
	// Gets the board's size
	int getOptionsBoardSize();
	// Switches to the next gamemode
	void nextGameMode();
	// Switches to the previous gamemode
	void previousGameMode();

public:
	// ######################
	// Variables
	// ######################

	// Specifies which set of buttons to use
	ButtonSet _currentButtonSet = ButtonSet::MainMenu;

	// Buttons
	std::vector<std::unique_ptr<Button>> _mainMenuButtons = std::vector<std::unique_ptr<Button>>();
	std::vector<std::unique_ptr<Button>> _optionsMenuButtons = std::vector<std::unique_ptr<Button>>();
	std::vector<std::unique_ptr<Button>> _gameplayButtons = std::vector<std::unique_ptr<Button>>();
	std::vector<std::unique_ptr<BoardButton>> _boardButtons = std::vector<std::unique_ptr<BoardButton>>();
	
	// Used by rule display buttons
	bool _drawPopup = false;
	std::string _popupTitle;
	std::string _popupText;
	Button* _resetGameButtonPtr;

	// Will only hold the game result that _board will give it
	Board::Tile _boardParentTile;
	Board _board;

	// Options
	bool _isUltimateBoard = true;
	int _optionsBoardSize = 3;
	int _boardSizeMin = 3;
	int _boardSizeMax = 20;

	// Temporay! <- definately speled right
	std::string _nRowGameRulesText =
		"Get n (max of 5) of\n"
		"your tiles in a row\n"
		"to win a board.";

	// ######################
	// Sprites
	// ######################

	// Main menu
	olc::Renderable _startGameTile;
	olc::Renderable _optionsTile;
	olc::Renderable _quitTile;

	// Gameplay
	olc::Renderable _boardBorder;
	olc::Renderable _boardTileBackground;
	olc::Renderable _boardOTile;
	olc::Renderable _boardXTile;

	// Options
	olc::Renderable _rightArrow;
	olc::Renderable _leftArrow;
	olc::Renderable _leftArrowWTail;

	// Other
	olc::Renderable _blankXOTile;
	olc::Renderable _questionMarkTile;
};

#endif // !TicTacToeGame_HPP