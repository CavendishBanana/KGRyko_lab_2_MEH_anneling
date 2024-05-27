#pragma once
#include "ICoolingFunction.h"
#include <cmath>
class LogarhitmicCooling :
    public ICoolingFunction
{

private:
    double startingTemperature;
public:
    double getNextTemperature() override;
    LogarhitmicCooling(double startingTemperature);

};

