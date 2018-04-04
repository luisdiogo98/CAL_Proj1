#pragma once

#include "Landmark.h"
#include "Graph.h"
#include "Truck.h"

class Company
{
private:
	Graph<Landmark*> map;
	vector<Landmark*> Garages;
	vector<Landmark*> TreatmentStations;
	vector<Landmark*> FullContainers;
public:
	Company();
};