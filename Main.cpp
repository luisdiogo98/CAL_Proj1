#include <iostream>

using namespace std;

bool mainMenu()
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
	cout << "5 - Add/Remove Trucks" << endl;
	cout << "6 - Send Truck" << endl;
	cout << "7 - Exit" << endl;

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
				repeat = false;
				return true;
			}
			case 2:
			{
				repeat = false;
				return true;
			}
			case 3:
			{
				repeat = false;
				return true;
			}
			case 4:
			{
				repeat = false;
				return true;
			}
			case 5:
			{
				repeat = false;
				return true;
			}
			case 6:
			{
				repeat = false;
				return true;
			}
			case 7:
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
	while (mainMenu());
	return 0;
}