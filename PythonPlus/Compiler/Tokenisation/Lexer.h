#pragma once
#include <queue>
#include <string>
#include <vector>
#include <iostream>

#include "Token.h"
#include "TokenType.h"
#include "../Vector2.h"
#include "../../Console/Colour.h"

static constexpr bool IsCharAlphaNum(char c)
{
	return (
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9')
		);
}

class Lexer final
{
private:
	std::string text;
	int line;
	int posOnLine;
	int pos;
	bool failed;
	std::vector<Token> tokens;

	char currentChar;
	std::queue<Token> tstack;

	void AppendTStack();
	char Peek();
	void Advance();
	Token GenerateIden();
	Token GenerateString(char strChr);

	void RemoveMultiSpace();

public:
	inline bool Failed() { return failed; }
	std::vector<Token> Tokenise();

	Lexer(std::string text);
};