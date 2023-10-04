// BoardButton.h
// Nathan Damon
// 2023-10-01
// Header file for BoardButton (a button that will give an x, y coordinate based on clicked area and internal size).

#include "Button.h"

#ifndef BOARDBUTTON_HPP
#define BOARDBUTTON_HPP

class BoardButton : public Button
{
public:
	BoardButton();
	BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions);
	BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions, std::function<void()> lambdaCallback);
	BoardButton(olc::v2d_generic<int> position, olc::Decal& buttonDecal, std::function<void()> lambdaCallback);

	// Needs testing code
	virtual void drawSelf(olc::PixelGameEngine* gfx) override;
	virtual bool isPressed(olc::v2d_generic<int> mousePosition) override;
	olc::v2d_generic<int> getClickedTile(olc::v2d_generic<int> boardDimensions);
	// Needs testing
	olc::v2d_generic<int> getClickedTile();

	void setBorderDecal(olc::Decal* borderDecal);
	olc::Decal* getBorderDecal();
	void setTileDecal(olc::Decal* tileDecal);
	olc::Decal* getTileDecal();
	void setODecal(olc::Decal* oDecal);
	olc::Decal* getODecal();
	void setXDecal(olc::Decal* xDecal);
	olc::Decal* getXDecal();

	// Needs testing code
	void setBoard(std::vector<std::vector<int>>* board);
	std::vector<std::vector<int>>* getBoard();

protected:
	// Needs pointer to board

	olc::Decal* _tileBackgroundDecal = nullptr;
	olc::Decal* _oDecal = nullptr;
	olc::Decal* _xDecal = nullptr;

	olc::v2d_generic<int> _clickedPosition;

	// Testing board
	std::vector<std::vector<int>>* _gameBoard = nullptr;
};

#endif // !BOARDBUTTON_HPP



