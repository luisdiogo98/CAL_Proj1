#pragma once

#include "Truck.h"
#include "Landmark.h"

class TreatmentStation : public Landmark
{
public:
	TreatmentStation(int id, double x, double y);
	string getColor();
	string display() const;
	string print() const;
};