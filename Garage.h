#pragma once

#include "Truck.h"
#include "Landmark.h"
#include <vector>

using namespace std;

class Garage : public Landmark
{
private:
	vector<Truck*> trucks;
public:
	Garage();
	Garage(vector<Truck*> tr);
	vector<Truck*> getTrucks();
	void setTrucks(vector<Truck*> tr);
	bool addTruck(Truck* tr);
	bool removeTruck(Truck * tr);
};