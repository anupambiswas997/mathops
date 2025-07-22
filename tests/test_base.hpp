#include "matrix.hpp"
#include "sparse_matrix.hpp"
#include "vectr.hpp"
#include "sparse_vector.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

struct TestParams
{
    std::string name;
    //std::string text;
    bool passed;
    TestParams(std::string tName, bool tPassed)//std::string tText, bool tPassed)
    {
        name = tName;
        //text = tText;
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
bool areEqual(const MatrixTypeA& ma, const MatrixTypeB& mb, size_t numRows, size_t numColumns, double tolerance)
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
bool areEqual(const VectorTypeA& va, const VectorTypeB& vb, size_t size, double tolerance)
{
    double maxDiff = getMaximumAbsDiff(va, vb, size);
    return (maxDiff <= tolerance);
}

Vector getVectorFromFile(std::string filepath)
{
    std::vector<double> r = {};
    std::ifstream f;
    f.open(filepath.c_str(), std::ios::in | std::ios::binary);
    size_t size;
    double value;
    f.read((char*)&size, sizeof(size_t));
    for(size_t i = 0; i < size; i++)
    {
        f.read((char*)&value, sizeof(double));
        r.push_back(value);
    }
    f.close();
    return Vector(r);
}

Matrix getMatrixFromFile(std::string filepath)
{
    std::vector<std::vector<double> > r = {};
    std::ifstream f;
    f.open(filepath.c_str(), std::ios::in | std::ios::binary);
    size_t numRows, numColumns;
    double value;
    f.read((char*)&numRows, sizeof(size_t));
    f.read((char*)&numColumns, sizeof(size_t));
    for(size_t i = 0; i < numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < numColumns; j++)
        {
            f.read((char*)&value, sizeof(double));
            r[i].push_back(value);
        }
    }
    f.close();
    return Matrix(r);
}

SparseVector getSparseVectorFromFile(std::string filepath)
{
    double value;
    size_t size, numElems, i;
    std::ifstream f;
    f.open(filepath.c_str(), std::ios::in | std::ios::binary);
    f.read((char*)&size, sizeof(size_t));
    f.read((char*)&value, sizeof(double));
    f.read((char*)&numElems, sizeof(size_t));
    SparseVector sv(value, size);
    for(size_t k = 0 ; k < numElems; k++)
    {
        f.read((char*)&i, sizeof(size_t));
        f.read((char*)&value, sizeof(double));
        sv[i] = value;
    }
    f.close();
    return sv;
}

SparseMatrix getSparseMatrixFromFile(std::string filepath)
{
    size_t numRows, numColumns, i, j, numElems;
    double value;
    std::ifstream f;
    f.open(filepath.c_str(), std::ios::in | std::ios::binary);
    f.read((char*)&numRows, sizeof(size_t));
    f.read((char*)&numColumns, sizeof(size_t));
    f.read((char*)&value, sizeof(double));
    SparseMatrix sm(value, numRows, numColumns);
    f.read((char*)&numElems, sizeof(size_t));
    for(size_t k = 0; k < numElems; k++)
    {
        f.read((char*)&i, sizeof(size_t));
        f.read((char*)&j, sizeof(size_t));
        f.read((char*)&value, sizeof(double));
        sm[i][j] = value;
    }
    f.close();
    return sm;
}