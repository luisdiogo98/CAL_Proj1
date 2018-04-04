#include <iostream>
#include "Company.h"
#include "Graph.h"
#include "Garage.h"
#include "Container.h"


using namespace std;

void displayTrucks(Company c)
{
	if (c.getTrucks().size() == 0)
	{
		cout << "No available trucks." << endl;
		getchar();
		return;
	}

	cout << "Avaliable trucks:" << endl << endl;

	vector<Truck*> tr = c.getTrucks();
	int i = 0;
	for (vector<Truck*>::iterator it = tr.begin(); it != tr.end(); it++)
	{
		i++;
		cout << i << ": Type - " << (*it)->getType() << "	Capacity - " << (*it)->getCapacity() << "	Garage - " << (*it)->getGarage()->getID() << endl;
	}
	getchar();
}

void displayFullContainers(Company c)
{
	if (c.getFullContainers().size() == 0)
	{
		cout << "No full containers." << endl;
		getchar();
		return;
	}

	cout << "Full containers:" << endl << endl;

	vector<Landmark*> cont = c.getFullContainers();
	int i = 0;
	for (vector<Landmark*>::iterator it = cont.begin(); it != cont.end(); it++)
	{
		i++;
		Container * c = (Container *) (*it);
		cout << i << ": ID - " << c->getID() << "	Type - " << c->getType() << "	Capacity - " << c->getCapacity() << "	Current Load - " << c->getCurrentLoad() << endl;
	}
	getchar();
}

void advanceTime(Company c)
{
	vector<Landmark*> cont = c.getMap().dfs();
	for (vector<Landmark*>::iterator it = cont.begin(); it != cont.end(); it++)
	{
		if ((*it)->advanceTime())
		{
			c.addFullContainer(*it);
		}
	}
	cout << "Time advanced." << endl << endl;
}

void removeTruck(Company &c)
{
	if (c.getTrucks().size() == 0)
	{
		cout << "No available trucks. Press ENTER to continue." << endl;
		getchar();
		return;
	}
	
	cout << "Avaliable trucks:" << endl << endl;

	vector<Truck*> tr = c.getTrucks();
	int i = 0;
	for (vector<Truck*>::iterator it = tr.begin(); it != tr.end(); it++)
	{
		i++;
		cout << i << ": Type - " << (*it)->getType() << "	Capacity - " << (*it)->getCapacity() << "	Garage - " << (*it)->getGarage()->getID() << endl;
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
	
	((Garage *)tr.at(choice - 1)->getGarage())->removeTruck((tr.at(choice - 1)));
	c.removeTruck(tr.at(choice - 1));
}

void addTruck(Company &c)
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

	vector<Landmark*> gar = c.getGarages();
	int i = 0;
	for (vector<Landmark*>::iterator it = gar.begin(); it != gar.end(); it++)
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

	g = gar.at(choice - 1);
	t = new Truck(tt, capacity, g);
	((Garage *)gar.at(choice - 1))->addTruck(t);
}

bool mainMenu(Company &c)
{
	int option;
	bool repeat = true;

	// main menu
	cout << "------------------------------" << endl;
	cout << "------------|MENU|------------" << endl;
	cout << "------------------------------" << endl;
	cout << "1 - Advance Time" << endl;
	cout << "2 - Available Trucks" << endl;
	cout << "3 - Full Containers" << endl;
	cout << "4 - Map" << endl;
	cout << "5 - Add Trucks" << endl;
	cout << "6 - Remove Trucks" << endl;
	cout << "7 - Send Truck" << endl;
	cout << "8 - Exit" << endl;

	while (repeat)
	{
		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Insert a valid menu option." << endl;
			continue;
		}
		else
		{
			cin.ignore(1000, '\n');
			switch (option)
			{
			case 1:
			{
				advanceTime(c);
				repeat = false;
				return true;
			}
			case 2:
			{
				displayTrucks(c);
				repeat = false;
				return true;
			}
			case 3:
			{
				displayFullContainers(c);
				repeat = false;
				return true;
			}
			case 4:
			{
				c.showMap();
				repeat = false;
				return true;
			}
			case 5:
			{
				addTruck(c);
				repeat = false;
				return true;
			}
			case 6:
			{
				removeTruck(c);
				repeat = false;
				return true;
			}
			case 7:
			{
				repeat = false;
				return true;
			}
			case 8:
			{
				return false;
			}
			default:
			{
				cout << "Insert a valid menu option." << endl;
			}
			}
		}
	}
	return true;
}

int main()
{
	Graph<Landmark*> g;
	Company c(g);
	while (mainMenu(c));
	return 0;
}