#pragma once
#include <ostream>

enum class _pyp_TokenType
{
    _EOF,
    STRING,
    IDENTIFIER,
    OPEN_BRACE,
    CLSE_BRACE,
    OPEN_BRA,
    CLSE_BRA,
    NEWLINE,
    SPACE,
    OPEN_BRACE_PY,
    CLSE_BRACE_PY,
    UNKNOWN,
};

static std::ostream& operator<<(std::ostream& o, const _pyp_TokenType& type)
{
    switch (type)
    {
        case _pyp_TokenType::_EOF:
            o << "_EOF";
            break;
        case _pyp_TokenType::STRING:
            o << "STRING";
            break;
        case _pyp_TokenType::IDENTIFIER:
            o << "IDENTIFIER";
            break;
        case _pyp_TokenType::OPEN_BRACE:
            o << "OPEN_BRACE";
            break;
        case _pyp_TokenType::CLSE_BRACE:
            o << "CLOSE_BRACE";
            break;
        case _pyp_TokenType::OPEN_BRA:
            o << "OPEN_BRACKET";
            break;
        case _pyp_TokenType::CLSE_BRA:
            o << "CLOSE_BRACKET";
            break;
        case _pyp_TokenType::NEWLINE:
            o << "NEWLINE";
            break;
        case _pyp_TokenType::SPACE:
            o << "SPACE";
            break;
        case _pyp_TokenType::OPEN_BRACE_PY:
            o << "OPEN_BRACE_PY";
            break;
        case _pyp_TokenType::CLSE_BRACE_PY:
            o << "CLOSE_BRACE_PY";
            break;
        case _pyp_TokenType::UNKNOWN:
            o << "UNKNOWN";
            break;
    }

    return o;
}