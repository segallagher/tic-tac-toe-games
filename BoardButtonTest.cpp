// BoardButtonTest.cpp
// Nathan Damon
// 2023-10-01
// This source file contains the unit tests for class BoardButton

#include "BoardButton.h"
#include "BoardButton.h" // Double-inclusion test
#include "doctest.h"

TEST_CASE("BoardButton Constructors")
{
	// Test values
	olc::vi2d position = { 10, 20 };
	olc::vi2d dimensions = { 30, 40 };
	bool callbackWorks = false;
	auto callback = [&callbackWorks] {callbackWorks = true; };
	olc::Sprite sprite(dimensions.x, dimensions.y);

	// Default boardButton
	BoardButton boardButton;
	CHECK(boardButton.getPosition() == olc::vi2d());
	CHECK(boardButton.getDimensions() == olc::vi2d());

	// BoardButton at a position and with dimensions
	BoardButton boardButton1(position, dimensions);
	CHECK(boardButton1.getPosition() == position);
	CHECK(boardButton1.getDimensions() == dimensions);

	// BoardButton at a position and with dimensions and a callback
	BoardButton boardButton2(position, dimensions, callback);
	CHECK(boardButton2.getPosition() == position);
	CHECK(boardButton2.getDimensions() == dimensions);
	boardButton2.getCallback()();
	CHECK(callbackWorks == true);

	// BoardButton at a position with a decal and a callback
	// Cannot be tested properly due to Decal's dependence on olcPixelGameEngine implementation
	callbackWorks = false;
	BoardButton boardButton3(position, sprite.Size(), callback);
	CHECK(boardButton3.getPosition() == position);
	CHECK(boardButton3.getDimensions() == dimensions);
	boardButton3.getCallback()();
	CHECK(callbackWorks == true);
}

TEST_CASE("BoardButton Clicking")
{
	olc::vi2d position = { 5, 10 };
	olc::vi2d dimensions = { 15, 20 };
	class boardButtonClickGetter : public BoardButton
	{
		public: olc::v2d_generic<int> getClickedLocation() { return _clickedPosition; }
	};
	boardButtonClickGetter boardButton;
	boardButton.setPosition(position);
	boardButton.setDimensions(dimensions);

	struct FakeBoard
	{
		olc::vi2d _dimensions;
		olc::vi2d _givenTile = { -1, -1 };
		olc::vi2d getDimensions() { return _dimensions; }
		void setTile(olc::vi2d position) { _givenTile = position; }
	};
	FakeBoard fakeBoard;
	fakeBoard._dimensions = { 5, 5 };

	// Callback gives boardButton the fakeBoard dimensions and then boardButton gives fakeBoard the tile clicked on
	auto callback = [&fakeBoard, &boardButton] {fakeBoard.setTile(boardButton.getClickedTile(fakeBoard.getDimensions())); };
	boardButton.setCallback(callback);

	// Is pressed
	for (int y = 0; y < position.y + dimensions.y + 5; y++)
	{
		for (int x = 0; x < position.x + dimensions.x + 5; x++)
		{
			// Set given tile to invalid
			fakeBoard._givenTile = { -1, -1 };

			// Function isPressed is inherited from class Button and has already been tested
			if (boardButton.isPressed({ x, y }))
			{
				INFO("BoardButton records the mouse input location");
				CHECK(boardButton.getClickedLocation() == olc::vi2d{ x, y });

				int tileX = (x - position.x) / (boardButton.getDimensions().x / fakeBoard.getDimensions().x);
				int tileY = (y - position.y) / (boardButton.getDimensions().y / fakeBoard.getDimensions().y);
				INFO("BoardButton gives the correct tile for mouse input");
				CHECK(fakeBoard._givenTile == olc::vi2d{ tileX, tileY });
			}
		}
	}
}

