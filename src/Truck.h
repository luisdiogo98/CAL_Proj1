#pragma once

#include "Graph.h"
#include "Landmark.h"

class Truck
{
private:
	GarbageType tt;
	float capacity;
	Landmark* g;
public:
	Truck(GarbageType tt, float cap, Landmark* g);
	void setType(GarbageType tt);
	void setCapacity(int cap);
	void setGarage(Landmark* g);
	GarbageType getType();
	float getCapacity();
	Landmark* getGarage();
};