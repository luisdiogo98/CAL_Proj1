#include "Truck.h"

using namespace std;

Truck::Truck(GarbageType tt, float cap, Vertex<Landmark>* g)
{
	this->tt = tt;
	capacity = cap;
	this->g = g;
}

void Truck::setType(GarbageType tt)
{
	this->tt = tt;
}

void Truck::setCapacity(int cap)
{
	capacity = cap;
}

void Truck::setGarage(Vertex<Landmark> * g)
{
	this->g = g;
}

GarbageType Truck::getType()
{
	return GarbageType();
}

float Truck::getCapacity()
{
	return capacity;
}

Vertex<Landmark> * Truck::getGarage()
{
	return g;
}