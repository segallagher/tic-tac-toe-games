// ButtonTest.cpp
// Nathan Damon
// 2023-10-01
// This source file contains the unit tests for class Button

#include "Button.h"
#include "Button.h" // Double-inclusion test

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"

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
			CHECK(button.getPosition() == olc::vi2d{ (x - dimx) / 2 , 0});

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
	for (int y = 0; y < position.y + dimensions.y + 5; y += 2)
	{
		for (int x = 0; x < position.x + dimensions.x + 5; x += 2)
		{
			INFO("Is position: (" << olc::vi2d{ x, y } << ") within the button area");
			bool result = button.isPositionWithin({ x, y });

			if(x >= position.x && x < position.x + dimensions.x &&
				y >= position.y && y < position.y + dimensions.y)
				CHECK(result == true);
			else
				CHECK(result == false);
		}
	}

	// Is pressed
	for (int y = 0; y < position.y + dimensions.y + 5; y += 2)
	{
		for (int x = 0; x < position.x + dimensions.x + 5; x += 2)
		{
			INFO("Is position: (" << olc::vi2d{ x, y } << ") within the button area");
			clickRecieved = false;
			bool result = button.isPressed({ x, y });

			if (x >= position.x && x < position.x + dimensions.x &&
				y >= position.y && y < position.y + dimensions.y)
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
}

