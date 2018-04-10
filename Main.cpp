#include <iostream>
#include "Company.h"
#include "Graph.h"
#include "Garage.h"
#include "Container.h"

using namespace std;

string type_names[] = { "INDISCRIMINATED", "PLASTIC", "PAPER", "GLASS" };

void sendTruck(Company &c)
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
		cout << i << ": Type - " << type_names[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
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

	vector<Landmark*> way = c.sendTruck(c.getTrucks().at(choice - 1));

	c.showWay(way);
}

void showGaragesandStations(Company &c)
{
	cout << endl << "Available garages:" << endl;

	vector<Landmark*> gar = c.getGarages();
	int i = 0;
	for (vector<Landmark*>::iterator it = gar.begin(); it != gar.end(); it++)
	{
		i++;
		cout << i << ": ID - " << (*it)->getID() << endl;
	}

	cout << endl << "Available treatment stations:" << endl;

	vector<Landmark*> sta = c.getTreatmentStations();
	i = 0;
	for (vector<Landmark*>::iterator it = sta.begin(); it != sta.end(); it++)
	{
		i++;
		cout << i << ": ID - " << (*it)->getID() << endl;
	}
}

void displayTrucks(Company &c)
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
		cout << i << ": Type - " << type_names[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
	}
	getchar();
}

void advanceTime(Company &c)
{
	vector<Landmark*> cont = c.getMap().dfs();

	for (vector<Landmark*>::iterator it = cont.begin(); it != cont.end(); it++)
		(*it)->advanceTime();

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
		cout << i << ": Type - " << type_names[(*it)->getType()] << "   Capacity - " << (*it)->getCapacity() << "   Garage - " << (*it)->getGarage()->getID() << endl;
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
	c.addTruck(t);
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
	cout << "2 - Available Garages and Treatment Stations" << endl;
	cout << "3 - Available Trucks" << endl;
	cout << "4 - Full Containers" << endl;
	cout << "5 - Map" << endl;
	cout << "6 - Add Trucks" << endl;
	cout << "7 - Remove Trucks" << endl;
	cout << "8 - Send Truck" << endl;
	cout << "9 - Exit" << endl;

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
				showGaragesandStations(c);
				repeat = false;
				return true;
			}
			case 3:
			{
				displayTrucks(c);
				repeat = false;
				return true;
			}
			case 4:
			{
				c.displayFullContainers();
				repeat = false;
				return true;
			}
			case 5:
			{
				c.showMap();
				repeat = false;
				return true;
			}
			case 6:
			{
				addTruck(c);
				repeat = false;
				return true;
			}
			case 7:
			{
				removeTruck(c);
				repeat = false;
				return true;
			}
			case 8:
			{
				sendTruck(c);
				repeat = false;
				return true;
			}
			case 9:
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
	c.read_files();
	c.fixIndex();
	while (mainMenu(c));
	return 0;
}