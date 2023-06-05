#include "Parser.h"

std::vector<Node*> Parser::Parse()
{
	while (index < tokens.size())
	{
		Node* node = nullptr;

		if (tokens[index]->type == _pyp_TokenType::OPEN_BRACE)
			node = ParseBlock();
		else
			node = ParseUnknown();

		nodes.push_back(node);
	}

	//Now we have nodes, we can process them, ready for code generation
	FillEmptyBlocks(nodes);
	FixBlockNewline(nodes);
	RemoveUnwantedSpaces(nodes);
	RestrictReserved(nodes);
	FillBuiltInMacros(nodes);

	return nodes;
}

void Parser::RestrictReserved(std::vector<Node*>& nodes)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetType() == NodeType::BLOCK)
			RestrictReserved(nodes[i]->GetSubnodes());
	}
}