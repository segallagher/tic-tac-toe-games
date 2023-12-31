// main.cpp
// Nathan Damon & Samuel Gallapher
// 2023-09-30
// The main.cpp file for tic-tac-toe games

#include "TicTacToeGame.h"
#include "Board.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char** argv)
{
#ifndef DEBUG
	FreeConsole(); // Removes the console when starting with the executable
#endif // !DEBUG

	int dtresult = 0;
#ifdef DEBUG
	// Doctest Testing
	doctest::Context dtcontext;
	dtcontext.applyCommandLine(argc, argv);
	dtcontext.setOption("no-breaks", true); // Don't break in the debugger when assertions fail

	dtresult = dtcontext.run();
	if (dtcontext.shouldExit()) // important - query flags (and --exit) rely on the user doing this
		return dtresult;		// propagate the result of the tests

	// End Doctest Testing
#endif // DEBUG

	TicTacToeGame game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();

	return dtresult;
}