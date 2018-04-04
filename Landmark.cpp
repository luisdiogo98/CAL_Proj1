#include "Landmark.h"

using namespace std;

Landmark::Landmark(int id, double x, double y)
{
	this->id = id;
	this->x = x;
	this->y = y;
}

int Landmark::getID() const
{
	return id;
}

double Landmark::getX() const
{
	return x;
}

double Landmark::getY() const
{
	return y;
}

void Landmark::advanceTime()
{
}
