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

	// Draws the button on the screen
	virtual void drawSelf(olc::PixelGameEngine* gfx);
	// Sets the callback function that is called on button clicked
	// [&] captures all variables for use in lambda (note items that will be out of scope)
	// [&objectName] captures only objectName by reference
	void setCallback(std::function<void()> lambdaCallback);
	// Returns the callback function
	std::function<void()>  getCallback();
	// Calls the callback function if the button is active and the given mouse position is within the button's clickable area
	virtual bool isPressed(olc::v2d_generic<int> mousePosition);
	// Calls the callback function if the button is active and the given mouse position is within the dimensions offset by the given offset
	bool isPressed(olc::v2d_generic<int> mousePosition, olc::v2d_generic<float> buttonDimensions, olc::v2d_generic<float> offset = { 0, 0 });
	// Checks if the given position is in the button's clickable area
	bool isPositionWithin(olc::v2d_generic<int> position);
	// Checks if the given position is in the given dimensions offset by the given offset
	bool isPositionWithin(olc::v2d_generic<int> checkPosition, olc::v2d_generic<float> buttonDimensions, olc::v2d_generic<float> offset = { 0, 0 });

	// Sets the button to be active or not (if false, will not be clickable)
	void setActive(bool isActive);
	// Returns true if the button is active
	bool isActive();
	// Sets the button to display or not (if false, will not show the button. Does not stop it from being clicked)
	void setHidden(bool isHidden);
	// Returns true if the button is hidden
	bool isHidden();

	// Sets the display image for the button
	void setDecal(olc::Decal* buttonDecal);
	// Gets the buttons display image
	olc::Decal* getDecal();

	// Sets the button's position based on the top left corner of the screen and button
	void setPosition(olc::v2d_generic<int> position);
	// Returns the button's position
	olc::v2d_generic<int> getPosition();
	// Sets the width and height of the button in pixels on the screen
	void setDimensions(olc::v2d_generic<int> dimensions);
	// Returns the width and height of the button in pixels on the screen
	olc::v2d_generic<int> getDimensions();

	// Centers the button based on the given screen size
	void center(olc::v2d_generic<int> screenSize);
	// Centers the button on the screen
	void center(olc::PixelGameEngine* gfx);

	// Centers the button horizontally based on the given screen width
	void centerHorizontally(int screenWidth);
	// Centers the button horizontally based on the given screen size
	void centerHorizontally(olc::v2d_generic<int> screenSize);
	// Centers the button horizontally on the screen
	void centerHorizontally(olc::PixelGameEngine* gfx);

	// Centers the button vertically based on the given screen height
	void centerVertically(int screenHeight);
	// Centers the button vertically based on the given screen size
	void centerVertically(olc::v2d_generic<int> screenSize);
	// Centers the button vertically on the screen
	void centerVertically(olc::PixelGameEngine* gfx);

	// Puts the button in the top right corner of the given screen size
	void alignTopRight(olc::v2d_generic<int> screenSize);
	// Puts the button in the top right corner of the screen
	void alignTopRight(olc::PixelGameEngine* gfx);
	// Puts the button in the top left corner
	void alignTopLeft();
	// Puts the button in the bottom right corner of the given screen size
	void alignBottomRight(olc::v2d_generic<int> screenSize);
	// Puts the button in the bottom right corner of the screen
	void alignBottomRight(olc::PixelGameEngine* gfx);
	// Puts the button in the bottom left corner of the given screen size
	void alignBottomLeft(olc::v2d_generic<int> screenSize);
	// Puts the button in the bottom left corner of the screen
	void alignBottomLeft(olc::PixelGameEngine* gfx);

protected:
	// Adjusts the scale of the decal to fit inside the button's dimensions
	void adjustDecalScale();

	// Sets the scale factor for the decal such that it fits inside the button's dimensions
	void setDecalScale(olc::v2d_generic<float> newScale);
	// Gets the decal's scale factor for fitting inside the button's dimensions
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


