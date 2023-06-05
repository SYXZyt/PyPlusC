#pragma once
#include <ostream>

class Vector2
{
public:
	int x;
	int y;

	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
};

static std::ostream& operator<<(std::ostream& o, const Vector2& v)
{
	o << "Pos: " << v.x << ", Line: " << v.y + 1;
	return o;
}