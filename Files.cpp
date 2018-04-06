#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include <ctime>
#include <map> //rip, nao consegui implementar, estava a dar erros com o insert

#include "Company.h"
#include "Road_temp.h"


using namespace std;




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



double deg2rad(double deg) {
	return (deg * (acos(-1))) / 180;
}


double rad2deg(double rad) {
	return (rad * 180 / (acos(-1)));
}


void Company::read_files() {

	/*typedef std::map<unsigned long long, Landmark* > nodes;
	typedef std::map<unsigned long long, Landmark* > roads;*/
	//vector<Landmark*> nodes; nao deve ser necessario
	vector<Road>roads;
	
	

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
	    unsigned long long id,
		double lat_deg, longe_deg;

	stringstream linha_node(node_line);
	char p_virgula;

	linha_node >> id >> p_virgula;

	linha_node >> lat_deg >> p_virgula;
	linha_node >> longe_deg >> p_virgula;
	int random = rand() % 100;
	Landmark *info = new Landmark(id, lat_deg, longe_deg);
	//verificar se esta dentro dos limites do min e max de latitutes e longitudes ??
	
	
	//temporario
	//nodes.push_back(info);

	
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


	Road r = Road(road_id, nome, dois_sentidos);
	roads.push_back(r);

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

	unsigned long long road_id, idnode1, idnode2;

	stringstream linha_road2(road_line2);
	char p_virgula;




	linha_road2 >> road_id >> p_virgula;
	linha_road2 >> idnode1 >> p_virgula;
	linha_road2 >> idnode2 >> p_virgula;

	vector<Vertex<Landmark*>*> v = map.getVertexSet();
	
		Vertex<Landmark*>* source;
		Vertex<Landmark*>* dest;




		for (vector<Vertex<Landmark*>*>::iterator it = v.begin(); it != v.end(); it++)
		{
			if ((*it)->getInfo()->getID() == idnode1)
			{
				source = *it;
			}

			if ((*it)->getInfo()->getID() == idnode2)
			{
				dest = *it;
			}


		}


		if (source == NULL || dest == NULL)
			continue;
		
		for (auto a : roads) 
		{
			if (a.getId == road_id)
			{
				double dist = haversine_distance(source->getInfo->getX(), source->getInfo->getY(), dest->getInfo->getX(), dest->getInfo.getY());
				
				map.addEdge(source->getInfo(), dest->getInfo(), dist,a.getName());

				if (a.gettwoways)
				{
					map.addEdge(dest->getInfo(),source->getInfo(), dist,a.getName());
				}
			}
		}
		

	


}
my_roads2.close();





}











