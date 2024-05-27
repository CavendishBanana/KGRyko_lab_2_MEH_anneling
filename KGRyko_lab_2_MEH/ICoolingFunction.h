#pragma once
class ICoolingFunction
{
protected:
	double currentTemperature;
	unsigned int n;
public:
	ICoolingFunction(double currentTemperature, unsigned int n=0);
	virtual double getNextTemperature() = 0;

	virtual ~ICoolingFunction();

	inline double getCurrentTemperature() { return currentTemperature; }
};



