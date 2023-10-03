// ButtonTest.cpp
// Nathan Damon
// 2023-10-01
// This source file contains the unit tests for class Button

#include "Button.h"
#include "Button.h" // Double-inclusion test
#include "doctest.h"

class ButtonProtectedGetter : public Button
{
	public: 
		olc::v2d_generic<float> getButtonDecalScale() { return getDecalScale(); }
		void setButtonDecalScale(olc::v2d_generic<float> newScale) { setDecalScale(newScale); }
};

TEST_CASE("Button Constructors")
{
	// Test values
	olc::vi2d position = { 10, 20 };
	olc::vi2d dimensions = { 30, 40 };
	bool callbackWorks = false;
	auto callback = [&callbackWorks] {callbackWorks = true; };
	olc::Sprite sprite(dimensions.x, dimensions.y);

	// Default button
	Button button;
	CHECK(button.getPosition() == olc::vi2d());
	CHECK(button.getDimensions() == olc::vi2d());

	// Button at a position and with dimensions
	Button button1(position, dimensions);
	CHECK(button1.getPosition() == position);
	CHECK(button1.getDimensions() == dimensions);

	// Button at a position and with dimensions and a callback
	Button button2(position, dimensions, callback);
	CHECK(button2.getPosition() == position);
	CHECK(button2.getDimensions() == dimensions);
	button2.getCallback()();
	CHECK(callbackWorks == true);

	// Button at a position with a decal and a callback
	// Cannot be tested properly due to Decal's dependence on olcPixelGameEngine implementation
	callbackWorks = false;
	Button button3(position, sprite.Size(), callback);
	CHECK(button3.getPosition() == position);
	CHECK(button3.getDimensions() == dimensions);
	button3.getCallback()();
	CHECK(callbackWorks == true);
}

TEST_CASE("Button Position and Dimension")
{
	Button button;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			button.setPosition({ x, y });			
			CHECK(button.getPosition() == olc::vi2d{x, y});
		}
	}
	
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			button.setDimensions({ x, y });
			CHECK(button.getDimensions() == olc::vi2d{ x, y });
		}
	}

	int dimx = 4;
	int dimy = 5;
	button.setDimensions({ dimx, dimy });
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			// Horizontal
			button.setPosition({ 0, 0 });
			button.centerHorizontally({ x, y });
			CHECK(button.getPosition() == olc::vi2d{ (x - dimx) / 2, 0});

			// Vertical
			button.setPosition({ 0, 0 });
			button.centerVertically({ x, y });
			CHECK(button.getPosition() == olc::vi2d{ 0, (y - dimy) / 2});

			// Horizontal and Vertical
			button.setPosition({ 0, 0 });
			button.center({ x, y });
			CHECK(button.getPosition() == olc::vi2d{ (x - dimx) / 2, (y - dimy) / 2 });
		}
	}

	// Aligning with a corner
	auto screenSize = olc::vi2d{ 100, 100 };
	auto rightLeftExtremePositions = olc::vi2d{ screenSize.x - button.getDimensions().x - 1, screenSize.y - button.getDimensions().y - 1 };
	
	button.center(screenSize);
	button.alignTopLeft();
	CHECK(button.getPosition() == olc::vi2d{ 0, 0 });

	button.center(screenSize);
	button.alignTopRight(screenSize);
	CHECK(button.getPosition() == olc::vi2d{ rightLeftExtremePositions.x, 0 });

	button.center(screenSize);
	button.alignBottomLeft(screenSize);
	CHECK(button.getPosition() == olc::vi2d{ 0, rightLeftExtremePositions.y });

	button.center(screenSize);
	button.alignBottomRight(screenSize);
	CHECK(button.getPosition() == rightLeftExtremePositions);
}

TEST_CASE("Button Callback")
{
	Button button;
	bool callbackWorks = false;
	auto callback = [&callbackWorks] {callbackWorks = true; };
	std::vector<int> data = { 0, 1, 2, 3, 4 };
	auto callback2 = [&] {data.clear(); };

	// Callback works
	button.setCallback(callback);
	button.getCallback()();
	CHECK(callbackWorks == true);
	
	// Another callback check
	button.setCallback(callback2);
	button.getCallback()();
	CHECK(data.empty() == true);
}

TEST_CASE("Button Clicking")
{
	olc::vi2d position = { 5, 10 };
	olc::vi2d dimensions = { 15, 20 };
	Button button(position, dimensions);
	bool clickRecieved = false;
	auto callback = [&clickRecieved] {clickRecieved = true; };
	button.setCallback(callback);

	// Is position within
	for (int y = 0; y < position.y + dimensions.y + 5; y++)
	{
		for (int x = 0; x < position.x + dimensions.x + 5; x++)
		{
			INFO("Is position: (" << olc::vi2d{ x, y } << ") within the button area");
			bool result = button.isPositionWithin({ x, y });

			if(x >= position.x && x <= position.x + dimensions.x &&
				y >= position.y && y <= position.y + dimensions.y)
				CHECK(result == true);
			else
				CHECK(result == false);
		}
	}

	// Is pressed
	for (int y = 0; y < position.y + dimensions.y + 5; y++)
	{
		for (int x = 0; x < position.x + dimensions.x + 5; x++)
		{
			INFO("Is position: (" << olc::vi2d{ x, y } << ") within the button area");
			clickRecieved = false;
			bool result = button.isPressed({ x, y });

			if (x >= position.x && x <= position.x + dimensions.x &&
				y >= position.y && y <= position.y + dimensions.y)
				CHECK(clickRecieved == true);
			else
				CHECK(clickRecieved == false);
		}
	}

	// Test setActive and isActive
	button.setActive(false);
	CHECK(button.isActive() == false);
	clickRecieved = false;
	bool result = button.isPressed({ position.x + dimensions.x / 2, position.y + dimensions.y / 2 });
	INFO("isActive is set to false");
	CHECK(clickRecieved == false);
	
	button.setActive(true);
	CHECK(button.isActive() == true);
	clickRecieved = false;
	result = button.isPressed({ position.x + dimensions.x / 2, position.y + dimensions.y / 2 });
	INFO("isActive is set to true");
	CHECK(clickRecieved == true);


	// Test setHidden and isHidden
	button.setHidden(false);
	CHECK(button.isHidden() == false);
	button.setHidden(true);
	CHECK(button.isHidden() == true);
}

TEST_CASE("Set Decal Scale")
{
	ButtonProtectedGetter button;
	auto scale = olc::vf2d(5.1f, 2.9f);
	for (size_t i = 0; i < 5; i++)
	{
		button.setButtonDecalScale(scale);
		CHECK(button.getButtonDecalScale().x == doctest::Approx(scale.x));
		CHECK(button.getButtonDecalScale().y == doctest::Approx(scale.y));
		scale.x *= 2.054f;
		scale.y *= 0.937f;
	}
}