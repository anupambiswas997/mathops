#include "random_quantities.hpp"
#include "matrix.hpp"
#include "vectr.hpp"
#include <cstdlib>

double getRandom(double start, double end)
{
    double diff = (end - start);
    double frac = rand() / (double)RAND_MAX;
    return start + diff * frac;
}

Matrix getRandomMatrix(size_t numRows, size_t numColumns, double start, double end)
{
    std::vector<std::vector<double> > data = {};
    for(size_t i = 0; i < numRows; i++)
    {
        data.push_back({});
        for(size_t j = 0; j < numColumns; j++)
        {
            data[i].push_back(getRandom(start, end));
        }
    }
    return Matrix(data);
}

Vector getRandomVector(size_t vectorSize, double start, double end)
{
    std::vector<double> data = {};
    for(size_t i = 0; i < vectorSize; i++)
    {
        data.push_back(getRandom(start, end));
    }
    return Vector(data);
}