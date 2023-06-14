#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../Parsing/Node.h"
#include "../../Console/Colour.h"

class CodeGenerator final
{
private:
	std::vector<Node*> nodes;
	int index;
	int indent;
	bool failed;

	inline void Indent()
	{
		indent++;
	}

	inline void Outdent()
	{
		if (indent <= 0)
		{
			SetConsoleColour(Colour::Red);
			std::cerr << "Error";
			ResetConsoleColour();
			std::cerr << ": Cannot outdent further\nAt " << nodes[index]->GetToken()->pos << '\n';
			return;
		}

		indent--;
	}

	std::string GenerateSpecificNode(std::vector<Node*> nodes, int index);
	std::string GenerateNode();
	std::string GenerateBlock(Node* node);
public:

	std::string GetPythonCode();
	CodeGenerator(std::vector<Node*>* nodes) : nodes(*nodes), failed(false), index(0), indent(0) {}
};