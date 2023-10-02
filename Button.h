// Button.h
// Nathan Damon
// 2023-09-30
// Header file for Button (a class that will serve as a clickable item that will call a function given to it).

#include "olcPixelGameEngine.h"

#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button
{
public:
	Button();
	Button(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions);
	Button(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions, std::function<void()> lambdaCallback);
	Button(olc::v2d_generic<int> position, olc::Decal& buttonDecal, std::function<void()> lambdaCallback);
	~Button();

	void drawSelf(olc::PixelGameEngine& gfx);
	void setCallback(std::function<void()> lambdaCallback);
	std::function<void()>  getCallback();
	bool isPressed(olc::v2d_generic<int> mousePosition);
	bool isPositionWithin(olc::v2d_generic<int> position);

	void setActive(bool isActive);
	bool isActive();

	void setDecal(olc::Decal& buttonDecal);
	olc::Decal& getDecal();

	void setPosition(olc::v2d_generic<int> position);
	olc::v2d_generic<int> getPosition();
	void setDimensions(olc::v2d_generic<int> dimensions);
	olc::v2d_generic<int> getDimensions();

	void center(olc::v2d_generic<int> screenSize);
	void centerHorizontally(int screenWidth);
	void centerHorizontally(olc::v2d_generic<int> screenSize);
	void centerVertically(int screenHeight);
	void centerVertically(olc::v2d_generic<int> screenSize);
private:
	olc::Decal* _buttonDecal = nullptr;
	olc::v2d_generic<int> _position;
	olc::v2d_generic<int> _dimensions;
	bool _isActive = true;

	std::function<void()> _callback = nullptr;
};

#endif // !BUTTON_HPP


