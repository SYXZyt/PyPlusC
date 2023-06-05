#pragma once
#include <iostream>

#include "Node.h"
#include "NodeType.h"
#include "../../Console/Colour.h"
#include "../Tokenisation/Token.h"
#include "../GlobalData/BuiltIns.h"

class Parser
{
private:
	std::vector<Token*> tokens;
	std::vector<Node*>* nodes;

	bool failed;
	int index;

	void RestrictReserved(std::vector<Node*>& nodes);
	void FillBuiltInMacros(std::vector<Node*>& nodes);
	void FillEmptyBlocks(std::vector<Node*>& nodes);
	void FixBlockNewline(std::vector<Node*>& nodes);
	void RemoveUnwantedSpaces(std::vector<Node*>& nodes);

	Node* ParseBlock();
	Node* ParseUnknown();

public:
	inline bool Failed() { return failed; }

	std::vector<Node*>* Parse();
	Parser(std::vector<Token*> tokens) : tokens(tokens), index(0), failed(false) { nodes = new std::vector<Node*>(); }
};