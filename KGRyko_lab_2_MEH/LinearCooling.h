#pragma once
#include "ICoolingFunction.h"
class LinearCooling :
    public ICoolingFunction
{
private:
    double alpha;

public:
    LinearCooling(double startingTemperature, double alpha, unsigned int n= 0);
    double getNextTemperature() override;
};

