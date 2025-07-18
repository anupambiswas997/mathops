#include <iostream>
#include <cassert>
#include <cmath>
#include "linear_algebra.hpp"
#include "random_quantities.hpp"
#include "print_utils.hpp"
#include "calculus.hpp"

using namespace std;

#define EXPECT(a, testMsg) cout << "\t" << testMsg << " - " << ((a) ? "PASS" : "FAIL") << endl;

void testRandomNumber()
{
    string text;

    double r = getRandom();
    text = "Value " + to_string(r) + " within [0, 1]";
    EXPECT((r >= 0) && (r <= 1), text);

    double start = 33;
    double end = 49;
    r = getRandom(start, end);
    text = "Value " + to_string(r) + " within [" + to_string(start) + ", " + to_string(end) + "]";
    EXPECT((r >= start) && (r <= end), text);

    int nrows = 3;
    int ncols = 5;
    double sval = 22;
    double eval = 37;
    Matrix m = getRandomMatrix(nrows, ncols, sval, eval);
    for(int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++)
        {
            text = "Matrix element at (" + to_string(i) + ", " + to_string(j) + ") -> " + to_string(m[i][j]) + " within [" + to_string(sval) +", " + to_string(eval) + "]";
            EXPECT((m[i][j] >= sval) && (m[i][j] <= eval), text);
        }
    }
    cout << "Random number tests passed" << endl;
}

void testPrint()
{
    Vector vec = getRandomVector(5, 0, 3);
    cout << "A vector of size 5 with elements in range [0, 3] should be printed below:" << endl;
    cout << getVectorText(vec) << endl;
    Matrix mat = getRandomMatrix(3, 4, -3, 3);
    cout << endl << "A matrix of dimensions (3, 4) with elements in range [-3, 3] should be printed below:" << endl;
    cout << getMatrixText(mat) << endl;
    Matrix ide = getIdentityMatrix(5);
    cout << endl << "An identity matrix of dimensions (5, 5) should be printed below:" << endl;
    cout << getMatrixText(ide) << endl;
    Matrix mat2 = getRandomMatrix(3, 3, -5, 5);
    Matrix mat3 = getMatrixInverse(mat2, true);
    Matrix mat4 = getProductOfMatrices(mat2, mat3);
    cout << "Matrix mat2:" << endl << getMatrixText(mat2, "   ") << endl;
    cout << "Matrix mat3:" << endl << getMatrixText(mat3, "   ") << endl;
    cout << "Matrix mat4:" << endl << getMatrixText(mat4, "   ") << endl;
}

void testCalculus()
{
    double pi = 4 * atan(1);
    double (*func)(double) = &sin;
    double sin0ToPiIntegComputed = getIntegratedValue(&sin, 0, pi, 100);
    double sin0ToPiIntegFormula = -cos(pi) + cos(0);
    cout << "Integration of sin(x) from 0 to pi:" << endl;
    cout << "Formula: " << sin0ToPiIntegFormula << ", computed: " << sin0ToPiIntegComputed << endl << endl;
    cout << "Integration of ln(x) from 1 to e:" << endl;
    cout << "Formula: 1, computed: " << getIntegratedValue(&log, 1, exp(1)) << endl << endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testRandomNumber();
    testPrint();
    testCalculus();
    return 0;
}