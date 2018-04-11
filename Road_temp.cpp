#include "Road_temp.h"

Road::Road()
{
	this->id = 0;
	this->name = "";
	this->two_ways = false;
}

Road::Road(unsigned long long id, string nome, bool t):id(id), name(nome), two_ways(t){}

void Road::setName(string n)
{
	this->name = n;
}

string Road::getName()
{
	return name;
}

void Road::settwoways(bool weis)
{
	this->two_ways = weis;
}

bool Road::gettwoways()
{
	return two_ways;
}

void Road::setId(unsigned long long id)
{
	this->id = id;
}

unsigned long long Road::getId()
{
	return id;
}