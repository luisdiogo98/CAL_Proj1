#include <stdlib.h>
#include "Container.h"

Container::Container(int id, double x, double y, GarbageType type, float garbageGrowth, float capacity) : Landmark(id, x, y)
{
	this->type = type;
	this->garbageGrowth = garbageGrowth;
	this->capacity = capacity;
	filled = 0;
}

bool Container::advanceTime()
{
	if (isFull())
		return false;

	float randomGarbage = ((rand() % 101) / 100.0) * garbageGrowth;
	filled += randomGarbage;

	if (filled > capacity)
		filled = capacity;

	return isFull();
}

bool Container::isFull() const
{
	return filled == capacity;
}

void Container::visit()
{
	filled = 0;
}

GarbageType Container::getType()
{
	return type;
}

float Container::getCurrentLoad()
{
	return filled;
}

float Container::getCapacity()
{
	return capacity;
}

string Container::getColor()
{
	if (type == INDISCRIMINATED)
	{
		return "GRAY";
	}
	else if (type == PLASTIC)
	{
		return "YELLOW";
	}
	else if (type == PAPER)
	{
		return "BLUE";
	}
	else
	{
		return "GREEN";
	}
}
