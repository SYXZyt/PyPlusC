#include "Node.h"

std::string Node::PrintNode(int indent)
{
	std::stringstream txt;
	txt << std::string(indent, ' ');
	txt << this;

	for (Node& n : subnodes)
		txt << '\n' << n.PrintNode(indent + 3);

	return txt.str();
}