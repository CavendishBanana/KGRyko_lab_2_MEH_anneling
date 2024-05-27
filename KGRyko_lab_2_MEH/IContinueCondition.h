#pragma once
class IContinueCondition
{
public:
	virtual bool continueCondition(double currentTemperature, unsigned int iterationsCount, double targetFunctionValue) = 0;
	virtual ~IContinueCondition();
};

