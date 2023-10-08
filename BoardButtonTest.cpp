// BoardButtonTest.cpp
// Nathan Damon
// 2023-10-01
// This source file contains the unit tests for class BoardButton

#include "BoardButton.h"
#include "BoardButton.h" // Double-inclusion test
#include "doctest.h"

class BoardButtonTester : public BoardButton
{
public:
	olc::v2d_generic<int> getClickedLocation() { return _clickedPosition; }
	olc::v2d_generic<float> testGetTilePosition(olc::v2d_generic<float> tileSize, olc::v2d_generic<float> internalOffsets, int xOffset, int yOffset)
	{
		return getTilePosition(tileSize, internalOffsets, xOffset, yOffset);
	}
	olc::v2d_generic<float> testGetTileScale(olc::v2d_generic<float> tileSize, olc::v2d_generic<int> spriteSize)
	{
		return getTileScale(tileSize, spriteSize);
	}
};
struct FakeBoard
{
	olc::vi2d _dimensions;
	olc::vi2d _givenTile = { -1, -1 };
	olc::vi2d getDimensions() { return _dimensions; }
	void setTile(olc::vi2d position) { _givenTile = position; }
};

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
	SUBCASE("Is pressed")
	{
		olc::vi2d position = { 5, 10 };
		olc::vi2d dimensions = { 15, 20 };
		BoardButtonTester boardButton;
		boardButton.setPosition(position);
		boardButton.setDimensions(dimensions);

		FakeBoard fakeBoard;
		fakeBoard._dimensions = { 5, 5 };

		// Callback gives boardButton the fakeBoard dimensions and then boardButton gives fakeBoard the tile clicked on
		auto callback = [&fakeBoard, &boardButton] {fakeBoard.setTile(boardButton.getClickedTile(fakeBoard.getDimensions())); };
		boardButton.setCallback(callback);
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
					CHECK(fakeBoard._givenTile == olc::vi2d{ std::min(tileX, fakeBoard._dimensions.x - 1), std::min(tileY, fakeBoard._dimensions.y - 1) });
				}
			}
		}
	}
		
	SUBCASE("Internal clickable offsets")
	{
		olc::vi2d position = { 5, 10 };
		olc::vi2d dimensions = { 15, 20 };
		auto boardButton = BoardButton(position, dimensions);

		auto spriteSize = olc::vi2d(32, 32);
		for (size_t i = 0; i < 5; i++)
		{
			auto result = boardButton.getInternalClickableOffsets(spriteSize);
			CHECK(result.x == doctest::Approx(float(dimensions.x) * float(boardButton.getBorderOffset().x) / float(spriteSize.x)));
			CHECK(result.y == doctest::Approx(float(dimensions.y) * float(boardButton.getBorderOffset().y) / float(spriteSize.y)));
			spriteSize *= 3;
		}
	}
}

TEST_CASE("Board Tiles")
{
	SUBCASE("Get tile size")
	{
		auto boardButton = BoardButtonTester();
		boardButton.setDimensions({ 10, 10 });

		auto internalOffsets = olc::vf2d(0, 0);
		for (size_t i = 0; i < 5; i++)
		{
			for (int y = 1; y < 15; y++)
			{
				for (int x = 1; x < 15; x++)
				{
					auto result = boardButton.getTileSize(x, y, internalOffsets);
					CHECK(result.x == doctest::Approx((float(boardButton.getDimensions().x) - internalOffsets.x * 2.0f) / float(x)));
					CHECK(result.y == doctest::Approx((float(boardButton.getDimensions().y) - internalOffsets.y * 2.0f) / float(y)));
				}
			}
			internalOffsets = (internalOffsets + olc::vf2d(0.1f, 0.1f)) * 1.1f;
			boardButton.setDimensions(boardButton.getDimensions() + olc::vi2d(1, 1));
		}
	}
	SUBCASE("Get tile position")
	{
		auto boardButton = BoardButtonTester();
		boardButton.setDimensions({ 10, 10 });

		auto tileSize = olc::vf2d(0.45f, 0.54f);
		auto internalOffsets = olc::vf2d(0.0f, 0.0f);
		int posX = 0;
		int posY = 0;

		auto result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(0.0f));
		CHECK(result.y == doctest::Approx(0.0f));

		posX = 3;
		posY = 5;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX)));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY)));

		posX = 213;
		posY = 187;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX)));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY)));

		// Change internal offsets
		internalOffsets = olc::vf2d(0.3f, 0.5f);

		posX = 3;
		posY = 5;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX) + internalOffsets.x));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY) + internalOffsets.y));

		posX = 213;
		posY = 187;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX) + internalOffsets.x));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY) + internalOffsets.y));

		// Change tile size
		tileSize = olc::vf2d(33.1f, 27.8f);

		posX = 3;
		posY = 5;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX) + internalOffsets.x));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY) + internalOffsets.y));

		posX = 213;
		posY = 187;
		result = boardButton.testGetTilePosition(tileSize, internalOffsets, posX, posY);
		CHECK(result.x == doctest::Approx(tileSize.x * float(posX) + internalOffsets.x));
		CHECK(result.y == doctest::Approx(tileSize.y * float(posY) + internalOffsets.y));
	}
	SUBCASE("Get tile scale")
	{
		auto boardButton = BoardButtonTester();

		auto spriteSize = olc::vi2d(32, 32);
		auto tileSize = olc::vf2d(10.0f, 10.0f);
		auto result = boardButton.testGetTileScale(tileSize, spriteSize);
		auto value = olc::vf2d(0.3125f, 0.3125f);
		CHECK(result.x == doctest::Approx(value.x));
		CHECK(result.y == doctest::Approx(value.y));

		spriteSize = olc::vi2d(50, 40);
		tileSize = olc::vf2d(15.0f, 9.5f);
		result = boardButton.testGetTileScale(tileSize, spriteSize);
		value = olc::vf2d(0.3f, 0.2375f);
		CHECK(result.x == doctest::Approx(value.x));
		CHECK(result.y == doctest::Approx(value.y));

		spriteSize = olc::vi2d(87, 13);
		tileSize = olc::vf2d(23.73f, 22.9f);
		result = boardButton.testGetTileScale(tileSize, spriteSize);
		value = olc::vf2d(0.27275862f, 1.761538461f);
		CHECK(result.x == doctest::Approx(value.x));
		CHECK(result.y == doctest::Approx(value.y));
	}
}

TEST_CASE("Misc Functions")
{
	BoardButton boardButton;
	SUBCASE("Set and get board")
	{
		std::vector<std::vector<int>> board = { {1}, {2}, {3, 2, 1} };
		boardButton.setBoard(&board);
		CHECK(*boardButton.getBoard() == board);
		for (size_t i = 0; i < 3; i++)
			CHECK((*boardButton.getBoard())[i] == board[i]);
	}

	SUBCASE("Board border offsets")
	{
		INFO("If failed: change test or internally stored _borderOffset");
		CHECK(boardButton.getBorderOffset() == olc::vi2d(32, 32));
	}
}

