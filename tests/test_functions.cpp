#include <iostream>
#include "linear_algebra.hpp"
#include <iostream>

typedef std::vector<double> doubleVec;

void expect(bool condition, std::string testMsg)
{
    std::cout << testMsg << ": " << (condition ? "PASS" : "FAIL") << std::endl;
}

template <typename T>
std::string getDescAndVal(T val, std::string desc)
{
    return desc + " (" + std::to_string(val) + ")";
}

bool areEqual(int a, int b, std::string sa, std::string sb)
{
    std::string testMsg = getDescAndVal(a, sa) + " equals " + getDescAndVal(b, sb);
    bool condition = (a == b);
    expect(condition, testMsg);
    return condition;
}

bool areEqual(double a, double b, double tolerance, std::string sa, std::string sb)
{
    bool condition = (abs(a - b) <= tolerance);
    std::string testMsg = getDescAndVal(a, sa) + " equals " + getDescAndVal(b, sb) + getDescAndVal(tolerance, ", within tolerance");
    expect(condition, testMsg);
    return condition;
}

Matrix getMatrix(int numRows, int numColumns, const doubleVec& values)
{
    Matrix mat = {};
    int count = 0;
    for(int i = 0; i < numRows; i++)
    {
        mat.push_back({});
        for(int j = 0; j < numColumns; j++)
        {
            mat[i].push_back(values[count]);
            count++;
        }
    }
    return mat;
}

void count(bool testResult, int& passCount, int& testCount)
{
    passCount += int(testResult);
    testCount++;
}

void testMatrixTranspose(int numRows, int numColumns, const std::vector<double>& matVals, double tolerance)
{
    Matrix m = getMatrix(numRows, numColumns, matVals);
    Matrix mT = getTranspose(m);
    bool numRowsEqualsNumColumns = (mT.size() == numColumns);
    int passCount = 0;
    int testCount = 0;
    count(areEqual(mT.size(), numColumns, "transpose num-rows", "original num-columns"), passCount, testCount);
    for(int i = 0; i < numColumns; i++)
    {
        areEqual(mT[i].size(), numRows, "transpose row" + std::to_string(i) + "length", "original num-rows");
        for(int j = 0; j < numRows; j++)
        {
            std::string eij = "element (" + std::to_string(i) + ", " + std::to_string(j) + ")";
            std::string eji = "element (" + std::to_string(j) + ", " + std::to_string(i) + ")";
            count(areEqual(mT[i][j], m[j][i], tolerance, eij, eji), passCount, testCount);
        }
    }
    std::cout << "Matrix-transpose tests: pass = " << passCount << ", num-tests = " << testCount << std::endl;
}