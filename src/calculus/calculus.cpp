#include "calculus.hpp"
#include <cassert>
#include <iostream>

double getIntegratedValue(double (*func)(double), double start, double end, int n, double frac)
{
    assert((frac >= 0) && (frac <= 1));
    double dx = (end - start) / n;
    double sum = 0;
    double x = start + frac * dx; // frac is generally 0, 0.5 or 1 (0.5 provides better approximation)
    for(int i = 0; i < n; i++)
    {
        sum += func(x);
        x += dx;
    }
    return sum * dx;
}

double getDifferentiatedValue(double (*func)(double), double x, double dx, int mode)
{
    double fxForward, fxBackward;
    switch(mode)
    {
        case DifferentialEnum::BACKWARD:
        fxForward = func(x);
        fxBackward = func(x - dx);
        break;

        case DifferentialEnum::FORWARD:
        fxForward = func(x + dx);
        fxBackward = func(x);
        break;

        case DifferentialEnum::CENTRAL:
        fxForward = func(x + 0.5 * dx);
        fxBackward = func(x - 0.5 * dx);
        break;

        default:
        std::cout << "Invalid mode for differentiation. Allowed: 0 for backward, 1 for forward and 2 for central differentiation." << std::endl;
        assert(false);
        break;
    }
    return (fxForward - fxBackward) / dx;
}