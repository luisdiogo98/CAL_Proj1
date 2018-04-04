#include "Landmark.h"

using namespace std;

Landmark::Landmark(int id, double x, double y)
{
	this->id = id;
	this->x = x;
	this->y = y;
}

int Landmark::getID()
{
	return id;
}

double Landmark::getX()
{
	return x;
}

double Landmark::getY()
{
	return y;
}

void Landmark::advanceTime()
{
}
