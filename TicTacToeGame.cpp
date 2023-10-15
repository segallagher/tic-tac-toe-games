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

	ultimateBoardSetup();
	//regularBoardSetup();
	buttonSetup();

	return true;
}
bool TicTacToeGame::OnUserUpdate(float fElapsedTime)
{
	// called once per frame

	// Only draw when we need to update
	drawing();

	// Other mechanics here
	checkButtons();

	return true;
}

void TicTacToeGame::startGame()
{
	ultimateBoardSetup({ 3, 3 }, { _optionsBoardSize, _optionsBoardSize });
	Board::setCurrentTileType(TileType::O);
	Board::setCurrentTurn(0);
	setMenu(ButtonSet::Gameplay);
}

void TicTacToeGame::drawing()
{
	// Clear the screen to given color
	Clear(olc::BLACK);

	drawButtons();

	// Is game complete
	if (_boardParentTile.getState() != TileType::GameInProgress && _boardParentTile.getState() != TileType::Empty)
		drawGameWinner();

	// Should the rules be displayed
	if (_drawRules)
		drawGameRulesText();
}
void TicTacToeGame::drawGameWinner()
{
	if (_currentButtonSet != ButtonSet::Gameplay)
	{
		if (_resetGameButtonPtr != nullptr)
			_resetGameButtonPtr->setActive(false);
		return;
	}

	if (_resetGameButtonPtr != nullptr)
		_resetGameButtonPtr->setActive(true);

	float backGroundDisplayRatio = 0.9f;
	float winnerTileDisplayRatio = 0.45f;
	auto backGroundPosition = olc::vf2d(GetScreenSize() * int(1000.0f * (1.0f - backGroundDisplayRatio) / 2.0f) / 1000);
	auto winnerTilePosition = olc::vf2d(GetScreenSize() * int(1000.0f * (1.0f - winnerTileDisplayRatio) / 2.0f) / 1000);
	auto titleOffset = olc::vf2d(90, 20);
	auto winnerTileOffset = olc::vf2d(70, 40);

	olc::vf2d backgroundDecalScale = {
		float(GetScreenSize().x * int(1000.0f * backGroundDisplayRatio) / 1000) / float(_blankXOTile.Sprite()->width),
		float(GetScreenSize().y * int(1000.0f * backGroundDisplayRatio) / 1000) / float(_blankXOTile.Sprite()->height)
	};
	olc::vf2d winnerDecalScale = {
		float(GetScreenSize().x * int(1000.0f * winnerTileDisplayRatio) / 1000) / float(_blankXOTile.Sprite()->width),
		float(GetScreenSize().y * int(1000.0f * winnerTileDisplayRatio) / 1000) / float(_blankXOTile.Sprite()->height)
	};

	// Set decal
	auto decalPtr = _boardOTile.Decal();
	if(_boardParentTile.getState() == TileType::X)
		decalPtr = _boardXTile.Decal();

	// Draw
	DrawDecal(backGroundPosition, _blankXOTile.Decal(), backgroundDecalScale, olc::GREY);
	DrawDecal(winnerTilePosition, decalPtr, winnerDecalScale);
	DrawStringDecal(backGroundPosition + titleOffset, "WINNER", olc::DARK_GREY, { 1.25f, 1.25f });
}
void TicTacToeGame::drawGameRulesText()
{
	float displayRatio = 0.9f;
	auto rulesPosition = olc::vf2d(GetScreenSize() * int(1000.0f * (1.0f - displayRatio) / 2.0f) / 1000);
	auto rulesTitleOffset = olc::vf2d(65, 20);
	auto rulesTextOffset = olc::vf2d(30, 40);

	olc::vf2d decalScale = {
		float(GetScreenSize().x * int(1000.0f * displayRatio) / 1000) / float(_blankXOTile.Sprite()->width),
		float(GetScreenSize().y * int(1000.0f * displayRatio) / 1000) / float(_blankXOTile.Sprite()->height)
	};

	DrawDecal(rulesPosition, _blankXOTile.Decal(), decalScale);
	DrawStringDecal(rulesPosition + rulesTitleOffset, "Game Rules", olc::GREY, {1.25f, 1.25f});
	DrawStringDecal(rulesPosition + rulesTextOffset, getGameRulesText(), olc::GREY);
}
std::string TicTacToeGame::getGameRulesText()
{
	switch (_board.getRuleset())
	{
	case nRow:
		return _nRowGameRulesText;
	default:
	case endOfList:
		return "Ruleset error: change gamemode";
	}
}

