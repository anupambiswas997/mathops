#ifndef CALCULUS_HPP
#define CALCULUS_HPP

double getIntegratedValue(double (*func)(double), double start, double end, int n=1000, double frac=0.5); 

enum DifferentialEnum {BACKWARD, FORWARD, CENTRAL};
double getDifferentiatedValue(double (*func)(double), double x, double dx, int mode=DifferentialEnum::CENTRAL);

#endif