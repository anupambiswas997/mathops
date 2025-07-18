#include <iostream>
#include "matrix.hpp"
#include "random_quantities.hpp"

using namespace std;

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
    cout << "Matrix to invert:" << endl << m.getText() << endl << endl;
    cout << "Matrix inverse:" << endl << mInv.getText() << endl << endl;
    cout << "Expecting identity matrix as product of the above two matrices:" << endl << p.getText() << endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testMatrixInverse();
    return 0;
}