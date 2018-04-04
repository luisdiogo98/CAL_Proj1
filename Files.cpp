#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include <ctime>

#include "Company.h"


using namespace std;

void Company::read_files() {





ifstream my_nodes("Nodes.txt");
ifstream my_roads("Edges_Info.txt");



string node_line;
string road_line;



//--------------------NODES---------------------------
if (my_nodes.fail())
{
	cerr << "Unable to open nodes file! \n";
	exit(1);
}
srand(time(NULL));
while (!my_nodes.eof())
{
	getline(my_nodes, node_line);
	Trata_fich_nodes(node_line);

}
my_nodes.close();

//--------------------ROADS---------------------------
if (my_roads.fail())
{
	cerr << "Unable to open roads file! \n";
	exit(1);
}

while (!my_roads.eof())
{
	getline(my_roads, road_line);
	if (road_line == "")
		break;
	Trata_fich_roads(road_line); 
}
my_roads.close();

}

void Company::Trata_fich_nodes(string text_line)
{
	unsigned long long id;
	double lat_deg, longe_deg;

	stringstream linha(text_line);
	char p_virgula;

	linha >> id >> p_virgula;

	linha >> lat_deg>> p_virgula;
	linha >> longe_deg>> p_virgula;
	int random = rand() % 100;
	Landmark *info;

	info = new Landmark(id,lat_deg,longe_deg);

	map.addVertex(info);
}


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








void Company::Trata_fich_roads(string text_line)
{


	unsigned long long id;
	string nome, is_two_ways;
	string conn_line;
	string nome_fich = "Edges.txt";

	stringstream linha(text_line);
	char p_virgula, carater;

	linha >> id >> p_virgula;

	carater = linha.get(); 
	//nome
	while (carater != ';')
	{
		nome = nome + carater;
		carater = linha.get();
	}
	carater = linha.get();
	while (carater != -1)
	{
		is_two_ways = is_two_ways + carater;
		carater = linha.get();
	}

	char c = tolower(is_two_ways.at(0));
	is_two_ways.at(0) = c;

	///////////////////////////////////////////////////////////////////

	ifstream my_conns(nome_fich);
	
	if (my_conns.fail())
	{
		cerr << "Unable to open file! \n";
		exit(1);
	}
	
	
	vector<Vertex<Landmark*>*> v = map.getVertexSet();

	while (!my_conns.eof())
	{
		unsigned long long id_read, idnode1, idnode2;
		char p_virgula;
		getline(my_conns, conn_line);
		stringstream linha(conn_line);

		linha >> id_read >> p_virgula >> idnode1 >> p_virgula>> idnode2 >> p_virgula;

		if (id_read == id) 
		{
			Vertex<Landmark*>* source = NULL;
			Vertex<Landmark*>* dest = NULL;

			

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

			//fazer calculo de distancia
			double dist = haversine_distance(source->getInfo()->getX(),source->getInfo()->getY(),dest->getInfo()->getX(),dest->getInfo()->getY());
			Edge<Landmark*> e(source,dist);
			e.setName(nome);
			map.addEdge(source->getInfo(), dest->getInfo(), dist);

		}
		else
		{
			continue;
		}

		

		



	}
	my_conns.close();



}



