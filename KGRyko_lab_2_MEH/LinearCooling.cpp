#include "LinearCooling.h"

LinearCooling::LinearCooling(double startingTemperature, double alpha, unsigned int n ): ICoolingFunction(startingTemperature, n), alpha(alpha)
{
    
}

double LinearCooling::getNextTemperature()
{
    currentTemperature = currentTemperature - alpha * (++n);
    return currentTemperature;
}
