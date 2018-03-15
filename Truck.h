#pragma once

typedef enum {INDISCRIMINATED, PLASTIC, PAPER, GLASS} TruckType;

class Truck
{
private:
	TruckType tt;
	float capacity;
	Vertex* g;
public:
	Truck(TruckType tt, float cap, Vertex* g);
	void setType(TruckType tt);
	void setCapacity(int cap);
	void setGarage(Vertex* g);
	TruckType getType();
	float getCapacity();
	Vertex* getGarage();
};