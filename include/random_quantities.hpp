#ifndef RANDOM_QUANTITIES_HPP
#define RANDOM_QUANTITIES_HPP

#include "common_types.hpp"

double getRandom(double start=0, double end=1);
Matrix getRandomMatrix(int numRows, int numColums, double start=0, double end=1);
Vector getRandomVector(int vectorSize, double start=0, double end=1);

#endif