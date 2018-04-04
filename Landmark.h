#pragma once

class Landmark
{
private:
	int id;
	double x;
	double y;
public:
	Landmark(int id, double x, double y);
	int getID() const;
	double getX() const;
	double getY() const;
	void advanceTime();
};
