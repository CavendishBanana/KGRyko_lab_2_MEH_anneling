#include "LogarhitmicCooling.h"

double LogarhitmicCooling::getNextTemperature()
{
	return startingTemperature / log( static_cast<double>(++n));
}

LogarhitmicCooling::LogarhitmicCooling(double startingTemperature) :ICoolingFunction(startingTemperature, 1), startingTemperature(startingTemperature)
{}
