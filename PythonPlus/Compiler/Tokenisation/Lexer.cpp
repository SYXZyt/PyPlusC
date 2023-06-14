#include "Lexer.h"

void Lexer::AppendTStack()
{
	while (!tstack.empty())
	{
		tokens.push_back(tstack.front());
		tstack.pop();
	}
}

char Lexer::Peek()
{
	if (static_cast<size_t>(pos) + 1 >= text.size())
		return '\0';

	return text[static_cast<size_t>(pos) + 1];
}

void Lexer::Advance()
{
	pos++;
	posOnLine += 1;

	if (pos >= text.size())
		currentChar = '\0';
	else
	{
		currentChar = text[pos];

		if (currentChar == '\n')
		{
			line++;
			posOnLine = 0;
			tstack.push(new Token(_pyp_TokenType::NEWLINE, Vector2(posOnLine, line), std::string("\n")));
		}

		return;
	}
}

Token* Lexer::GenerateIden()
{
	Vector2 pos = Vector2(posOnLine, line);
	std::string lexeme = "";

	//Loop while we are reading a letter, underscore or number, since they are the valid characters
	while (IsCharAlphaNum(currentChar) || currentChar == '_')
	{
		lexeme += currentChar;
		Advance();
	}

	return new Token(_pyp_TokenType::IDENTIFIER, pos, lexeme);
}

Token* Lexer::GenerateString(char strChr)
{
	Vector2 pos = Vector2(posOnLine, line);
	Advance();

	std::string lexeme = "";
	while (currentChar != strChr)
	{
		if (currentChar == '\0' || currentChar == '\n')
		{
			SetConsoleColour(Colour::BrightRed);
			std::cerr << "Error";
			ResetConsoleColour();
			std::cerr << ": String not terminated\nAt " << pos << '\n';
			failed = true;
			return nullptr;
		}

		//Handle escape characters
		if (currentChar == '\\')
		{
			Advance();

			if (currentChar == '\0')
			{
				SetConsoleColour(Colour::BrightRed);
				std::cerr << "Error";
				ResetConsoleColour();
				std::cerr << ": End of file was unexpected\nAt " << pos << '\n';
				failed = true;
				return nullptr;
			}

			if (currentChar == '"')
				lexeme += "\\\"";
			else if (currentChar == '\'')
				lexeme += "\\'";
			else if (currentChar == 'n')
				lexeme += "\\n";
			else if (currentChar == 'b')
				lexeme += "\\b";
			else if (currentChar == 'r')
				lexeme += "\\r";
			else if (currentChar == '\\')
				lexeme += "\\\\";
			else if (currentChar == '0')
				lexeme += "\\0";
			else if (currentChar == 't')
				lexeme += "\\t";
			else
			{
				SetConsoleColour(Colour::BrightRed);
				std::cerr << "Error";
				ResetConsoleColour();
				std::cerr << ": Unknown escape character '\\" << currentChar << "'\nAt " << pos << '\n';
				failed = true;
				return nullptr;
			}
		}
		else
			lexeme += currentChar;
		Advance();
	}

	Advance();
	return new Token(_pyp_TokenType::STRING, pos, strChr + lexeme + strChr);
}

void Lexer::RemoveMultiSpace()
{
	//We don't want to deal with the users multi-space tab, but we want to deal with spaces
	//so we can remove multiple spaces in a row
	std::vector<Token*> tokens;

	//If the lexical analysis failed, skip this as it may crash
	if (failed)
		return;

	int i = 0;
	while (i < this->tokens.size())
	{
		while (i < this->tokens.size() - 1)
		{
			if (this->tokens[i]->type == _pyp_TokenType::SPACE && this->tokens[static_cast<size_t>(i) + 1]->type == _pyp_TokenType::SPACE)
			{
				i++;
				continue;
			}

			break;
		}

		tokens.push_back(this->tokens[i]);
		i++;
	}

	this->tokens = tokens;
}

std::vector<Token*> Lexer::Tokenise()
{
	while (currentChar != '\0')
	{
		//Handle all whitespace characters. We typically skip them, except spaces, which are needed in code generation
		if (currentChar == ' ' || currentChar == '\t' || currentChar == '\r' || currentChar == '\n')
		{
			if (currentChar == ' ')
				tokens.push_back(new Token(_pyp_TokenType::SPACE, Vector2(posOnLine, line), " "));
			Advance();
			AppendTStack();
			continue;
		}

		if (currentChar == '"' || currentChar == '\'')
		{
			Token* string = GenerateString(currentChar);
			tokens.push_back(string);
		}
		else if (IsCharAlphaNum(currentChar) || currentChar == '_')
		{
			tokens.push_back(GenerateIden());
		}
		else if (currentChar == '{')
		{
			tokens.push_back(new Token(_pyp_TokenType::OPEN_BRACE, Vector2(posOnLine, line), std::string(1, currentChar)));
			Advance();
		}
		else if (currentChar == '}')
		{
			tokens.push_back(new Token(_pyp_TokenType::CLSE_BRACE, Vector2(posOnLine, line), std::string(1, currentChar)));
			Advance();
		}
		else if (currentChar == '(')
		{
			tokens.push_back(new Token(_pyp_TokenType::OPEN_BRA, Vector2(posOnLine, line), std::string(1, currentChar)));
			Advance();
		}
		else if (currentChar == ')')
		{
			tokens.push_back(new Token(_pyp_TokenType::CLSE_BRA, Vector2(posOnLine, line), std::string(1, currentChar)));
			Advance();
		}
		else if (currentChar == '\\')
		{
			if (Peek() == '{')
			{
				Advance();
				tokens.push_back(new Token(_pyp_TokenType::OPEN_BRACE_PY, Vector2(posOnLine, line), std::string(1, currentChar)));
				Advance();
			}
			else if (Peek() == '}')
			{
				Advance();
				tokens.push_back(new Token(_pyp_TokenType::CLSE_BRACE_PY, Vector2(posOnLine, line), std::string(1, currentChar)));
				Advance();
			}
			else
			{
				tokens.push_back(new Token(_pyp_TokenType::UNKNOWN, Vector2(posOnLine, line), std::string(1, currentChar)));
				Advance();
			}
		}
		else if (currentChar == '#')
		{
			//Since we want to ignore comments, as they do not affect code execution, we can just skip to the next line
			while (currentChar != '\n' && currentChar != '\0')
				Advance();
		}
		else
		{
			tokens.push_back(new Token(_pyp_TokenType::UNKNOWN, Vector2(posOnLine, line), std::string(1, currentChar)));
			Advance();
		}

		AppendTStack();
	}

	RemoveMultiSpace();
	return tokens;
}

Lexer::Lexer(std::string text)
{
	this->text = text;
	line = 0;
	pos = -1;
	posOnLine = -1;
	Advance(); //Loads the current character and preps the positions

	failed = false;
}