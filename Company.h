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
	vector<Truck*> Trucks;
public:
	Company(Graph<Landmark*> m);
	Graph<Landmark*> getMap();
	vector<Landmark*> getGarages();
	vector<Landmark*> getTreatmentStations();
	vector<Landmark*> getFullContainers();
	vector<Truck*> getTrucks();
	void addGarage(Landmark* l);
	void addTreatmentStation(Landmark* l);
	void addFullContainer(Landmark* l);
	void addTruck(Truck* t);
	void removeFullContainer(Landmark* l);
	void removeTruck(Truck* t);
};