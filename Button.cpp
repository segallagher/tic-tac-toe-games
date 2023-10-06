// Button.cpp
// Nathan Damon
// 2023-09-30
// Source file for Button (a class that will serve as a clickable item that will call a function given to it).

#include "Button.h"

// Constructors
Button::Button() : Button::Button({ 0, 0 }, { 0, 0 })
{
}

Button::Button(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions)
{
	setPosition(position);
	setDimensions(dimensions);
}

Button::Button(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions, std::function<void()> lambdaCallback)
	: Button::Button(position, dimensions)
{
	setCallback(lambdaCallback);
}

Button::Button(olc::v2d_generic<int> position, olc::Decal& buttonDecal, std::function<void()> lambdaCallback)
	: Button::Button(position, buttonDecal.sprite->Size(), lambdaCallback)
{
}

Button::~Button()
{
}

// ###########################################################################################################################
// Member functions
// ###########################################################################################################################


void Button::drawSelf(olc::PixelGameEngine* gfx)
{
	if (_buttonDecal != nullptr)
		gfx->DrawDecal(getPosition(), _buttonDecal, getDecalScale());
	else
		gfx->DrawRect(getPosition(), getDimensions(), olc::MAGENTA);
}

void Button::setCallback(std::function<void()> lambdaCallback)
{
	_callback = lambdaCallback;
}
std::function<void()> Button::getCallback()
{
	return _callback;
}
bool Button::isPressed(olc::v2d_generic<int> mousePosition)
{
	return isPressed(mousePosition, getDimensions());
}
bool Button::isPressed(olc::v2d_generic<int> mousePosition, olc::v2d_generic<float> buttonDimensions, olc::v2d_generic<float> offset)
{
	if (isActive() && isPositionWithin(mousePosition, buttonDimensions, offset))
	{
		if (_callback != nullptr)
			_callback();
		else
			std::cout << "[DEBUG: Button pressed with no callback]" << std::endl;
		return true;
	}
	return false;
}
bool Button::isPositionWithin(olc::v2d_generic<int> checkPosition)
{
	return isPositionWithin(checkPosition, getDimensions());
}
bool Button::isPositionWithin(olc::v2d_generic<int> checkPosition, olc::v2d_generic<float> buttonDimensions, olc::v2d_generic<float> offset)
{
	auto pos = olc::vf2d(checkPosition - getPosition()) - offset;
	if (pos.x >= 0.0f && pos.x <= buttonDimensions.x)
		if (pos.y >= 0.0f && pos.y <= buttonDimensions.y)
			return true;
	return false;
}

void Button::setActive(bool isActive)
{
	_isActive = isActive;
}
bool Button::isActive()
{
	return _isActive;
}
void Button::setHidden(bool isHidden)
{
	_isHidden = isHidden;
}
bool Button::isHidden()
{
	return _isHidden;
}

void Button::setDecal(olc::Decal* buttonDecal)
{
	_buttonDecal = buttonDecal;
	adjustDecalScale();
}
olc::Decal* Button::getDecal()
{
	return _buttonDecal;
}

void Button::setPosition(olc::v2d_generic<int> position)
{
	_position = position;
}
olc::v2d_generic<int> Button::getPosition()
{
	return _position;
}

void Button::setDimensions(olc::v2d_generic<int> dimensions)
{
	_dimensions = dimensions;
	adjustDecalScale();
}
olc::v2d_generic<int> Button::getDimensions()
{
	return _dimensions;
}


// Centering

void Button::center(olc::v2d_generic<int> screenSize)
{
	centerHorizontally(screenSize.x);
	centerVertically(screenSize.y);
}
void Button::center(olc::PixelGameEngine* gfx)
{
	center(gfx->GetScreenSize());
}
void Button::centerHorizontally(int screenWidth)
{
	setPosition({ (screenWidth - getDimensions().x) / 2, getPosition().y });
}
void Button::centerHorizontally(olc::v2d_generic<int> screenSize)
{
	centerHorizontally(screenSize.x);
}
void Button::centerHorizontally(olc::PixelGameEngine* gfx)
{
	centerHorizontally(gfx->GetScreenSize().x);
}
void Button::centerVertically(int screenHeight)
{
	setPosition({ getPosition().x, (screenHeight - getDimensions().y) / 2 });
}
void Button::centerVertically(olc::v2d_generic<int> screenSize)
{
	centerVertically(screenSize.y);
}
void Button::centerVertically(olc::PixelGameEngine* gfx)
{
	centerVertically(gfx->GetScreenSize().y);
}

void Button::alignTopRight(olc::v2d_generic<int> screenSize)
{
	setPosition({ screenSize.x - getDimensions().x - 1, 0 });
}
void Button::alignTopLeft()
{
	setPosition({ 0, 0 });
}
void Button::alignBottomRight(olc::v2d_generic<int> screenSize)
{
	setPosition({ screenSize.x - getDimensions().x - 1, screenSize.y - getDimensions().y - 1 });
}
void Button::alignBottomLeft(olc::v2d_generic<int> screenSize)
{
	setPosition({ 0, screenSize.y - getDimensions().y - 1});
}


// Protected

void Button::adjustDecalScale()
{
	if (getDecal() != nullptr && getDimensions().x != 0 && getDimensions().y != 0)
	{
		auto xScale = float(getDimensions().x / float(getDecal()->sprite->width));
		auto yScale = float(getDimensions().y / float(getDecal()->sprite->height));
		setDecalScale({ xScale, yScale });
	}
}

void Button::setDecalScale(olc::v2d_generic<float> newScale)
{
	_decalScale = newScale;
}
olc::v2d_generic<float> Button::getDecalScale()
{
	return _decalScale;
}
