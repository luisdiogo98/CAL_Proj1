#pragma once

typedef enum {INDISCRIMINATED, PLASTIC, PAPER, GLASS} TruckType;

class Truck
{
private:
	TruckType tt;
	float capacity;
	Garage* g;
public:
	Truck(TruckType tt, float cap, Garage* g);
	void setType(TruckType tt);
	void setCapacity(int cap);
	void setGarage(Garage* g);
	TruckType getType();
	float getCapacity();
	Garage* getGarage();
};