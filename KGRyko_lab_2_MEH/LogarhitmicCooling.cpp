#include "LogarhitmicCooling.h"

double LogarhitmicCooling::getNextTemperature()
{
	n++;
	return startingTemperature / log( static_cast<double>(n));
}

LogarhitmicCooling::LogarhitmicCooling(double startingTemperature) :ICoolingFunction(startingTemperature), startingTemperature(startingTemperature), n(1)
{}
