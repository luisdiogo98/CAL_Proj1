#pragma once

#include<string>

using namespace std;

class Road
{
	unsigned long long id;
	string name;
	bool two_ways;

public :
	Road();
	Road(unsigned long long id, string nome, bool t);
	void setName(string n);
	string getName();
	void settwoways(bool weis);
	bool gettwoways();
	void setId(unsigned long long id);
	unsigned long long getId();
};
