#include <iostream>
#include "linear_algebra.hpp"
#include "random_quantities.hpp"
#include "print_utils.hpp"
#include <cassert>

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
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testRandomNumber();
    testPrint();
    return 0;
}