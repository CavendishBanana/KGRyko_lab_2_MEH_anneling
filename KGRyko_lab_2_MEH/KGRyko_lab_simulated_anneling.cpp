// KGRyko_lab_2_MEH.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "ICoolingFunction.h"
#include "IRangeOperator.h"
#include "GeometricCoolingFunction.h"
#include <random>
#include "IContinueCondition.h"
#include "LinearCooling.h"
#include "GeometricCoolingFunction.h"
#include "LogarhitmicCooling.h"
#include "ContinueConditionMaxIters.h"
#include "NormalRangeOperator.h"

#define twoPi 3.14159265358979323846
#define ePlus20 22.71828182845904523536

using namespace std;

double ackleyFunction(const std::vector<double>& x )
{
    double oneByDimensionality = 1.0 / static_cast<double>(x.size());
    double sum1 = 0.0;
    double sum2 = 0.0;
    auto actionSum = [&sum1, &sum2](const double& x) { sum1 += (x * x); sum2 += cos(twoPi * x); };
    std::for_each(x.begin(), x.end(), actionSum);
    return ePlus20 - 20.0 * exp(-0.2 * sqrt(oneByDimensionality) * sum1) - exp(oneByDimensionality * sum2);
}


vector<double> simulatedAnneling(double (*targetFunction)(const vector<double>&), vector<double> startPoint, ICoolingFunction* coolingFunction,
    IRangeOperator& rangeOperator, unsigned int maxItersPerTemprature, double kParam, IContinueCondition& continueCondition ,bool maximize = false)
{
    int optimalizationType = -1;
    if (maximize)
    {
        optimalizationType = 1;
    }
    vector<double> currentBestSolution = startPoint;
    vector<double> bestGlobalSolution = startPoint;
    double bestGlobalSolutionTargetFunctionValue = targetFunction(bestGlobalSolution);
    double currentBestTargetFunctionValue = targetFunction(startPoint);
    double currentTemperature = coolingFunction->getCurrentTemperature();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    unsigned int n = 0;
    do {
        unsigned int constantTemperatureIterationsCount = 0;
        do {
            vector<double> candidateSolution = rangeOperator(currentBestSolution);
            double candidateSolTargetFun = targetFunction(candidateSolution);
            //candidateSolTargetFun - currentBestTargetFunctionValue
            if (optimalizationType * (candidateSolTargetFun - currentBestTargetFunctionValue) > 0)
            {
                currentBestSolution = std::move(candidateSolution);
                currentBestTargetFunctionValue = candidateSolTargetFun;
            }
            else
            {
                double y = distribution(generator);
                if (y < exp(-optimalizationType * (candidateSolTargetFun - currentBestTargetFunctionValue) / (currentTemperature * kParam)))
                {
                    currentBestSolution = std::move(candidateSolution);
                    currentBestTargetFunctionValue = candidateSolTargetFun;
                }

            }
            if (optimalizationType * (currentBestTargetFunctionValue - bestGlobalSolutionTargetFunctionValue) > 0)
            {
                bestGlobalSolutionTargetFunctionValue = currentBestTargetFunctionValue;
                bestGlobalSolution = std::move(currentBestSolution);
            }
            constantTemperatureIterationsCount++;
        } while (constantTemperatureIterationsCount < maxItersPerTemprature);
        currentTemperature = coolingFunction->getNextTemperature();
        n++;
    }while(continueCondition.continueCondition(currentTemperature, n, bestGlobalSolutionTargetFunctionValue));
    return bestGlobalSolution;
}

vector<double> simulatedAnneling(double (*targetFunction)(const vector<double>&), unsigned int dimensionality, ICoolingFunction* coolingFunction,
    IRangeOperator& rangeOperator, unsigned int maxItersPerTemprature, double kParam, IContinueCondition& continueCondition, bool maximize = false)
{
    vector<double> vecStart = vector<double>( dimensionality, 0.0);
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1000000.0, 1000000.0);
    for (unsigned int i = 0; i < dimensionality; i++)
    {
        vecStart[i] = distribution(generator);
    }
    return simulatedAnneling(targetFunction, vecStart, coolingFunction, rangeOperator, maxItersPerTemprature, kParam, continueCondition, maximize);
}


int main()
{
    unsigned int numberOfIterationsForTemperature = 100;
    double kParam = 2.0;
    unsigned int outerLoopsMaxIterations = 10000;
    double startingTemperature = 1000000.0;
    double alphaLinear = 0.01;
    double alphaGeometric = 0.02;
    
    unsigned int runsCount = 5;
    unsigned int dimensionality = 10;
    double mi = 0.0, sigma = 0.6;
    bool optimizationMaximize = false;
    NormalRangeOperator rangeOperator = NormalRangeOperator(mi, sigma);
    ContinueConditionMaxIters continueCondition = ContinueConditionMaxIters(outerLoopsMaxIterations);

    double linearCoolingResultsAccumulator = 0.0;
    double geometricCoolingResultsAccumulator = 0.0;
    double logarhitmicCoolingResultsAccumulator = 0.0;
    for (unsigned int runIdx = 0; runIdx < runsCount; runIdx++)
    {
        LinearCooling linearCooling = LinearCooling(startingTemperature, alphaLinear);
        GeometricCoolingFunction geometricCooling = GeometricCoolingFunction(alphaGeometric, startingTemperature);
        LogarhitmicCooling logarhitmicCooling = LogarhitmicCooling(startingTemperature);
        
        vector<double> bestSolutionlinearCooling = simulatedAnneling(ackleyFunction, dimensionality, &linearCooling, rangeOperator, numberOfIterationsForTemperature, kParam, continueCondition, optimizationMaximize);
        std::cout << "Run " << runIdx << ", finished liniar cooling";
        vector<double> bestSolutionGeometricCooling = simulatedAnneling(ackleyFunction, dimensionality, &geometricCooling, rangeOperator, numberOfIterationsForTemperature, kParam, continueCondition, optimizationMaximize);
        std::cout << ", geometric cooling";
        vector<double> bestSolutionLogarhitmicCooling = simulatedAnneling(ackleyFunction, dimensionality, &logarhitmicCooling, rangeOperator, numberOfIterationsForTemperature, kParam, continueCondition, optimizationMaximize);
        std::cout << ", logarhitmic cooling" << std::endl;
        linearCoolingResultsAccumulator += ackleyFunction(bestSolutionlinearCooling);
        geometricCoolingResultsAccumulator += ackleyFunction(bestSolutionGeometricCooling);
        logarhitmicCoolingResultsAccumulator += ackleyFunction(bestSolutionLogarhitmicCooling);
    }
    std::cout << "linear cooling results for: " << runsCount << ": " << linearCoolingResultsAccumulator / runsCount << std::endl;
    std::cout << "Geometric cooling results for: " << runsCount << ": " << geometricCoolingResultsAccumulator / runsCount << std::endl;
    std::cout << "Logarhitmic cooling results for: " << runsCount << ": " << logarhitmicCoolingResultsAccumulator / runsCount << std::endl;

}


