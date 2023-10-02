// BoardButton.h
// Nathan Damon
// 2023-10-01
// Source file for class BoardButton

#include "BoardButton.h"

// Constructors
BoardButton::BoardButton() : Button()
{
}
BoardButton::BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions) : Button(position, dimensions)
{
}
BoardButton::BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions, std::function<void()> lambdaCallback) : Button(position, dimensions, lambdaCallback)
{
}
BoardButton::BoardButton(olc::v2d_generic<int> position, olc::Decal& tileDecal, std::function<void()> lambdaCallback) : Button(position, tileDecal, lambdaCallback)
{
}

// ###########################################################################################################################
// Member functions
// ###########################################################################################################################

void BoardButton::drawSelf(olc::PixelGameEngine& gfx)
{
    std::cout << "[Debug]: BoardButton requires a reference or pointer to the board for drawing." << std::endl;
}
bool BoardButton::isPressed(olc::v2d_generic<int> mousePosition)
{
    _clickedPosition = mousePosition;
    return Button::isPressed(mousePosition);
}
olc::v2d_generic<int> BoardButton::getClickedTile(olc::v2d_generic<int> boardDimensions)
{
    int tileX = (_clickedPosition.x - getPosition().x) / boardDimensions.x;
    int tileY = (_clickedPosition.y - getPosition().y) / boardDimensions.y;
    return { tileX, tileY };
}

void BoardButton::setTileDecal(olc::Decal& tileDecal)
{
    setDecal(tileDecal);
}
olc::Decal& BoardButton::getTileDecal()
{
    return getDecal();
}

void BoardButton::setODecal(olc::Decal& oDecal)
{
    _oDecal = &oDecal;
}
olc::Decal& BoardButton::getODecal()
{
    return *_oDecal;
}

void BoardButton::setXDecal(olc::Decal& xDecal)
{
    _xDecal = &xDecal;
}
olc::Decal& BoardButton::getXDecal()
{
    return *_xDecal;
}