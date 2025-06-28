#include <iostream>
#include "matrix.hpp"

using namespace std;

Matrix getRandomMatrix(size_t nrows, size_t ncols, double start=0, double end=1)
{
    double diff = end - start;
    vector<vector<double> > r = {};
    for(size_t i = 0; i < nrows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < ncols; j++)
        {
            double randomValue = rand() / (RAND_MAX * 1.0);
            r[i].push_back(start + randomValue * diff);
        }
    }
    return Matrix(r);
}

void showMatrix(const Matrix& m, string indent="   ")
{
    vector<vector<string> > mS = {};
    size_t maxLen = 0;
    for(size_t i = 0; i < m.getNumRows(); i++)
    {
        mS.push_back({});
        for(size_t j = 0; j < m.getNumColumns(); j++)
        {
            string s = to_string(m[i][j]);
            maxLen = (maxLen < s.length()) ? s.length() : maxLen;
            mS[i].push_back(s);
        }
    }
    for(size_t i = 0; i < m.getNumRows(); i++)
    {
        cout << indent;
        for(size_t j = 0; j < m.getNumColumns(); j++)
        {
            size_t lenDiff = maxLen - mS[i][j].length();
            string s = (lenDiff > 0) ? string(lenDiff, ' ') : "";
            cout << s << mS[i][j] << " ";
        }
        cout << endl;
    }
}

void testMatrixInverse()
{
    std::cout << "Testing matrix inverse" << std::endl;
    Matrix m = getRandomMatrix(3, 3, 0.0, 1.0);
    Matrix mInv = m.getInverse();
    Matrix p = m * mInv;
    cout << "Matrix to invert:" << endl;
    showMatrix(m);
    cout << endl << "Matrix inverse:" << endl;
    showMatrix(mInv);
    cout << endl << "Expecting identity matrix as product of the above two matrices:" << endl;
    showMatrix(p);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testMatrixInverse();
    return 0;
}