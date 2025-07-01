#ifndef RANDOM_QUANTITIES_HPP
#define RANDOM_QUANTITIES_HPP

#include <cstddef>

class Matrix;
class Vector;

double getRandom(double start=0, double end=1);
Matrix getRandomMatrix(size_t numRows, size_t numColumns, double start=0, double end=1);
Vector getRandomVector(size_t vectorSize, double start=0, double end=1);

#endif