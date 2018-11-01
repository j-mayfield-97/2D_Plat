#pragma once
#include "Vector2.h"

class Bounding
{

public:
	Bounding();
	~Bounding();

	Vector2 center;
	Vector2 halfSize;

	Bounding(Vector2 center, Vector2 halfSize);
	bool Overlaps(Bounding other);
};

