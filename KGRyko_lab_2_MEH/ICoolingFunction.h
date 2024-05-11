#pragma once
class ICoolingFunction
{
protected:
	double currentTemperature;
public:
	ICoolingFunction(double currentTemperature);
	virtual double getNextTemperature() = 0;
};



