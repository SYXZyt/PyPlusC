#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "Console/Colour.h"
#include "Compiler/Parsing/Node.h"
#include "Compiler/Parsing/Parser.h"
#include "Compiler/Tokenisation/Token.h"
#include "Compiler/Tokenisation/Lexer.h"

#define CNV_STR(str) std::string(str)

#if _DEBUG
static bool dump_lexer = true;
static bool dump_parser = true;
#else
static bool dump_lexer = false;
static bool dump_parser = false;
#endif

void _pyp_exit(int code)
{
	std::cout << "\nExited with code " << code << '\n';
	exit(code);
}

inline bool FileExists(const char* name)
{
	return std::filesystem::exists(name);
}

std::string LoadTextFromFile(const char* fname)
{
	std::ifstream in(fname);
	std::stringstream buffer;
	buffer << in.rdbuf();
	return buffer.str();
}

void FreeCompileUnit(std::vector<Token*>& tokens, std::vector<Node*>* nodes)
{
	for (Token* t : tokens)
		delete t;

	for (Node* n : *nodes)
		delete n;

	delete nodes;
}

void CompileFile(const char* fname)
{
	if (!FileExists(fname))
	{
		std::cerr << "Could not find file '" << fname << "'\n";
		_pyp_exit(1);
	}

	std::cout << "Compiling file '" << fname << "'\n";

	Lexer lexer = Lexer(LoadTextFromFile(fname));
	std::vector<Token*> tokens = lexer.Tokenise();

	if (lexer.Failed())
	{
		std::cerr << "In " << fname << '\n';
		_pyp_exit(1);
	}

	if (dump_lexer)
		for (Token* t : tokens)
			std::cout << *t << '\n';

	Parser parser = Parser(tokens);
	std::vector<Node*>* nodes = parser.Parse();

	if (parser.Failed())
	{
		std::cerr << "In " << fname << '\n';
		_pyp_exit(1);
	}

	if (dump_parser)
	{
		std::cout << '\n';
		for (Node* n : *nodes)
			std::cout << n->PrintNode(0) << '\n';
	}

	FreeCompileUnit(tokens, nodes);
}

void CompileToPython() {}

bool* CheckArgsForCommands(int argc, char** argv)
{
	bool* areCmds = new bool[argc - 1] { false };

	for (int i = 1; i < argc; i++)
	{
		if (CNV_STR(argv[i]) == "-D_TESTCOLOUR" || CNV_STR(argv[i]) == "-D_TESTCOLOR")
		{
			DisplayTestPattern();
			areCmds[i - 1] = true;
		}
		else if (CNV_STR(argv[i]) == "-D_DUMPLEXER")
		{
			dump_lexer = true;
			std::cout << "Dumping tokens\n";
			areCmds[i - 1] = true;
		}
		else if (CNV_STR(argv[i]) == "-D_DUMPPARSER")
		{
			dump_parser = true;
			std::cout << "Dumping nodes\n";
			areCmds[i - 1] = true;
		}
	}

	return areCmds;
}

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
		std::cerr << ": No input file / s\nUsage: PyPlus <FILE_PATHS>\n";
		return 1;
	}

	bool* areCmds = CheckArgsForCommands(argc, argv);

	//Loop over each file provided and try to compile the file
	for (int i = 1; i < argc; i++)
	{
		if (!areCmds[i - 1])
			CompileFile(argv[i]);
	}

	CompileToPython();

	_pyp_exit(0);
}