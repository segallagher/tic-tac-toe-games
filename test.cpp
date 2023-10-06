

#include "TicTacToeGame.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char** argv)
{
	// Doctest Testing
	doctest::Context dtcontext;
	int dtresult = 0;
	dtcontext.applyCommandLine(argc, argv);
	dtcontext.setOption("no-breaks", true); // Don't break in the debugger when assertions fail

	dtresult = dtcontext.run();
	if (dtcontext.shouldExit()) // important - query flags (and --exit) rely on the user doing this
		return dtresult;		// propagate the result of the tests

	// End Doctest Testing

}