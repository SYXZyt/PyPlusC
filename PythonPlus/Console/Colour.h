#pragma once
enum class Colour
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Yellow,
    White,
    BrightBlack,
    BrightBlue,
    BrightGreen,
    BrightCyan,
    BrightRed,
    BrightMagenta,
    BrightYellow,
    BrightWhite
};

#ifdef _WIN32
#include <Windows.h>

static void SetConsoleColour(Colour foreground, Colour background = Colour::Black)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    //This function requires the two numbers to be merged instead of separate, so this maths will handle it
    int k = (int)foreground + ((int)background * 16);
    SetConsoleTextAttribute(console, k);
}

static void ResetConsoleColour()
{
    SetConsoleColour(Colour::White);
}
#elif defined(linux) //UNTESTED
#include <string>

static void SetConsoleColour(ConsoleColour foreground, ConsoleColour background = ConsoleColour::Black)
{
    std::string foregroundColor;
    std::string backgroundColor;

    //Convert foreground color to ANSI escape sequence
    switch (foreground)
    {
        case Black:
            foregroundColor = "0;30";
            break;
        case Red:
            foregroundColor = "0;31";
            break;
        case Green:
            foregroundColor = "0;32";
            break;
        case Yellow:
            foregroundColor = "0;33";
            break;
        case Blue:
            foregroundColor = "0;34";
            break;
        case Magenta:
            foregroundColor = "0;35";
            break;
        case Cyan:
            foregroundColor = "0;36";
            break;
        case White:
            foregroundColor = "0;37";
            break;
        case BrightBlack:
            foregroundColor = "1;30";
            break;
        case BrightRed:
            foregroundColor = "1;31";
            break;
        case BrightGreen:
            foregroundColor = "1;32";
            break;
        case BrightYellow:
            foregroundColor = "1;33";
            break;
        case BrightBlue:
            foregroundColor = "1;34";
            break;
        case BrightMagenta:
            foregroundColor = "1;35";
            break;
        case BrightCyan:
            foregroundColor = "1;36";
            break;
        case BrightWhite:
            foregroundColor = "1;37";
            break;
    }

    //Convert background color to ANSI escape sequence
    switch (background)
    {
        case Black:
            backgroundColor = "40";
            break;
        case Red:
            backgroundColor = "41";
            break;
        case Green:
            backgroundColor = "42";
            break;
        case Yellow:
            backgroundColor = "43";
            break;
        case Blue:
            backgroundColor = "44";
            break;
        case Magenta:
            backgroundColor = "45";
            break;
        case Cyan:
            backgroundColor = "46";
            break;
        case White:
            backgroundColor = "47";
            break;
        case BrightBlack:
            backgroundColor = "100";
            break;
        case BrightRed:
            backgroundColor = "101";
            break;
        case BrightGreen:
            backgroundColor = "102";
            break;
        case BrightYellow:
            backgroundColor = "103";
            break;
        case BrightBlue:
            backgroundColor = "104";
            break;
        case BrightMagenta:
            backgroundColor = "105";
            break;
        case BrightCyan:
            backgroundColor = "106";
            break;
        case BrightWhite:
            backgroundColor = "107";
            break;
    }

    //Set console color using ANSI escape sequence
    std::cout << "\033[" << foregroundColor << ";" << backgroundColor << "m";
}

static void ResetConsoleColour()
{
    std::cout << "\033[0m";
}
#else //If an unsupported OS, just write empty functions so that the code still runs, just without colour
static void SetConsoleColour(ConsoleColour foreground, ConsoleColour background = ConsoleColour::Black) {}
static void ResetConsoleColour() {}
#endif