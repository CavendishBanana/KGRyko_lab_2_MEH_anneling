#include "ContinueConditionMaxIters.h"

ContinueConditionMaxIters::ContinueConditionMaxIters(unsigned int maxIterations) : maxIterations(maxIterations)
{

}

bool ContinueConditionMaxIters:: continueCondition(double currentTemperature, unsigned int iterationsCount, double targetFunctionValue)
{
	return iterationsCount < maxIterations;
}

