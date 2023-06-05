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

#elif defined(linux)
#include <string>
#include <iostream>

static void SetConsoleColour(Colour foreground, Colour background = Colour::Black)
{
    std::string foregroundColor;
    std::string backgroundColor;

    //Convert foreground color to ANSI escape sequence
    switch (foreground)
    {
        case Colour::Black:
            foregroundColor = "0;30";
            break;
        case Colour::Red:
            foregroundColor = "0;31";
            break;
        case Colour::Green:
            foregroundColor = "0;32";
            break;
        case Colour::Yellow:
            foregroundColor = "0;33";
            break;
        case Colour::Blue:
            foregroundColor = "0;34";
            break;
        case Colour::Magenta:
            foregroundColor = "0;35";
            break;
        case Colour::Cyan:
            foregroundColor = "0;36";
            break;
        case Colour::White:
            foregroundColor = "0;37";
            break;
        case Colour::BrightBlack:
            foregroundColor = "1;30";
            break;
        case Colour::BrightRed:
            foregroundColor = "1;31";
            break;
        case Colour::BrightGreen:
            foregroundColor = "1;32";
            break;
        case Colour::BrightYellow:
            foregroundColor = "1;33";
            break;
        case Colour::BrightBlue:
            foregroundColor = "1;34";
            break;
        case Colour::BrightMagenta:
            foregroundColor = "1;35";
            break;
        case Colour::BrightCyan:
            foregroundColor = "1;36";
            break;
        case Colour::BrightWhite:
            foregroundColor = "1;37";
            break;
    }

    //Convert background color to ANSI escape sequence
    switch (background)
    {
        case Colour::Black:
            backgroundColor = "40";
            break;
        case Colour::Red:
            backgroundColor = "41";
            break;
        case Colour::Green:
            backgroundColor = "42";
            break;
        case Colour::Yellow:
            backgroundColor = "43";
            break;
        case Colour::Blue:
            backgroundColor = "44";
            break;
        case Colour::Magenta:
            backgroundColor = "45";
            break;
        case Colour::Cyan:
            backgroundColor = "46";
            break;
        case Colour::White:
            backgroundColor = "47";
            break;
        case Colour::BrightBlack:
            backgroundColor = "100";
            break;
        case Colour::BrightRed:
            backgroundColor = "101";
            break;
        case Colour::BrightGreen:
            backgroundColor = "102";
            break;
        case Colour::BrightYellow:
            backgroundColor = "103";
            break;
        case Colour::BrightBlue:
            backgroundColor = "104";
            break;
        case Colour::BrightMagenta:
            backgroundColor = "105";
            break;
        case Colour::BrightCyan:
            backgroundColor = "106";
            break;
        case Colour::BrightWhite:
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
static void SetConsoleColour(Colour foreground, Colour background = Colour::Black) {}
static void ResetConsoleColour() {}
#endif

static void DisplayTestPattern()
{
    //Loop over each colour possibility, and then display a character on the screen for it
    for (int b = 0; b < 16; b++)
    {
        for (int f = 0; f < 16; f++)
        {
            Colour foregroundColour = (Colour)f;
            Colour backgroundColour = (Colour)b;

            SetConsoleColour(foregroundColour, backgroundColour);
            std::cout << 'A';
        }
    }

    ResetConsoleColour();
}