// KGRyko_lab_2_MEH.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "ICoolingFunction.h"
#include "GeometricCoolingFunction.h"
#define twoPi 3.14159265358979323846
#define ePlus20 22.71828182845904523536

using namespace std;

double ackleyFunction( std::vector<double> x )
{
    double oneByDimensionality = 1.0 / static_cast<double>(x.size());
    double sum1 = 0.0;
    double sum2 = 0.0;
    auto actionSum = [&sum1, &sum2](const double& x) { sum1 += (x * x); sum2 += cos(twoPi * x); };
    std::for_each(x.begin(), x.end(), actionSum);
    return ePlus20 - 20.0 * exp(-0.2 * sqrt(oneByDimensionality) * sum1) - exp(oneByDimensionality * sum2);
}



vector<double> simulatedAnneling(vector<double> startPoint, ICoolingFunction* coolingFunction )
{


}

int main()
{
    std::cout << "Hello World!\n";
}


