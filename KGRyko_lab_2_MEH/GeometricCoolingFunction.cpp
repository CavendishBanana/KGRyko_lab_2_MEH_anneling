#include "GeometricCoolingFunction.h"

GeometricCoolingFunction::GeometricCoolingFunction(double alfa, double startingTemperature) : ICoolingFunction(startingTemperature), alfa(alfa)
{}

double GeometricCoolingFunction::getNextTemperature()
{
	currentTemperature = currentTemperature * alfa;
	return currentTemperature;
}
