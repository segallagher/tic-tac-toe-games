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
	// Checks if the Button was pressed
	virtual bool isPressed(olc::v2d_generic<int> mousePosition) override;
	// Gets the clicked tile inside the BoardButton based on the boardDimensions given
	olc::v2d_generic<int> getClickedTile(olc::v2d_generic<int> boardDimensions);
	// Needs testing
	// Gets the clicked tile inside the BoardButton based on the internally stored pointer to a board
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
	// Returns pixel width and height of the border
	olc::v2d_generic<int> getBorderOffset();
	// Returns the scaled offset of the tiles from the BoardButton's position based on the given width and height
	olc::v2d_generic<float> getInternalClickableOffsets(olc::v2d_generic<int> spriteSize);
	// Returns the scaled offset of the tiles from the BoardButton's position
	olc::v2d_generic<float> getInternalClickableOffsets();

	// Returns the size of tiles based on the given inputs
	olc::v2d_generic<float> getTileSize(int boardWidth, int boardHeight, olc::v2d_generic<float> internalOffsets = { 0, 0 });

protected:
	void attemptDrawDecal(olc::PixelGameEngine* gfx, olc::Decal* decal, olc::v2d_generic<float> decalPosition, olc::v2d_generic<int> rectDimensions, olc::v2d_generic<float> decalScale, olc::Pixel decalTint = olc::WHITE, olc::Pixel errorColor = olc::MAGENTA);
	// Needs testing
	olc::v2d_generic<float> getTilePosition(olc::v2d_generic<float> tileSize, olc::v2d_generic<float> internalOffsets, int xOffset, int yOffset);
	olc::v2d_generic<float> getTileScale(olc::v2d_generic<float> tileSize, olc::v2d_generic<int> spriteSize);


	// Needs pointer to board

	olc::Decal* _tileBackgroundDecal = nullptr;
	olc::Decal* _oDecal = nullptr;
	olc::Decal* _xDecal = nullptr;

	olc::v2d_generic<int> _clickedPosition;
	olc::v2d_generic<int> _boarderOffset = { 32, 32 };

	// Testing board
	std::vector<std::vector<int>>* _gameBoard = nullptr;
};

#endif // !BOARDBUTTON_HPP



