#include "Bounding.h"
#include <stdio.h>
#include <iostream>

Bounding::Bounding()
{

}

Bounding::Bounding(Vector2 center, Vector2 halfSize)
{
	this->center = center;
	this->halfSize = halfSize;
}


Bounding::~Bounding()
{
}

bool Bounding::Overlaps(Bounding other)
{
	if (std::abs(center.x_pos - other.center.x_pos) >
		halfSize.x_pos + other.halfSize.x_pos || 
		std::abs(center.y_pos - other.center.y_pos) >
		halfSize.y_pos + other.halfSize.y_pos) return false;

	//if () return false;
	return true;
}