void TicTacToeGame::loadSprites()
{
	_boardBorder.Load("./Sprites/BoardBorder.png");
	_boardTileBackground.Load("./Sprites/TileBackground.png");
	_boardOTile.Load("./Sprites/OTile.png");
	_boardXTile.Load("./Sprites/XTile.png");
	_blankXOTile.Load("./Sprites/BlankXOTile.png");
}

void TicTacToeGame::ultimateBoardSetup(olc::v2d_generic<int> bigBoardDimensions, olc::v2d_generic<int> smallBoardDimensions)
{
	_boardParentTile.setState(TileType::Empty);
	_board.setParentTile(&_boardParentTile);
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
	_boardParentTile.setState(TileType::Empty);
	_board.setParentTile(&_boardParentTile);
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
}

void TicTacToeGame::setMenu(ButtonSet buttonSet)
{
	_currentButtonSet = buttonSet;
}

void TicTacToeGame::mainMenuButtonSetup()
{
	_mainMenuButtons.clear();

	olc::vi2d buttonDimensions = { 100, 40 };
	int spacing = 10;

	// Button: Start game
	{
		Button button({ 0, 0 }, buttonDimensions);
		button.setDecal(_blankXOTile.Decal());
		button.setCallback([&]
			{
				startGame();
			});
		_mainMenuButtons.push_back(std::make_unique<Button>(button));		
	}

	// Button: Options menu
	{
		Button button({ 0, 0 }, buttonDimensions);
		button.setDecal(_blankXOTile.Decal());
		button.setCallback([&]
			{
				setMenu(ButtonSet::OptionsMenu);
			});
		_mainMenuButtons.push_back(std::make_unique<Button>(button));
	}

	// Button: Quit game
	{
		Button button({ 0, 0 }, buttonDimensions);
		button.setDecal(_blankXOTile.Decal());
		button.setCallback([&]
			{
				olc_Terminate();
			});
		_mainMenuButtons.push_back(std::make_unique<Button>(button));
	}

	// Place buttons
	int startPosition = (GetScreenSize().y - _mainMenuButtons.size() * (buttonDimensions.y + spacing)) / 2;
	int offset = 0;
	for (auto& buttonPtr : _mainMenuButtons)
	{
		olc::vi2d position = { 0, startPosition + (buttonDimensions.y + spacing) * offset };

		buttonPtr->setPosition(position);
		buttonPtr->centerHorizontally(this);
		offset++;
	}
}

