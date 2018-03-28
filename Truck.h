#pragma once

typedef enum {INDISCRIMINATED, PLASTIC, PAPER, GLASS} GarbageType;

class Truck
{
private:
	GarbageType tt;
	float capacity;
	Vertex* g;
public:
	Truck(GarbageType tt, float cap, Vertex* g);
	void setType(GarbageType tt);
	void setCapacity(int cap);
	void setGarage(Vertex* g);
	GarbageType getType();
	float getCapacity();
	Vertex* getGarage();
};