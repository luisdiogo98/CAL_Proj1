#include "Garage.h"

using namespace std;

Garage::Garage()
{

}

Garage::Garage(vector<Truck*> tr)
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