void TicTacToeGame::optionsMenuButtonSetup()
{
	_optionsMenuButtons.clear();

	// Button: Return to main menu
	{
		Button button({ 0, 0 }, { 20, 20 });
		button.setDecal(_blankXOTile.Decal());
		button.setCallback([&]
			{
				setMenu(ButtonSet::MainMenu);
			});
		_optionsMenuButtons.push_back(std::make_unique<Button>(button));
	}

	// Button: Board Size
	{
		int xPosition = 40;
		int yPosition = 40;

		int xOffset = 40;
		int yOffset = 0;

		// Decrement button
		{
			Button button({ xPosition, yPosition }, { 20, 20 });
			button.setDecal(_blankXOTile.Decal());
			button.setCallback([&]
				{
					setOptionsBoardSize(getOptionsBoardSize() - 1);
				});
			_optionsMenuButtons.push_back(std::make_unique<Button>(button));
		}

		// Increment button
		{
			Button button({ xPosition + xOffset, yPosition + yOffset }, { 20, 20 });
			button.setDecal(_blankXOTile.Decal());
			button.setCallback([&]
				{
					setOptionsBoardSize(getOptionsBoardSize() + 1);
				});
			_optionsMenuButtons.push_back(std::make_unique<Button>(button));
		}
	}

	// Button: Gamemode
	{
		int xPosition = 40;
		int yPosition = 80;

		int xOffset = 40;
		int yOffset = 0;

		// Decrement button
		{
			Button button({ xPosition, yPosition }, { 20, 20 });
			button.setDecal(_blankXOTile.Decal());
			button.setCallback([&]
				{
					previousGameMode();
				});
			_optionsMenuButtons.push_back(std::make_unique<Button>(button));
		}

		// Increment button
		{
			Button button({ xPosition + xOffset, yPosition + yOffset }, { 20, 20 });
			button.setDecal(_blankXOTile.Decal());
			button.setCallback([&]
				{
					nextGameMode();
				});
			_optionsMenuButtons.push_back(std::make_unique<Button>(button));
		}
	}

	// Buttons: Show and close rules
	{
		// Button: Show rules
		Button buttonShow({ 0, 0 }, { 20, 20 });
		buttonShow.setDecal(_blankXOTile.Decal());
		buttonShow.alignTopRight(this);
		_optionsMenuButtons.push_back(std::make_unique<Button>(buttonShow));

		auto buttonShowPtr = _optionsMenuButtons.back().get();

		// Button: Close rules
		Button buttonClose({ 0, 0 }, GetScreenSize());
		buttonClose.setDecal(_blankXOTile.Decal());
		buttonClose.setActive(false);
		buttonClose.setHidden(true);
		_optionsMenuButtons.push_back(std::make_unique<Button>(buttonClose));

		auto buttonClosePtr = _optionsMenuButtons.back().get();

		// Set callbacks ###################################################33

		// Button callback: Show rules
		buttonShowPtr->setCallback([&, buttonShowPtr, buttonClosePtr]
			{
				_drawRules = true;
				buttonShowPtr->setActive(false);
				buttonClosePtr->setActive(true);
			});

		// Button callback: Close rules
		buttonClosePtr->setCallback([&, buttonShowPtr, buttonClosePtr]
			{
				_drawRules = false;
				buttonShowPtr->setActive(true);
				buttonClosePtr->setActive(false);
			});
	}
}

void TicTacToeGame::gameplayButtonSetup()
{
	_gameplayButtons.clear();

	// Button: Quit to main menu
	{
		Button button({ 0, 0 }, { 20, 20 });
		button.setDecal(_blankXOTile.Decal());
		button.setCallback([&]
			{
				setMenu(ButtonSet::MainMenu);
			});
		_gameplayButtons.push_back(std::make_unique<Button>(button));
	}

	// Button: Return to main on win
	{
		Button button({ 0, 0 }, GetScreenSize());
		button.setDecal(_boardXTile.Decal());
		button.setHidden(true);
		button.setActive(false);
		_gameplayButtons.push_back(std::make_unique<Button>(button));
		auto buttonptr = _gameplayButtons.back().get();
		buttonptr->setCallback([&, buttonptr]
			{
				buttonptr->setActive(false);
				setMenu(ButtonSet::MainMenu);
			});
		// Button is set active through this pointer on game win
		_resetGameButtonPtr = buttonptr;
	}

	// Buttons: Show and close rules
	{
		// Button: Show rules
		Button buttonShow({ 0, 0 }, { 20, 20 });
		buttonShow.setDecal(_blankXOTile.Decal());
		buttonShow.alignTopRight(this);
		_gameplayButtons.push_back(std::make_unique<Button>(buttonShow));

		auto buttonShowPtr = _gameplayButtons.back().get();

		// Button: Close rules
		Button buttonClose({ 0, 0 }, GetScreenSize());
		buttonClose.setDecal(_blankXOTile.Decal());
		buttonClose.setActive(false);
		buttonClose.setHidden(true);
		_gameplayButtons.push_back(std::make_unique<Button>(buttonClose));

		auto buttonClosePtr = _gameplayButtons.back().get();

		// Set callbacks ###################################################33

		// Button callback: Show rules
		buttonShowPtr->setCallback([&, buttonShowPtr, buttonClosePtr]
			{
				_drawRules = true;
				buttonShowPtr->setActive(false);
				buttonClosePtr->setActive(true);
			});

		// Button callback: Close rules
		buttonClosePtr->setCallback([&, buttonShowPtr, buttonClosePtr]
			{
				_drawRules = false;
				buttonShowPtr->setActive(true);
				buttonClosePtr->setActive(false);
			});
	}
}

