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

bool Landmark::isFull() const
{
	return false;
}

bool Landmark::advanceTime()
{
	return false;
}

string Landmark::getColor()
{
	return "WHITE";
}

double Landmark::getGarbage(GarbageType tipo) const
{
	return 0.0;
}

void Landmark::emptyGarbage(){}

string Landmark::display() const
{
	return "*";
}

string Landmark::print() const
{
	return "Nothing";
}
