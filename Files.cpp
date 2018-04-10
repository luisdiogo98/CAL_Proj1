#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include <ctime>
#include <map>

#include "Company.h"
#include "Road_temp.h"
#include "Garage.h"
#include "TreatmentStation.h"
#include "Landmark.h"
#include "Container.h"



const float LAT_MAX = 41.17941;
const float LAT_MIN = 41.15026;
const float LON_MAX = -8.635939;
const float LON_MIN = -8.604123;
const int BACKGROUND_X = 1000;
const int BACKGROUND_Y = 1000;

int longitude_to_x(double l)
{
	return floor(((l - LON_MIN) * BACKGROUND_Y) / (LON_MAX - LON_MIN));
}

int latitude_to_y(double l)
{
	return floor(((l - LAT_MIN) * BACKGROUND_X) / (LAT_MAX - LAT_MIN));
}



using namespace std;

double deg2rad(double deg) {
	return (deg * (acos(-1))) / 180;
}


double rad2deg(double rad) {
	return (rad * 180 / (acos(-1)));
}


double haversine_distance(double lat1d, double lon1d, double lat2d, double lon2d)
{
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}



void Company::read_files() {

	typedef std::map<unsigned long long, Landmark* > nodes;
	typedef std::map<unsigned long long, Road> roads;
	nodes n; 
	roads r;
	
	

ifstream my_nodes("Nodes.txt");
ifstream my_roads("Edges_Info.txt");
ifstream my_roads2("Edges.txt");




string node_line;
string road_line;
string road_line2;



//--------------------NODES---------------------------
if (my_nodes.fail())
{
	cerr << "Unable to open file! \n";
	exit(1);
}
srand(time(NULL));

while (!my_nodes.eof())
{
	getline(my_nodes, node_line);
	unsigned long long id;
	double lati_deg, longi_deg;
	int lat_deg, longe_deg;

	stringstream linha_node(node_line);
	char p_virgula;

	linha_node >> id >> p_virgula;

	linha_node >> lati_deg >> p_virgula;
	linha_node >> longi_deg >> p_virgula;
	int random = rand() % 1000;

	lat_deg = latitude_to_y(lati_deg);
	longe_deg = longitude_to_x(longi_deg);


	Landmark *info;

	if (random < 4)
	{
		info = new Garage(id, lat_deg, longe_deg);
		Garages.push_back(info);
	}
	else if (random < 6)
	{
		info = new TreatmentStation(id, lat_deg, longe_deg);
		TreatmentStations.push_back(info);
	}
	else if (random < 106)
	{
		int cap = 500 + rand() % (1500 - 500 + 1);
		int growth = 400 + rand() % (600 - 400 + 1);
		info = new Container(id, lat_deg, longe_deg, INDISCRIMINATED, growth, cap);
	}
	else if (random < 206)
	{
		int cap = 500 + rand() % (1500 - 500 + 1);
		int growth = 400 + rand() % (600 - 400 + 1);
		info = new Container(id, lat_deg, longe_deg, PLASTIC, growth, cap);
	}
	else if (random < 306)
	{
		int cap = 500 + rand() % (1500 - 500 + 1);
		int growth = 400 + rand() % (600 - 400 + 1);
		info = new Container(id, lat_deg, longe_deg, PAPER, growth, cap);
	}
	else if (random < 406)
	{
		int cap = 500 + rand() % (1500 - 500 + 1);
		int growth = 400 + rand() % (600 - 400 + 1);
		info = new Container(id, lat_deg, longe_deg, GLASS, growth, cap);
	}
	else
	{
		info = new Landmark(id, lat_deg, longe_deg);
	}	
	
	n.insert(std::pair<unsigned long long, Landmark*>(id, info));

	
	map.addVertex(info);

}
my_nodes.close();

//--------------------ROADS---------------------------
if (my_roads.fail())
{
	cerr << "Unable to open file! \n";
	exit(1);
}

while (!my_roads.eof())
{
	getline(my_roads, road_line);
	if (road_line == "")
		break;

	unsigned long long road_id;
	string nome, is_two_ways;

	stringstream linha_road(road_line);
	char p_virgula, carater;
	bool dois_sentidos;


	linha_road >> road_id >> p_virgula;

	carater = linha_road.get();
	//nome
	while (carater != ';')
	{
		nome = nome + carater;
		carater = linha_road.get();
	}
	carater = linha_road.get();


	while (carater != -1)
	{
		is_two_ways = is_two_ways + carater;
		carater = linha_road.get();
	}

	if (is_two_ways == "True")
	{
		dois_sentidos = true;
	}
	else
	{
		dois_sentidos = false;
	}

	Road road = Road(road_id, nome, dois_sentidos);
	r.insert(std::pair<unsigned long long, Road>(road_id, road));

}
my_roads.close();
//-------------------------ROADS2-------------------------


if (my_roads2.fail())
{
	cerr << "Unable to open file! \n";
	exit(1);
}

while (!my_roads2.eof())
{
	getline(my_roads2, road_line2);
	if (road_line2 == "")
		break;

	unsigned long long road_id, idnode1, idnode2;

	stringstream linha_road2(road_line2);
	char p_virgula;




	linha_road2 >> road_id >> p_virgula;
	linha_road2 >> idnode1 >> p_virgula;
	linha_road2 >> idnode2 >> p_virgula;
	
		Vertex<Landmark*>* source;
		Vertex<Landmark*>* dest;

		source = map.findVertex(n.find(idnode1)->second);
		dest = map.findVertex(n.find(idnode2)->second);

		Road road_info = r.find(road_id)->second;
		//double dist = haversine_distance(source->getInfo()->getX(), source->getInfo()->getY(), dest->getInfo()->getX(), dest->getInfo()->getY());
		double dist = sqrt(pow((source->getInfo()->getX() - dest->getInfo()->getX()), 2) + pow((source->getInfo()->getY() - dest->getInfo()->getY()), 2));
		map.addEdge(source->getInfo(), dest->getInfo(), dist, road_info.getName());

		if (road_info.gettwoways())
		{
			map.addEdge(dest->getInfo(), source->getInfo(), dist, road_info.getName());
		}


}
my_roads2.close();





}