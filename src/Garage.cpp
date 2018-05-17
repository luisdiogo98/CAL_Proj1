#include "Garage.h"

using namespace std;

Garage::Garage(int id, double x, double y) : Landmark(id, x, y){}

Garage::Garage(int id, double x, double y, vector<Truck*> tr) : Landmark(id, x, y)
{
	trucks = tr;
}

vector<Truck*> Garage::getTrucks()
{
	return trucks;
}

void Garage::setTrucks(vector<Truck*> tr)
{
	trucks = tr;
}

bool Garage::addTruck(Truck* tr)
{
	for (vector<Truck*>::iterator it = trucks.begin(); it != trucks.end(); it++)
	{
		if (*it == tr)
			return false;
	}

	trucks.push_back(tr);
	return true;
}

bool Garage::removeTruck(Truck* tr)
{
	for (vector<Truck*>::iterator it = trucks.begin(); it != trucks.end(); it++)
	{
		if (*it == tr)
		{
			trucks.erase(it);
			return true;
		}
	}
	return false;
}

string Garage::getColor()
{
	return "MAGENTA";
}

string Garage::display() const
{
	return "Garage";
}

string Garage::print() const
{
	return "Garage";
}
