#include "Company.h"
#include "graphviewer.h"

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

void Company::showMap() const
{
	unsigned long long edgeID = 0;
	//Checkar const em caso de erro
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	vector<Vertex<Landmark*>*> vertices = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		gv->addNode((*it)->info->getID(), (*it)->info->getX() * 10000 - 41.1 * 10000, (*it)->info->getY() * 10000 + 8.6 * 10000);

		vector<Edge<Landmark*>> edges = (*it)->adj;

		for (vector<Edge<Landmark*>>::const_iterator ti = edges.begin(); ti != edges.end(); ti++)
		{
			gv->addEdge(edgeID, (*it)->info->getID(), ti->dest->info->getID(), EdgeType::DIRECTED);
			gv->setEdgeLabel(edgeID, ti->name);
			cout << ti->name << endl;
			edgeID++;
		}
	}

	gv->rearrange();
	free(gv); //Cuidado com este free
}
