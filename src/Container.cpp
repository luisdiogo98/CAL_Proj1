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
	return (int)filled == (int)capacity;
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

double Container::getGarbage(GarbageType tipo) const
{
	if (isFull() && tipo == type)
		return filled;

	return 0.0;
}

void Container::emptyGarbage()
{
	filled = 0;
}

string Container::display() const
{
	return to_string((int)filled) + " / " + to_string((int)capacity);
}

string Container::print() const
{
	string ans;

	if (type == INDISCRIMINATED)
	{
		ans = "Indiscriminated";
	}
	else if (type == PLASTIC)
	{
		ans = "Plastic";
	}
	else if (type == PAPER)
	{
		ans = "Paper";
	}
	else
	{
		ans = "Glass";
	}

	ans += " Container";

	return ans;
}
