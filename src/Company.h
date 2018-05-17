#pragma once

#include "Landmark.h"
#include "Graph.h"
#include "Truck.h"
#include <set>

class Company
{
private:
	Graph<Landmark*> mapa;
	vector<Landmark*> Garages;
	vector<Landmark*> TreatmentStations;
	vector<Truck*> Trucks;
	set<string> streetNames;

	bool relaxGarbage(Vertex<Landmark*> *v, Vertex<Landmark*> *w, double weight, GarbageType tipo, double capacity);
	vector<Landmark*> getNearestTreatmentStation(Landmark *garage, GarbageType tipo, double capacity);
public:
	Company(Graph<Landmark*> m);
	~Company();
	Graph<Landmark*> getMap();
	vector<Landmark*> getGarages();
	vector<Landmark*> getTreatmentStations();
	vector<Truck*> getTrucks();
	void addGarage(Landmark* l);
	void addTreatmentStation(Landmark* l);
	void addTruck(Truck* t);
	void removeTruck(Truck* t);
	void showMap() const;
	void read_files();
	void fixIndex();
	vector<Landmark*> sendTruck(Truck* truck);
	void showWay(vector<Landmark*> way) const;
	void displayFullContainers();
	void addTruck();
	void removeTruck();
	void advanceTime();
	void displayTrucks();
	void showGaragesandStations();
	void sendTruck();
	void searchContainer(string name1, string name2);
	void searchExactContainer();
	void searchApproximateContainer();
};