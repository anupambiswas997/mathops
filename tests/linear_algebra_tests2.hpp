#include "test_base.hpp"
#include <vector>

using namespace std;

void doTest(double expected, double computed, string testName, vector<TestParams>& tpList)
{
    bool passed = areEqual(computed, expected);
    cout << "TEST: " << testName << endl;
    cout << "    computed: " << computed << endl;
    cout << "    expected: " << expected << endl;
    tpList.push_back(TestParams(testName, passed));
    cout << "    passed: " << passed << endl;
}

void performLinearAlgebraTests2(vector<TestParams>& testParamsList)
{
    Vector v = vector<double>{3, -4.5, 7, -6.2, 8.1, 1.5}; // sum 8.9 min -6.2 max 8.1
    doTest(8.9, v.getSum(), "Vector sum", testParamsList);
    doTest(-6.2, v.getMin(), "Vector min", testParamsList);
    doTest(8.1, v.getMax(), "Vector max", testParamsList);
    SparseVector sv(0, 25);
    sv[2] = 3;
    sv[5] = -4.5;
    sv[8] = 7;
    sv[12] = -6.2;
    sv[14] = 8.1;
    sv[18] = 1.5;
    doTest(8.9, sv.getSum(), "SparseVector sum", testParamsList);
    doTest(-6.2, sv.getMin(), "SparseVector min", testParamsList);
    doTest(8.1, sv.getMax(), "SparseVector max", testParamsList);
}