#include "CodeGenerator.h"

std::string CodeGenerator::GenerateSpecificNode(std::vector<Node*> nodes, int index)
{
	std::string output = "";

	//In order to print this node, we need to check if the last node was a new line, as we need to print the indent if so
	if ((index > 0 && nodes[(size_t)index - 1]->GetType() == NodeType::NEWLINE) || index == 0)
		for (int i = 0; i < indent; i++)
			output += '\t';

	//For printing a block, we need to add the colon before a newline
	if (nodes[index]->GetType() == NodeType::BLOCK)
	{
		output += ":\n";
		output += GenerateBlock(nodes[index]);
	}
	//Generating a newline is a little tricky, as we need to check if the next token is a block
	//as in that case we need to not print the newline
	else if (nodes[index]->GetType() == NodeType::NEWLINE)
	{
		//If the next node is a block, we don't want to print anything
		//We also need to check if there is a token first
		if (index < nodes.size() - 1 && nodes[(size_t)index + 1]->GetType() != NodeType::BLOCK)
			output += '\n';
	}
	else if (nodes[index]->GetType() == NodeType::SPACE)
	{
		output += ' ';
	}
	else
	{
		output += nodes[index]->GetToken()->lexeme;
	}

	return output;
}

std::string CodeGenerator::GenerateNode()
{
	std::string output = GenerateSpecificNode(nodes, index);
	index++;
	return output;
}

std::string CodeGenerator::GenerateBlock(Node* node)
{
	std::string output = "";
	Indent();

	std::vector<Node*> subnodes = *node->GetSubnodes();

	for (int i = 0; i < subnodes.size(); i++)
		output += GenerateSpecificNode(subnodes, i);

	Outdent();
	return output;
}

std::string CodeGenerator::GetPythonCode()
{
	std::string output = "";

	while (index < nodes.size())
		output += GenerateNode();

	return output;
}