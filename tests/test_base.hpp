#include "matrix.hpp"
#include "sparse_matrix.hpp"
#include "vectr.hpp"
#include "sparse_vector.hpp"

struct TestParams
{
    std::string name;
    bool passed;
    TestParams(std::string tName, bool tPassed)
    {
        name = tName;
        passed = tPassed;
    }
};

template <typename MatrixTypeA, typename MatrixTypeB>
double getMaximumAbsDiff(const MatrixTypeA& ma, const MatrixTypeB& mb, size_t numRows, size_t numColumns)
{
    double maxDiff = 0;
    for(size_t i = 0; i < numRows; i++)
    {
        for(size_t j = 0; j < numColumns; j++)
        {
            double curDiff = abs(ma[i][j] - mb[i][j]);
            maxDiff = (curDiff > maxDiff) ? curDiff : maxDiff;
        }
    }
    return maxDiff;
}

template <typename MatrixTypeA, typename MatrixTypeB>
bool equals(const MatrixTypeA& ma, const MatrixTypeB& mb, size_t numRows, size_t numColumns, double tolerance)
{
    double maxDiff = getMaximumAbsDiff(ma, mb, numRows, numColumns);
    return (maxDiff <= tolerance);
}

template <typename VectorTypeA, typename VectorTypeB>
double getMaximumAbsDiff(const VectorTypeA& va, const VectorTypeB& vb, size_t size)
{
    double maxDiff = 0;
    for(size_t i = 0; i < size; i++)
    {
        double curDiff = abs(va[i] - vb[i]);
        maxDiff = (curDiff > maxDiff) ? curDiff : maxDiff;
    }
    return maxDiff;
}

template <typename VectorTypeA, typename VectorTypeB>
bool equals(const VectrorTypeA& va, const VectorTypeB& vb, size_t size, double tolerance)
{
    double maxDiff = getMaximumAbsDiff(va, vb, size);
    return (maxDiff <= tolerance);
}