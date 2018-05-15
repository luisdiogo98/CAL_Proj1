#include "Company.h"
#include "Garage.h"
#include "Container.h"
#include "graphviewer.h"

int kmpMatcher(string text, string pattern);

string type_name[] = { "INDISCRIMINATED", "PLASTIC", "PAPER", "GLASS" };
int visited = 0;

Company::Company(Graph<Landmark*> m)
{
	map = m;
}

Company::~Company()
{
	vector<Vertex<Landmark*>*> pontos = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::iterator it = pontos.begin(); it != pontos.end(); it++)
	{
		delete((*it)->info);
		delete(*it);
	}

	for (vector<Truck*>::iterator it = Trucks.begin(); it != Trucks.end(); it++)
		delete(*it);
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

void Company::addTruck(Truck * t)
{
	Trucks.push_back(t);
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
	unsigned int edgeID = 0;
	GraphViewer *gv = new GraphViewer(1000, 1000, false);
	gv->createWindow(1000, 1000);

	vector<Vertex<Landmark*>*> vertices = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		gv->addNode((*it)->info->getID(), (*it)->info->getX(), (*it)->info->getY());

		gv->setVertexColor((*it)->info->getID(), (*it)->info->getColor());
		gv->setVertexLabel((*it)->info->getID(), (*it)->info->display());
	}

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		vector<Edge<Landmark*>*> edges = (*it)->outgoing;

		for (vector<Edge<Landmark*>*>::const_iterator ti = edges.begin(); ti != edges.end(); ti++)
		{
			gv->addEdge(edgeID, (*it)->info->getID(), (*ti)->dest->info->getID(), EdgeType::DIRECTED);
			gv->setEdgeLabel(edgeID, (*ti)->name);
			edgeID++;
		}
	}

	gv->rearrange();
	free(gv);
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

	if (garbage)
	{
		if (garbage + v->filling > capacity)
			garbage = 0;

		else
		{
			vector<Landmark*> oldpath = v->fullpath;

			for (vector<Landmark*>::iterator it = oldpath.begin(); it != oldpath.end(); it++)
				if ((*it)->getID() == w->info->getID())
				{
					garbage = 0;
					break;
				}
		}
	}

	if (v->dist + weight - (garbage * 10) < w->dist)
	{
		w->dist = v->dist + weight - (garbage * 10);
		w->fullpath = v->fullpath;
		w->fullpath.push_back(v->info);
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

	if (v == nullptr || min_dist == INF)
	{
		cout << endl << "No way found!" << endl;
		return res;
	}

	res = v->fullpath;
	res.push_back(v->info);

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

	cout << endl << "Garbage Collected: " << filling << endl;

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
		for (auto e : v->outgoing)
		{
			auto oldDist = e->dest->dist;
			if (relaxGarbage(v, e->dest, e->weight, tipo, capacity))
			{
				if (oldDist == INF)
					q.insert(e->dest);

				else q.decreaseKey(e->dest);
			}
		}
	}

	return getNearestTreatmentStation(garage, tipo, capacity);
}

void Company::showWay(vector<Landmark*> way) const
{
	unsigned int edgeID = 0;
	GraphViewer *gv = new GraphViewer(1000, 1000, false);
	gv->createWindow(1000, 1000);

	vector<Vertex<Landmark*>*> vertices = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		gv->addNode((*it)->info->getID(), (*it)->info->getX(), (*it)->info->getY());

		gv->setVertexColor((*it)->info->getID(), (*it)->info->getColor());
		gv->setVertexLabel((*it)->info->getID(), (*it)->info->display());
	}

	for (vector<Vertex<Landmark*>*>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		vector<Edge<Landmark*>*> edges = (*it)->outgoing;

		for (vector<Edge<Landmark*>*>::const_iterator ti = edges.begin(); ti != edges.end(); ti++)
		{
			gv->addEdge(edgeID, (*it)->info->getID(), (*ti)->dest->info->getID(), EdgeType::DIRECTED);

			for (vector<Landmark*>::const_iterator tri = way.begin(); tri != way.end(); tri++)
			{
				if (tri + 1 == way.end())
					break;

				if ((*tri)->getID() == (*it)->info->getID() && (*(tri + 1))->getID() == (*ti)->dest->info->getID())
				{
					gv->setEdgeColor(edgeID, "RED");
					gv->setEdgeThickness(edgeID, 5);
				}
			}

			edgeID++;
		}
	}

	gv->rearrange();
	free(gv);
}

void Company::displayFullContainers()
{
	cout << "Full containers:" << endl << endl;

	int i = 0;

	vector<Vertex<Landmark*>*> v = map.getVertexSet();

	for (vector<Vertex<Landmark*>*>::iterator it = v.begin(); it != v.end(); it++)
	{
		if ((*it)->getInfo()->isFull())
		{
			i++;
			Container * c = (Container*)(*it)->getInfo();
			cout << i << ": ID - " << c->getID() << "   Type - " << type_name[c->getType()] << "   Capacity - " << c->getCapacity() << "   Current Load - " << c->getCurrentLoad() << endl;
		}
	}

	if (!i)
		cout << "No full containers." << endl;

	getchar();
}

