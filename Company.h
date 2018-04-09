#pragma once

#include "Landmark.h"
#include "Graph.h"
#include "Truck.h"
#include <map>

class Company
{
private:
	Graph<Landmark*> map;
	vector<Landmark*> Garages;
	vector<Landmark*> TreatmentStations;
	vector<Landmark*> FullContainers;
	vector<Truck*> Trucks;

	bool relaxGarbage(Vertex<Landmark*> *v, Vertex<Landmark*> *w, double weight, GarbageType tipo, double capacity);
	vector<Landmark*> getNearestTreatmentStation(Landmark *garage, GarbageType tipo, double capacity);
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
	void showMap() const;
	void Trata_fich_roads(string text_line);
	void read_files();
	void Trata_fich_nodes(string text_lines);
	void fixIndex();
	vector<Landmark*> sendTruck(Truck* truck);
	void showWay(std::map<int,Landmark*> way) const;
};