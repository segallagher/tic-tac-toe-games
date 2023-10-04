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

	virtual void drawSelf(olc::PixelGameEngine* gfx);
	// [&] captures all variables for use in lambda (note items that will be out of scope)
	// [&objectName] captures only objectName by reference
	void setCallback(std::function<void()> lambdaCallback);
	std::function<void()>  getCallback();
	virtual bool isPressed(olc::v2d_generic<int> mousePosition);
	bool isPositionWithin(olc::v2d_generic<int> position);

	void setActive(bool isActive);
	bool isActive();
	void setHidden(bool isHidden);
	bool isHidden();

	void setDecal(olc::Decal* buttonDecal);
	olc::Decal* getDecal();

	void setPosition(olc::v2d_generic<int> position);
	olc::v2d_generic<int> getPosition();
	void setDimensions(olc::v2d_generic<int> dimensions);
	olc::v2d_generic<int> getDimensions();

	void center(olc::v2d_generic<int> screenSize);
	void center(olc::PixelGameEngine* gfx);

	void centerHorizontally(int screenWidth);
	void centerHorizontally(olc::v2d_generic<int> screenSize);
	void centerHorizontally(olc::PixelGameEngine* gfx);

	void centerVertically(int screenHeight);
	void centerVertically(olc::v2d_generic<int> screenSize);
	void centerVertically(olc::PixelGameEngine* gfx);

	void alignTopRight(olc::v2d_generic<int> screenSize);
	void alignTopLeft();
	void alignBottomRight(olc::v2d_generic<int> screenSize);
	void alignBottomLeft(olc::v2d_generic<int> screenSize);

protected:
	void adjustDecalScale();

	void setDecalScale(olc::v2d_generic<float> newScale);
	olc::v2d_generic<float> getDecalScale();

protected:
	olc::v2d_generic<float> _decalScale = { 1.0f, 1.0f };
	olc::Decal* _buttonDecal = nullptr;
	olc::v2d_generic<int> _position;
	olc::v2d_generic<int> _dimensions;
	bool _isActive = true;
	bool _isHidden = false;

	std::function<void()> _callback = nullptr;
};

#endif // !BUTTON_HPP


