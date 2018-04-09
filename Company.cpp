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

bool Company::relaxGarbage(Vertex<Landmark*> *v, Vertex<Landmark*> *w, double weight, GarbageType tipo, double capacity)
{
	double garbage = w->info->getGarbage(tipo);

	if (garbage + v->filling > capacity)
		garbage = 0;

	if (v->dist + weight - garbage < w->dist) 
	{
		w->dist = v->dist + weight - garbage;
		w->path = v;
		w->filling = v->filling + garbage;
		return true;
	}

	else return false;
}

vector<Landmark*> Company::getNearestTreatmentStation(Landmark * garage, GarbageType tipo, double capacity)
{
	vector<Landmark*> res;
	Vertex<Landmark*>* v;
	double min_dist = INF;

	for (vector<Landmark*>::iterator it = TreatmentStations.begin(); it != TreatmentStations.end(); it++)
	{
		auto aux = map.findVertex(*it);
		if (aux == nullptr || aux->dist == INF) // missing or disconnected
			continue;

		if (aux->dist < min_dist)
		{
			v = aux;
			min_dist = aux->dist;
		}
	}

	if (min_dist == INF)
		return res;

	for (; v != nullptr; v = v->path)
		res.push_back(v->info);

	reverse(res.begin(), res.end());

	double filling = 0;

	for (vector<Landmark*>::iterator it = res.begin(); it != res.end(); it++)
	{
		double garbage = (*it)->getGarbage(tipo);

		if (!garbage)
			continue;

		if (filling + garbage <= capacity)
		{
			(*it)->emptyGarbage();
			filling += garbage;
		}
	}

	return res;
}


vector<Landmark*> Company::sendTruck(Truck* truck)
{
	Landmark* garage = truck->getGarage();
	GarbageType tipo = truck->getType();
	double capacity = truck->getCapacity();

	auto s = map.initSingleSourceNegative(garage);
	MutablePriorityQueue<Vertex<Landmark*>> q;
	q.insert(s);

	while (!q.empty()) 
	{
		auto v = q.extractMin();
		for (auto e : v->adj) 
		{
			auto oldDist = e.dest->dist;
			if (relaxGarbage(v, e.dest, e.weight, tipo, capacity)) 
			{
				if (oldDist == INF)
					q.insert(e.dest);

				else q.decreaseKey(e.dest);
			}
		}
	}

	return getNearestTreatmentStation(garage, tipo, capacity);
}
