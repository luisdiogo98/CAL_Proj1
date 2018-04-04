#include <stdlib.h>
#include "Container.h"

Container::Container(int id, double x, double y, GarbageType type, float garbageGrowth, float capacity) : Landmark(id, x, y)
{
	this->type = type;
	this->garbageGrowth = garbageGrowth;
	this->capacity = capacity;
	filled = 0;
}

bool Container::advanceTime(float time)
{
	float randomGarbage = ((rand() % 101) / 100.0) * garbageGrowth * time;
	filled += randomGarbage;

	return isFull();
}

bool Container::isFull() const
{
	return filled >= capacity;
}

void Container::visit()
{
	filled = 0;
}
