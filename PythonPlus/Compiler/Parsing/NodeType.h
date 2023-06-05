#pragma once
#include <ostream>

enum class NodeType
{
	UNKNOWN,
	BLOCK,
	NEWLINE,
	SPACE,
	STRING,
};

static std::ostream& operator<<(std::ostream& o, const NodeType& t)
{
	switch (t)
	{
		case NodeType::UNKNOWN:
			o << "UNKNOWN";
			break;
		case NodeType::BLOCK:
			o << "BLOCK";
			break;
		case NodeType::NEWLINE:
			o << "NEWLINE";
			break;
		case NodeType::SPACE:
			o << "SPACE";
			break;
		case NodeType::STRING:
			o << "STRING";
			break;
	}

	return o;
}