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

void BoardButton::drawSelf(olc::PixelGameEngine* gfx)
{
    auto attemptDrawDecal = [&](olc::Decal* decal, olc::v2d_generic<float> decalPosition, olc::v2d_generic<int> rectDimensions, olc::v2d_generic<float> decalScale, olc::Pixel errorColor, olc::Pixel decalTint = olc::WHITE) {
        if (decal != nullptr)
            gfx->DrawDecal(decalPosition, decal, decalScale, decalTint);
        else
            gfx->DrawRect(decalPosition, rectDimensions, errorColor);
        };

    // Parameter setting
    auto boarderOffset = olc::vi2d(32, 32);
    auto width = _gameBoard->size();
    auto height = _gameBoard[0].size();
    auto internalOffsets = olc::vf2d(
        float(getDimensions().x) * (float(boarderOffset.x) / float(getBorderDecal()->sprite->width)),
        float(getDimensions().y) * (float(boarderOffset.y) / float(getBorderDecal()->sprite->height)));
    auto tileSize = olc::vf2d(float(getDimensions().x - (internalOffsets.x * 2.0f)) / float(width), float(getDimensions().y - (internalOffsets.y * 2.0f)) / float(height));


    // TileBackground
    for (size_t y = 0; y < width; y++)
        for (size_t x = 0; x < height; x++)
            attemptDrawDecal(
                getTileDecal(),
                olc::vf2d(getPosition()) + (internalOffsets + olc::vf2d(tileSize.x * x, tileSize.y * y)),
                tileSize,
                { tileSize.x / float(getTileDecal()->sprite->Size().x), tileSize.y / float(getTileDecal()->sprite->Size().y) },
                olc::MAGENTA,
                olc::GREY);

    // Border
    attemptDrawDecal(getBorderDecal(), getPosition(), getDimensions(), getDecalScale(), olc::MAGENTA, olc::GREY);

    // Top tiles
    for (size_t y = 0; y < width; y++)
        for (size_t x = 0; x < height; x++)
        {
            if ((*_gameBoard)[y][x] == 0) // No tile
                continue;
            else
            {
                olc::Decal* decal = getODecal();
                if ((*_gameBoard)[y][x] == 2)
                    decal = getXDecal();

                attemptDrawDecal(
                    decal,
                    olc::vf2d(getPosition()) + (internalOffsets + olc::vf2d(tileSize.x * x, tileSize.y * y)),
                    tileSize,
                    olc::vf2d(tileSize.x / float(getODecal()->sprite->Size().x), tileSize.y / float(getODecal()->sprite->Size().y)),
                    olc::MAGENTA);
            }
        }
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

void BoardButton::setBorderDecal(olc::Decal* borderDecal)
{
    setDecal(borderDecal);
}
olc::Decal* BoardButton::getBorderDecal()
{
    return getDecal();
}

void BoardButton::setTileDecal(olc::Decal* tileDecal)
{
    _tileBackgroundDecal = tileDecal;
}
olc::Decal* BoardButton::getTileDecal()
{
    return _tileBackgroundDecal;
}

void BoardButton::setODecal(olc::Decal* oDecal)
{
    _oDecal = oDecal;
}
olc::Decal* BoardButton::getODecal()
{
    return _oDecal;
}

void BoardButton::setXDecal(olc::Decal* xDecal)
{
    _xDecal = xDecal;
}
olc::Decal* BoardButton::getXDecal()
{
    return _xDecal;
}

void BoardButton::setBoard(std::vector<std::vector<int>>* board)
{
    _gameBoard = board;
    //setCallback([&][&fakeBoard, &boardButton]{ fakeBoard.setTile(boardButton.getClickedTile(fakeBoard.getDimensions())); };)
    std::cout << "[Debug]: BoardButton requires a reference or pointer to the board and a CALLBACK to be set." << std::endl;
}

std::vector<std::vector<int>>* BoardButton::getBoard()
{
    return _gameBoard;
}
