#include "print_utils.hpp"
#include <string>

std::pair<int, std::vector<std::string> > getMaxLengthAndStringVec(const Vector& vec)
{
    int maxLen = 0;
    std::vector<std::string> strVec = {};
    for(auto& e: vec)
    {
        std::string es = std::to_string(e);
        maxLen = (es.length() > maxLen) ? es.length() : maxLen;
        strVec.push_back(es);
    }
    return std::make_pair(maxLen, strVec);
}

std::string getPaddedString(std::string str, int maxLen, bool prePad=true)
{
    std::string padText = (maxLen > str.length()) ? std::string((maxLen - str.length()), ' ') : "";
    return prePad ? (padText + str) : (str + padText);
}

std::string getVectorText(const Vector& vec, std::string indent)
{
    std::string vecStr = indent;
    for(auto& e: vec)
    {
        vecStr += std::to_string(e) + " ";
    }
    return vecStr;
}

std::string getMatrixText(const Matrix& mat, std::string indent)
{
    std::string matStr = "";
    int maxLen = 0;
    std::vector<std::vector<std::string> > strMat = {};
    for(auto& vec: mat)
    {
        std::pair<int, std::vector<std::string> > maxLenAndStrVec = getMaxLengthAndStringVec(vec);
        maxLen = (maxLenAndStrVec.first > maxLen) ? maxLenAndStrVec.first : maxLen;
        strMat.push_back(maxLenAndStrVec.second);
    }
    for(auto& v: strMat)
    {
        std::string line = indent;
        for(auto& s: v)
        {
            line += getPaddedString(s, maxLen) + " ";
        }
        matStr += (line + "\n");
    }
    return matStr;
}