#pragma once
#include "ICoolingFunction.h"
#include <cmath>
class LogarhitmicCooling :
    public ICoolingFunction
{

private:
    double startingTemperature;
    int n;
public:
    double getNextTemperature();
    LogarhitmicCooling(double startingTemperature);
};

