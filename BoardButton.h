// BoardButton.h
// Nathan Damon
// 2023-10-01
// Header file for BoardButton (a button that will give an x, y coordinate based on clicked area and internal size).

#include "Button.h"

#ifndef BOARDBUTTON_HPP
#define BOARDBUTTON_HPP

class BoardButton : public Button
{
public:
	BoardButton();
	BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions);
	BoardButton(olc::v2d_generic<int> position, olc::v2d_generic<int> dimensions, std::function<void()> lambdaCallback);
	BoardButton(olc::v2d_generic<int> position, olc::Decal& buttonDecal, std::function<void()> lambdaCallback);

	virtual void drawSelf(olc::PixelGameEngine& gfx) override;
	virtual bool isPressed(olc::v2d_generic<int> mousePosition) override;
	olc::v2d_generic<int> getClickedTile(olc::v2d_generic<int> boardDimensions);

	void setTileDecal(olc::Decal& tileDecal);
	olc::Decal& getTileDecal();
	void setODecal(olc::Decal& oDecal);
	olc::Decal& getODecal();
	void setXDecal(olc::Decal& xDecal);
	olc::Decal& getXDecal();

protected:
	// Needs pointer to board

	olc::Decal* _oDecal = nullptr;
	olc::Decal* _xDecal = nullptr;

	olc::v2d_generic<int> _clickedPosition;
};

#endif // !BOARDBUTTON_HPP



