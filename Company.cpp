#include "Company.h"
#include "graphviewer.h"
#include <float.h>

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

		gv->setVertexColor((*it)->info->getID(), (*it)->info->getColor());

		if ((*it)->info->isFull())
		{
			gv->setVertexLabel((*it)->info->getID(), "FULL");
		}
	}

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		vector<Edge<Landmark*>> edges = (*it)->adj;

		for (vector<Edge<Landmark*>>::const_iterator ti = edges.begin(); ti != edges.end(); ti++)
		{
			gv->addEdge(edgeID, (*it)->info->getID(), ti->dest->info->getID(), EdgeType::DIRECTED);
			gv->setEdgeLabel(edgeID, ti->name);
			edgeID++;
		}
	}

	gv->rearrange();
	free(gv); //Cuidado com este free
}

void Company::fixIndex()
{
	int i = 0;
	vector<Vertex<Landmark*>*> v = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::iterator it = v.begin(); it != v.end(); it++)
	{
		(*it)->info->setID(i);
		i++;
	}
}

bool Company::relaxGarbage(Vertex<Landmark*> *v, Vertex<Landmark*> *w, double weight)
{
	if (v->dist + weight - w->info->getGarbage() < w->dist) 
	{
		w->dist = v->dist + weight - w->info->getGarbage();
		w->path = v;
		return true;
	}

	else return false;
}


vector<Landmark*> Company::sendTruck(Truck* truck)
{
	Landmark* garage = truck->getGarage();

	auto s = map.initSingleSource(garage);
	MutablePriorityQueue<Vertex<Landmark*>> q;
	q.insert(s);

	while (!q.empty()) 
	{
		auto v = q.extractMin();
		for (auto e : v->adj) 
		{
			auto oldDist = e.dest->dist;
			if (relaxGarbage(v, e.dest, e.weight)) 
			{
				if (oldDist == DBL_MAX)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}

	return map.getPath(garage, TreatmentStations[0]);
}
