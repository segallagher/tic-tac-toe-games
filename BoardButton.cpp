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
    // Parameter setting
    auto height = _gameBoard->size();
    auto width = (*_gameBoard)[0].size();
    auto internalOffsets = getInternalClickableOffsets();
    auto tileSize = getTileSize(width, height, internalOffsets);

    // TileBackground
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
            attemptDrawDecal(
                gfx,
                getTileDecal(),
                getTilePosition(tileSize, internalOffsets, x, y),
                tileSize,
                getTileScale(tileSize, getTileDecal()->sprite->Size()),
                olc::Pixel(150, 150, 150)); // Lighter than olc::DARK_GREY

    // Border
    attemptDrawDecal(gfx, getBorderDecal(), getPosition(), getDimensions(), getDecalScale(), olc::DARK_GREY);

    // Top tiles
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
        {
            if ((*_gameBoard)[y][x] == 0) // No tile
                continue;
            else
            {
                olc::Decal* decal = getODecal();
                if ((*_gameBoard)[y][x] == 2)
                    decal = getXDecal();

                attemptDrawDecal(
                    gfx,
                    decal,
                    getTilePosition(tileSize, internalOffsets, x, y),
                    tileSize,
                    getTileScale(tileSize, decal->sprite->Size()));
            }
        }
}
bool BoardButton::isPressed(olc::v2d_generic<int> mousePosition)
{
    _clickedPosition = mousePosition;
    auto internalOffsets = olc::vf2d();
    if (getBorderDecal() != nullptr)
        internalOffsets = getInternalClickableOffsets();

    return Button::isPressed(mousePosition, olc::vf2d(
        float(getDimensions().x) - (internalOffsets.x * 2.0f), 
        float(getDimensions().y) - (internalOffsets.y * 2.0f)),
        internalOffsets);
}
olc::v2d_generic<int> BoardButton::getClickedTile(olc::v2d_generic<int> boardDimensions)
{
    int tileX = (_clickedPosition.x - getPosition().x) / (getDimensions().x / boardDimensions.x);
    int tileY = (_clickedPosition.y - getPosition().y) / (getDimensions().y / boardDimensions.y);
    tileX = std::min(tileX, boardDimensions.x - 1);
    tileY = std::min(tileY, boardDimensions.y - 1);
    return { tileX, tileY };
}
olc::v2d_generic<int> BoardButton::getClickedTile()
{
    std::cout << "[DEMO CODE]: getClickedTile() cycles the clicked tile." << std::endl;
    auto clickedTile = getClickedTile({ int(getBoard()->size()), int(getBoard()[0].size()) });
    (*_gameBoard)[clickedTile.y][clickedTile.x] = ((*_gameBoard)[clickedTile.y][clickedTile.x] + 1) % 3;

        return clickedTile;
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

olc::v2d_generic<int> BoardButton::getBorderOffset()
{
    return _boarderOffset;
}

olc::v2d_generic<float> BoardButton::getInternalClickableOffsets(olc::v2d_generic<int> spriteSize)
{
    return olc::vf2d(
        float(getDimensions().x) * (float(getBorderOffset().x) / float(spriteSize.x)),
        float(getDimensions().y) * (float(getBorderOffset().y) / float(spriteSize.y)));
}
olc::v2d_generic<float> BoardButton::getInternalClickableOffsets()
{
    return getInternalClickableOffsets(getBorderDecal()->sprite->Size());
}

void BoardButton::attemptDrawDecal(olc::PixelGameEngine* gfx, olc::Decal* decal, olc::v2d_generic<float> decalPosition, olc::v2d_generic<int> rectDimensions, olc::v2d_generic<float> decalScale, olc::Pixel decalTint, olc::Pixel errorColor) {
    if (decal != nullptr)
        gfx->DrawDecal(decalPosition, decal, decalScale, decalTint);
    else
        gfx->DrawRect(decalPosition, rectDimensions, errorColor);
};

olc::v2d_generic<float> BoardButton::getTileSize(int boardWidth, int boardHeight, olc::v2d_generic<float> internalOffsets)
{
    return olc::vf2d(float(getDimensions().x - (internalOffsets.x * 2.0f)) / float(boardWidth), float(getDimensions().y - (internalOffsets.y * 2.0f)) / float(boardHeight));
}
olc::v2d_generic<float> BoardButton::getTilePosition(olc::v2d_generic<float> tileSize, olc::v2d_generic<float> internalOffsets, int xOffset, int yOffset)
{
    return olc::vf2d(getPosition()) + (internalOffsets + olc::vf2d(tileSize.x * xOffset, tileSize.y * yOffset));
}
olc::v2d_generic<float> BoardButton::getTileScale(olc::v2d_generic<float> tileSize, olc::v2d_generic<int> spriteSize)
{
    return { tileSize.x / float(spriteSize.x), tileSize.y / float(spriteSize.y) };
}