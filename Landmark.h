#pragma once

class Landmark
{
private:
	int id;
	double x;
	double y;
public:
	Landmark(int id, double x, double y);
	int getID();
	double getX();
	double getY();
};
