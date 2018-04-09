#pragma once

#include "Truck.h"
#include "Landmark.h"

class Container : public Landmark
{
private:
	GarbageType type;
	float garbageGrowth;
	float filled;
	float capacity;
public:
	Container(int id, double x, double y, GarbageType type, float garbageGrowth, float capacity);
	bool advanceTime();
	bool isFull() const;
	void visit();
	GarbageType getType();
	float getCurrentLoad();
	float getCapacity();
	string getColor();
	double getGarbage(GarbageType type) const;
	void emptyGarbage();
	string display() const;
};