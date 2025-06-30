#include "random_quantities.hpp"
#include <cstdlib>

double getRandom(double start, double end)
{
    double diff = (end - start);
    double frac = rand() / (double)RAND_MAX;
    return start + diff * frac;
}

Matrix getRandomMatrix(int numRows, int numColums, double start, double end)
{
    Matrix mat = {};
    for(int i = 0; i < numRows; i++)
    {
        mat.push_back(getRandomVector(numColums, start, end));
    }
    return mat;
}

Vector getRandomVector(int vectorSize, double start, double end)
{
    Vector vec = {};
    for(int i = 0; i < vectorSize; i++)
    {
        vec.push_back(getRandom(start, end));
    }
    return vec;
}