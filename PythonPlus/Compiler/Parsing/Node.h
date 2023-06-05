#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <ostream>

#include "NodeType.h"
#include "../Tokenisation/Token.h"

class Node
{
private:
	Token* token;
	NodeType type;
	std::vector<Node*>* subnodes;

public:
	inline Token* GetToken() const { return token; }
	inline NodeType GetType() const { return type; }
	inline std::vector<Node*>* GetSubnodes() { return subnodes; }

	inline void SetType(NodeType type) { this->type = type; }
	
	inline void RemoveAt(int index) { subnodes->erase(subnodes->begin() + index); }
	inline void Append(Node* node) { subnodes->push_back(node); }

	std::string PrintNode(int indent);

	Node(Token* token, NodeType type) : token(token), type(type) { subnodes = new std::vector<Node*>(); }
	~Node()
	{
		delete subnodes;
	}
};

static std::ostream& operator<<(std::ostream& o, const Node& n)
{
	o << "Node: " << n.GetType() << ", <" << n.GetToken() << '>';
	return o;
}