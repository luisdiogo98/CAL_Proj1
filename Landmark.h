#pragma once

class Landmark
{
private:
	unsigned long long id;
	double x;
	double y;
public:
	Landmark(int id, double x, double y);
	void setID(int id);
	int getID() const;
	double getX() const;
	double getY() const;
	bool advanceTime();
};
