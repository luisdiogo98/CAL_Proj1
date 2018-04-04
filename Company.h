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
	Company(Graph<Landmark*> m);
	Graph<Landmark*> getMap();
	vector<Landmark*> getGarages();
	vector<Landmark*> getTreatmentStations();
	vector<Landmark*> getFullContainers();
	void addGarage(Landmark* l);
	void addTreatmentStation(Landmark* l);
	void addFullContainer(Landmark* l);
	void removeFullContainer(Landmark* l);
};