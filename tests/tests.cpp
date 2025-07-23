#include <iostream>
#include <vector>
#include "linear_algebra_tests.hpp"
//#include "calculus_tests.hpp" // in future

using namespace std;

void tabulateResults(const vector<TestParams>& testResults)
{
    // Determine the maximum length of all test-names so that a structured
    // tabulation can be created.
    size_t maxLen = 0;
    size_t numPassed = 0;
    for(const auto& tP: testResults)
    {
        maxLen = (tP.name.length() > maxLen) ? tP.name.length() : maxLen;
        numPassed += (tP.passed ? 1 : 0);
    }
    maxLen++;
    cout << endl << "TEST SUMMARY" << endl;
    for(const auto& tP: testResults)
    {
        string tName = tP.name + string(maxLen - tP.name.length(), ' ');
        string tPassed = tP.passed ? "PASS" : "FAIL";
        cout << "  " << tName << ": " << tPassed << endl;
    }
}

void testAll()
{
    vector<TestParams> testParamsList = {};
    performLinearAlgebraTests(testParamsList);
    //performCalculusTests(testParamsList);
    tabulateResults(testParamsList);
}

int main(int argc, char *argv[])
{
    testAll();
    return 0;
}