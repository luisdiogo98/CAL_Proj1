#include <iostream>
#include "Company.h"
#include "Graph.h"
#include "Garage.h"
#include "Container.h"

using namespace std;

bool mainMenu(Company &c)
{
	int option;
	bool repeat = true;

	cout << "------------------------------" << endl;
	cout << "------------|MENU|------------" << endl;
	cout << "------------------------------" << endl;
	cout << "1  - Advance Time" << endl;
	cout << "2  - Available Garages and Treatment Stations" << endl;
	cout << "3  - Available Trucks" << endl;
	cout << "4  - Full Containers" << endl;
	cout << "5  - Map" << endl;
	cout << "6  - Add Trucks" << endl;
	cout << "7  - Remove Trucks" << endl;
	cout << "8  - Send Truck" << endl;
	cout << "9  - Exact Search Container" << endl;
	cout << "10 - Approximate Search Container" << endl;
	cout << "0  - Exit" << endl;

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
				c.advanceTime();
				repeat = false;
				return true;
			}
			case 2:
			{
				c.showGaragesandStations();
				repeat = false;
				return true;
			}
			case 3:
			{
				c.displayTrucks();
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
				c.addTruck();
				repeat = false;
				return true;
			}
			case 7:
			{
				c.removeTruck();
				repeat = false;
				return true;
			}
			case 8:
			{
				c.sendTruck();
				repeat = false;
				return true;
			}
			case 9:
			{
				c.searchExactContainer();
				repeat = false;
				return true;
			}
			case 10:
			{
				c.searchApproximateContainer();
				repeat = false;
				return true;
			}
			case 0:
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