#include <sstream>
#include <iostream>

#include "Console\Colour.h"

int main(int argc, char** argv)
{
	//Check how many arguments we were provided
	//If we only got one, we want to print an error
	//Remember, arg[0] in C++ will always be our exe
	if (argc == 1)
	{
		SetConsoleColour(BrightRed);
		std::cerr << "Error";
		ResetConsoleColour();
		std::cerr << ": No input file / s\nUsage: PyPlus <FILE_PATHS> <args>";
		return 1;
	}
}