void TicTacToeGame::buttonSetup()
{
	mainMenuButtonSetup();
	optionsMenuButtonSetup();
	gameplayButtonSetup();

#ifdef DEBUG
	// Outputs the number of buttons
	auto buttonCount =
		_mainMenuButtons.size() +
		_optionsMenuButtons.size() +
		_gameplayButtons.size() +
		_boardButtons.size();
	std::cout << "[DEBUG]: Button count: " << buttonCount << std::endl;
#endif // DEBUG
}

void TicTacToeGame::drawButtons()
{
	switch (_currentButtonSet)
	{
	default:
	case ButtonSet::MainMenu:
		drawButtons(_mainMenuButtons);
		break;
	case ButtonSet::OptionsMenu:
		drawButtons(_optionsMenuButtons);
		break;
	case ButtonSet::Gameplay:
		drawButtons(_gameplayButtons);
		drawButtons(_boardButtons);
		break;
	}
}
void TicTacToeGame::drawButtons(std::vector<std::unique_ptr<Button>>& buttons)
{
	for (auto& button : buttons)
	{
		if (button->isHidden() == false)
			button->drawSelf(this);
	}
}
void TicTacToeGame::drawButtons(std::vector<std::unique_ptr<BoardButton>>& buttons)
{
	for (auto& button : buttons)
	{
		if (button->isHidden() == false)
			button->drawSelf(this);
	}
}

void TicTacToeGame::checkButtons()
{
	if (GetMouse(0).bReleased)
	{
		switch (_currentButtonSet)
		{
		default:
		case ButtonSet::MainMenu:
			checkButtons(_mainMenuButtons);
			break;
		case ButtonSet::OptionsMenu:
			checkButtons(_optionsMenuButtons);
			break;
		case ButtonSet::Gameplay:
			if (checkButtons(_gameplayButtons))
				return;
			checkButtons(_boardButtons);
			break;
		}

	}
}
bool TicTacToeGame::checkButtons(std::vector<std::unique_ptr<Button>>& buttons)
{
	for (size_t i = buttons.size(); i >= 1; --i) {
		if (buttons[i - 1]->isActive())
			if (buttons[i - 1]->isPressed(GetMousePos()))
				return true;
	}
	return false;
}
bool TicTacToeGame::checkButtons(std::vector<std::unique_ptr<BoardButton>>& buttons)
{
	for (size_t i = buttons.size(); i >= 1; --i) {
		if (buttons[i - 1]->isActive())
			if (buttons[i - 1]->isPressed(GetMousePos()))
				return true;
	}
	return false;
}

void TicTacToeGame::setButtonsActive(std::vector<std::unique_ptr<Button>>& buttons, bool active)
{
	for (auto& button : buttons)
		button->setActive(active);
}

void TicTacToeGame::setOptionsBoardSize(int size)
{
	if (size == 2) // Do not allow a 2x2
	{
		if (_optionsBoardSize < size)
			size = 3;
		else
			size = 1;
	}

	_optionsBoardSize = std::max(std::min(size, _boardSizeMax), _boardSizeMin);

#ifdef DEBUG
	std::cout << "[DEBUG]: Board size set to " << _optionsBoardSize << std::endl;
#endif // DEBUG
}
int TicTacToeGame::getOptionsBoardSize()
{
	return _optionsBoardSize;
}

void TicTacToeGame::nextGameMode()
{
	auto currentRuleset = _board.getRuleset();
	currentRuleset = static_cast<GameMode>(static_cast<int>(currentRuleset) + 1);
	if(GameMode::endOfList) // Wrap around
		currentRuleset = static_cast<GameMode>(0);

	_board.setRuleset(currentRuleset);
#ifdef DEBUG
	std::cout << "[DEBUG]: Ruleset set to " << currentRuleset << std::endl;
#endif // DEBUG
}
void TicTacToeGame::previousGameMode()
{
	auto currentRuleset = _board.getRuleset();
	if(static_cast<int>(currentRuleset) - 1 < 0) // Wrap around
		currentRuleset = static_cast<GameMode>(static_cast<int>(GameMode::endOfList) - 1);
	else
		currentRuleset = static_cast<GameMode>(static_cast<int>(currentRuleset) - 1);

	_board.setRuleset(currentRuleset);
#ifdef DEBUG
	std::cout << "[DEBUG]: Ruleset set to " << currentRuleset << std::endl;
#endif // DEBUG
}
