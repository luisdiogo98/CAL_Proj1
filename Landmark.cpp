#include "Landmark.h"

using namespace std;

Landmark::Landmark(int id, double x, double y)
{
	this->id = id;
	this->x = x;
	this->y = y;
}

void Landmark::setID(int id)
{
	this->id = id;
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

bool Landmark::advanceTime()
{
	return false;
}