void Company::addTruck()
{
	Truck* t;
	GarbageType tt;
	float capacity;
	Landmark* g;

	cout << "Choose truck type:" << endl;
	cout << "1 - INDISCRIMINATED" << endl;
	cout << "2 - PLASTIC" << endl;
	cout << "3 - PAPER" << endl;
	cout << "4 - GLASS" << endl;

	int choice;
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > 4)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insert a valid option." << endl;
		cin >> choice;
	}

	switch (choice)
	{
	case 1:
	{
		tt = INDISCRIMINATED;
		break;
	}
	case 2:
	{
		tt = PLASTIC;
		break;
	}
	case 3:
	{
		tt = PAPER;
		break;
	}
	case 4:
	{
		tt = GLASS;
		break;
	}
	}

	cout << endl << "Insert truck capacity: ";
	cin >> capacity;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insert a valid option." << endl;
		cin >> capacity;
	}

	cout << endl << "Available garages:" << endl;

	int i = 0;
	for (vector<Landmark*>::iterator it = Garages.begin(); it != Garages.end(); it++)
	{
		i++;
		cout << i << ": ID - " << (*it)->getID() << endl;
	}

	cin >> choice;

	while (cin.fail() || choice < 1 || choice > i)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insert a valid option." << endl;
		cin >> choice;
	}

	g = Garages.at(choice - 1);
	t = new Truck(tt, capacity, g);
	((Garage *)Garages.at(choice - 1))->addTruck(t);
	addTruck(t);
}

void Company::removeTruck()
{
	if (Trucks.size() == 0)
	{
		cout << "No available trucks. Press ENTER to continue." << endl;
		getchar();
		return;
	}

	cout << "Avaliable trucks:" << endl << endl;

	int i = 0;
	for (vector<Truck*>::iterator it = Trucks.begin(); it != Trucks.end(); it++)
	{
		i++;
		cout << i << ": Type - " << type_name[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
	}

	cout << endl << "Select truck to remove (0 to cancel): ";
	int choice;
	cin >> choice;

	while (cin.fail() || choice < 0 || choice > i)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insert a valid option." << endl;
		cin >> choice;
	}

	if (choice == 0)
		return;

	((Garage *)Trucks.at(choice - 1)->getGarage())->removeTruck((Trucks.at(choice - 1)));
	removeTruck(Trucks.at(choice - 1));
}

void Company::advanceTime()
{
	vector<Landmark*> cont = map.dfs();

	for (vector<Landmark*>::iterator it = cont.begin(); it != cont.end(); it++)
		(*it)->advanceTime();

	cout << "Time advanced." << endl << endl;
}

void Company::displayTrucks()
{
	if (Trucks.size() == 0)
	{
		cout << "No available trucks." << endl;
		getchar();
		return;
	}

	cout << "Avaliable trucks:" << endl << endl;

	int i = 0;
	for (vector<Truck*>::iterator it = Trucks.begin(); it != Trucks.end(); it++)
	{
		i++;
		cout << i << ": Type - " << type_name[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
	}
	getchar();
}

void Company::showGaragesandStations()
{
	cout << endl << "Available garages:" << endl;

	int i = 0;
	for (vector<Landmark*>::iterator it = Garages.begin(); it != Garages.end(); it++)
	{
		i++;
		cout << i << ": ID - " << (*it)->getID() << endl;
	}

	cout << endl << "Available treatment stations:" << endl;

	i = 0;
	for (vector<Landmark*>::iterator it = TreatmentStations.begin(); it != TreatmentStations.end(); it++)
	{
		i++;
		cout << i << ": ID - " << (*it)->getID() << endl;
	}
}

void Company::sendTruck()
{
	if (Trucks.size() == 0)
	{
		cout << "No available trucks." << endl;
		getchar();
		return;
	}

	cout << "Avaliable trucks:" << endl << endl;

	int i = 0;
	for (vector<Truck*>::iterator it = Trucks.begin(); it != Trucks.end(); it++)
	{
		i++;
		cout << i << ": Type - " << type_name[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
	}

	cout << endl << "Select truck to send (0 to cancel): ";
	int choice;
	cin >> choice;

	while (cin.fail() || choice < 0 || choice > i)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Insert a valid option." << endl;
		cin >> choice;
	}

	if (choice == 0)
		return;

	vector<Landmark*> way = sendTruck(Trucks.at(choice - 1));

	showWay(way);
}

void Company::searchContainer(string name1, string name2)
{
	bool found = false;
	for (auto v : map.vertexSet)
		for (auto e1 : v->incoming)
			if (e1->name == name1)
				for (auto e2 : v->incoming)
					if (e2->name == name2)
					{
						found = true;
						cout << v->info->print() << " found at intersection between " << name1 << " and " << name2 << endl;
					}

	if (!found)
		cout << "No intersection between " << name1 << " and " << name2 << endl;
}

void Company::searchExactContainer()
{
	string street1, street2;
	cout << "Insert first street name: ";
	getline(cin, street1);
	cout << "Insert second street name: ";
	getline(cin, street2);

	vector<string> match1;
	vector<string> match2;

	for (auto nome : streetNames)
	{
		if (kmpMatcher(nome, street1))
			match1.push_back(nome);

		if (kmpMatcher(nome, street2))
			match2.push_back(nome);
	}

	if (match1.empty())
		cout << "Could not find " << street1 << ".\n";

	if (match2.empty())
		cout << "Could not find " << street2 << ".\n";

	if (match1.empty() || match2.empty())
	{
		getchar();
		return;
	}

	for (auto name1 : match1)
		for (auto name2 : match2)
			searchContainer(name1, name2);
}