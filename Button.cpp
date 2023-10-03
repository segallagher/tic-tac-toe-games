// Button.cpp
// Nathan Damon
// 2023-09-30
// Source file for Button (a class that will serve as a clickable item that will call a function given to it).

#include "Button.h";

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


void Button::drawSelf(olc::PixelGameEngine& gfx)
{
	if (_buttonDecal != nullptr)
		gfx.DrawDecal(getPosition(), _buttonDecal);
	else
		gfx.DrawRect(getPosition(), getDimensions(), olc::MAGENTA);
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
	if (isActive() && isPositionWithin(mousePosition))
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
	auto pos = checkPosition - getPosition();
	if (pos.x >= 0 && pos.x < getDimensions().x)
		if (pos.y >= 0 && pos.y < getDimensions().y)
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

void Button::setDecal(olc::Decal& buttonDecal)
{
	_buttonDecal = &buttonDecal;
}
olc::Decal& Button::getDecal()
{
	return *_buttonDecal;
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
void Button::centerHorizontally(int screenWidth)
{
	setPosition({ (screenWidth - getDimensions().x) / 2, getPosition().y });
}
void Button::centerHorizontally(olc::v2d_generic<int> screenSize)
{
	centerHorizontally(screenSize.x);
}
void Button::centerVertically(int screenHeight)
{
	setPosition({ getPosition().x, (screenHeight - getDimensions().y) / 2 });
}
void Button::centerVertically(olc::v2d_generic<int> screenSize)
{
	centerVertically(screenSize.y);
}