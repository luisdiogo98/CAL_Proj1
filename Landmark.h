#pragma once
#include <string>

typedef enum { INDISCRIMINATED, PLASTIC, PAPER, GLASS } GarbageType;

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
	virtual bool isFull() const;
	virtual bool advanceTime();
	virtual std::string getColor();
	virtual double getGarbage(GarbageType tipo) const;
	virtual void emptyGarbage();
	virtual std::string display() const;
};
