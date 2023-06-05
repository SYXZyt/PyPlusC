#include "Parser.h"

std::vector<Node*>* Parser::Parse()
{
	if (tokens.size() == 0)
	{
		SetConsoleColour(Colour::BrightRed);
		std::cerr << "Error";
		ResetConsoleColour();
		std::cerr << ": Cannot compile empty file\n";
		failed = true;
		return nodes;
	}

	while (index < tokens.size())
	{
		Node* node = nullptr;

		if (tokens[index]->type == _pyp_TokenType::OPEN_BRACE)
			node = ParseBlock();
		else
			node = ParseUnknown();

		nodes->push_back(node);
	}

	//Now we have nodes, we can process them, ready for code generation
	FillEmptyBlocks(*nodes);
	FixBlockNewline(*nodes);
	RemoveUnwantedSpaces(*nodes);
	RestrictReserved(*nodes);
	FillBuiltInMacros(*nodes);

	return nodes;
}

void Parser::RestrictReserved(std::vector<Node*>& nodes)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if ((nodes[i])->GetType() == NodeType::BLOCK)
			RestrictReserved(*(nodes[i])->GetSubnodes());
		else
		{
			for (std::string& name : RestrictedKeywords)
			{
				if (nodes[i]->GetToken()->lexeme == name)
				{
					SetConsoleColour(Colour::Red);
					std::cerr << "Error";
					ResetConsoleColour();
					std::cerr << ": Restricted name '" << name << "' found\nAt " << nodes[i]->GetToken()->pos << '\n';
					failed = true;
				}
			}
		}
	}
}

void Parser::FillBuiltInMacros(std::vector<Node*>& nodes)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetType() == NodeType::BLOCK)
			FillBuiltInMacros(*nodes[i]->GetSubnodes());
		else
		{
			for (auto& kvp : BuiltIn)
			{
				if (nodes[i]->GetToken()->lexeme == kvp.first)
					nodes[i]->GetToken()->lexeme = kvp.second;
			}
		}
	}
}

void Parser::FillEmptyBlocks(std::vector<Node*>& nodes)
{
	for (Node* n : nodes)
	{
		if (n->GetType() == NodeType::BLOCK)
		{
			//Since python does not have empty blocks, we need to use the pass keyword which allows it
			if (n->GetSubnodes()->size() == 0)
			{
				Node* passNode = new Node(new Token(_pyp_TokenType::IDENTIFIER, n->GetToken()->pos, "pass"), NodeType::UNKNOWN);
				n->Append(passNode);
			}
			else
			{
				FillEmptyBlocks(*n->GetSubnodes());
			}
		}
	}
}

void Parser::FixBlockNewline(std::vector<Node*>& nodes)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->GetType() == NodeType::BLOCK)
		{
			Node* block = nodes[i];
			FixBlockNewline(*block->GetSubnodes());

			std::vector<Node*>& subnodes = *block->GetSubnodes();

			while (subnodes[0]->GetType() == NodeType::NEWLINE || subnodes[0]->GetType() == NodeType::SPACE)
			{
				delete subnodes[0];
				subnodes.erase(subnodes.begin());
			}
		}
	}
}

void Parser::RemoveUnwantedSpaces(std::vector<Node*>& nodes)
{
	//If a space follows a newline, remove it
	size_t i = 0;
	size_t e = nodes.size();

	while (i < e)
	{
		if (nodes[i]->GetType() == NodeType::BLOCK)
			RemoveUnwantedSpaces(*nodes[i]->GetSubnodes());

		if (i == 0)
		{
			i++;
			continue;
		}

		if (nodes[i]->GetType() == NodeType::SPACE && nodes[i - 1]->GetType() == NodeType::NEWLINE)
		{
			nodes.erase(nodes.begin() + i);
			i--;
			e = nodes.size();
		}

		i++;
	}
}

Node* Parser::ParseBlock()
{
	Node* n = new Node(tokens[index++], NodeType::BLOCK);

	while (index < tokens.size() && tokens[index]->type != _pyp_TokenType::CLSE_BRACE)
	{
		Node* sub = ParseUnknown();
		n->Append(sub);
	}

	if (index >= tokens.size())
	{
		SetConsoleColour(Colour::BrightRed);
		std::cerr << "Error";
		ResetConsoleColour();
		std::cerr << ": Expected '}'\nAt " << tokens[tokens.size() - 1]->pos << '\n';
		failed = true;
	}

	index++; // <-- skips the } character so we can read a new token
	return n;
}

Node* Parser::ParseUnknown()
{
	if (tokens[index]->type == _pyp_TokenType::OPEN_BRACE)
		return ParseBlock();

	Node* n = new Node(tokens[index], NodeType::UNKNOWN);

	if (tokens[index]->type == _pyp_TokenType::NEWLINE)
		n->SetType(NodeType::NEWLINE);
	else if (tokens[index]->type == _pyp_TokenType::SPACE)
		n->SetType(NodeType::SPACE);

	index++;
	return n;
}