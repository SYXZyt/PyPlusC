#include <fstream>
#include <sstream>
#include <iostream>

#include "Console\Colour.h"
#include "Compiler\Tokenisation\Token.h"
#include "Compiler\Tokenisation\Lexer.h"

#ifdef _DEBUG
#define DUMP_LEXER
#define DUMP_PARSER
#endif

void _pyp_exit(int code)
{
	std::cout << "Exited with code " << code << '\n';
	exit(code);
}

inline bool FileExists(const char* name)
{
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

std::string LoadTextFromFile(const char* fname)
{
	std::ifstream in(fname);
	std::stringstream buffer;
	buffer << in.rdbuf();
	return buffer.str();
}

void FreeCompileUnit(std::vector<Token*>& tokens, std::vector<Node*> nodes)
{
	for (Token* t : tokens)
		delete t;

	for (Node* n : nodes)
		delete n;
}

void CompileFile(const char* fname)
{
	if (!FileExists(fname))
	{
		std::cerr << "";
	}

	Lexer lexer = Lexer(LoadTextFromFile(fname));
	std::vector<Token*> tokens = lexer.Tokenise();

	if (lexer.Failed())
		_pyp_exit(1);

#ifdef DUMP_LEXER
	for (Token* t : tokens)
		std::cout << t << '\n';
#endif
}

void CompileToPython() {}

int main(int argc, char** argv)
{
	//Check how many arguments we were provided
	//If we only got one, we want to print an error
	//Remember, arg[0] in C++ will always be our exe
	if (argc == 1)
	{
		SetConsoleColour(Colour::BrightRed);
		std::cerr << "Error";
		ResetConsoleColour();
		std::cerr << ": No input file / s\nUsage: PyPlus <FILE_PATHS>";
		return 1;
	}

	//Loop over each file provided and try to compile the file
	for (int i = 1; i < argc; i++)
		CompileFile(argv[i]);

	CompileToPython();

	_pyp_exit(0);
}