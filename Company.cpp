#include "Company.h"

Company::Company(Graph<Landmark*> m)
{
	map = m;
}

Graph<Landmark*> Company::getMap()
{
	return map;
}

vector<Landmark*> Company::getGarages()
{
	return Garages;
}

vector<Landmark*> Company::getTreatmentStations()
{
	return TreatmentStations;
}

vector<Landmark*> Company::getFullContainers()
{
	return FullContainers;
}

vector<Truck*> Company::getTrucks()
{
	return Trucks;
}

void Company::addGarage(Landmark * l)
{
	Garages.push_back(l);
}

void Company::addTreatmentStation(Landmark * l)
{
	TreatmentStations.push_back(l);
}

void Company::addFullContainer(Landmark * l)
{
	FullContainers.push_back(l);
}

void Company::addTruck(Truck * t)
{
	Trucks.push_back(t);
}

void Company::removeFullContainer(Landmark * l)
{
	for (vector<Landmark*>::iterator it = FullContainers.begin(); it != FullContainers.end(); it++)
	{
		if (*it == l)
		{
			FullContainers.erase(it);
			return;
		}
	}
}

void Company::removeTruck(Truck * t)
{
	for (vector<Truck*>::iterator it = Trucks.begin(); it != Trucks.end(); it++)
	{
		if (*it == t)
		{
			Trucks.erase(it);
			return;
		}
	}
}
