#pragma once

#include "Graph.h"
#include "Landmark.h"

typedef enum {INDISCRIMINATED, PLASTIC, PAPER, GLASS} GarbageType;

class Truck
{
private:
	GarbageType tt;
	float capacity;
	Vertex<Landmark>* g;
public:
	Truck(GarbageType tt, float cap, Vertex<Landmark>* g);
	void setType(GarbageType tt);
	void setCapacity(int cap);
	void setGarage(Vertex<Landmark>* g);
	GarbageType getType();
	float getCapacity();
	Vertex<Landmark>* getGarage();
};