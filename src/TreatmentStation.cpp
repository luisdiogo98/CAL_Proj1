#include "TreatmentStation.h"

TreatmentStation::TreatmentStation(int id, double x, double y) : Landmark(id, x, y)
{
}

string TreatmentStation::getColor()
{
	return "BLACK";
}

string TreatmentStation::display() const
{
	return "Station";
}

string TreatmentStation::print() const
{
	return "Treatment Station";
}
