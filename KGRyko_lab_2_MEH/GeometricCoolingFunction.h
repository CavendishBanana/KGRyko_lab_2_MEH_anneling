#pragma once
#include "ICoolingFunction.h"
class GeometricCoolingFunction :
    public ICoolingFunction
{
private:
    double alfa;

public:
    GeometricCoolingFunction(double alfa, double startTemperature);
    double getNextTemperature();
};

