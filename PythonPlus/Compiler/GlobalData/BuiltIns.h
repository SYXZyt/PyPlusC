#pragma once
#include <string>
#include <vector>
#include <unordered_map>

//Stores each built-in phrase the compiler has. These are like pass through terms
//A word will be converted into one which Python understands
//For example, writing "false" will be converted to Python's "False"
static std::unordered_map<std::string, std::string> BuiltIn
{
	{"false", "False"},
	{"true", "True"},
	{"null", "None"},
};

//Stores any keyword which we are not allowed to use in a name.
//Most of these are Python keywords, and so will cause errors if we name a variable after them
static std::vector<std::string> RestrictedKeywords
{
	"pass",
	"True",
	"False",
	"None",
};