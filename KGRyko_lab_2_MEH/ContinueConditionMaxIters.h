#pragma once
#include "IContinueCondition.h"
class ContinueConditionMaxIters :
    public IContinueCondition
{
private:
    unsigned int maxIterations;

public:
    ContinueConditionMaxIters(unsigned int maxIterations);
    bool continueCondition(double currentTemperature, unsigned int iterationsCount, double targetFunctionValue) override;
};

