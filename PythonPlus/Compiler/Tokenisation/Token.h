#pragma once
#include <string>
#include <ostream>

#include "TokenType.h"
#include "../Vector2.h"
#include "../StringReplace.h"

struct Token
{
	_pyp_TokenType type;
	Vector2 pos;
	std::string lexeme;

	Token() : type(_pyp_TokenType::_EOF) {}
	Token(_pyp_TokenType type, Vector2 pos, std::string lexeme) : type(type), pos(pos), lexeme(lexeme) {}
};

static std::ostream& operator<<(std::ostream& o, const Token& token)
{
	std::string lexeme = token.lexeme;
	StringReplace(lexeme, "\n", "\\n");
	StringReplace(lexeme, "\t", "\\t");
	StringReplace(lexeme, "\b", "\\b");
	StringReplace(lexeme, "\0", "\\0");
	StringReplace(lexeme, "\r", "\\r");

	o << "Token: " << token.type << ", ";
	o << token.pos << ", '";
	o << lexeme << '\'';
	return o;
}