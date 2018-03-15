#include "Truck.h"

using namespace std;

Truck::Truck(TruckType tt, float cap, Vertex* g)
{
	this->tt = tt;
	capacity = cap;
	this->g = g;
}

void Truck::setType(TruckType tt)
{
	this->tt = tt;
}

void Truck::setCapacity(int cap)
{
	capacity = cap;
}

void Truck::setGarage(Vertex * g)
{
	this->g = g;
}

TruckType Truck::getType()
{
	return TruckType();
}

float Truck::getCapacity()
{
	return capacity;
}

Vertex * Truck::getGarage()
{
	return g;
}

