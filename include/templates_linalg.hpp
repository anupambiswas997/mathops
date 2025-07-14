#ifndef TEMPLATES_LINALG_HPP
#define TEMPLATES_LINALG_HPP

#include <vector>

template <typename VectorLikeA, typename VectorLikeB>
std::vector<double> getVectorSum(const VectorLikeA& va, const VectorLikeB& vb, size_t size)
{
    std::vector<double> r = {};
    for(size_t i = 0; i < size; i++)
    {
        r.push_back(va[i] + vb[i]);
    }
    return r;
}

template <typename VectorLikeA, typename VectorLikeB>
std::vector<double> getVectorDiff(const VectorLikeA& va, const VectorLikeB& vb, size_t size)
{
    std::vector<double> r = {};
    for(size_t i = 0; i < size; i++)
    {
        r.push_back(va[i] - vb[i]);
    }
    return r;
}

template <typename MatrixLikeA, typename MatrixLikeB>
std::vector<std::vector<double> > getMatrixSum(const MatrixLikeA& ma, const MatrixLikeB& mb, size_t numRows, size_t numColumns)
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < numColumns; j++)
        {
            r[i].push_back(ma[i][j] + mb[i][j]);
        }
    }
    return r;
}

template <typename MatrixLikeA, typename MatrixLikeB>
std::vector<std::vector<double> > getMatrixDiff(const MatrixLikeA& ma, const MatrixLikeB& mb, size_t numRows, size_t numColumns)
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < numColumns; j++)
        {
            r[i].push_back(ma[i][j] - mb[i][j]);
        }
    }
    return r;
}

template <typename MatrixLikeA, typename MatrixLikeB>
std::vector<std::vector<double> > getMatrixMatrixProduct(const MatrixLikeA& ma, const MatrixLikeB& mb, size_t numRowsA, size_t numColumnsA, size_t numColumnsB)
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < numRowsA; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < numColumnsB; j++)
        {
            double sum = 0;
            for(size_t k = 0; k < numColumnsA; k++)
            {
                sum += (ma[i][k] * mb[k][j]);
            }
            r[i].push_back(sum);
        }
    }
    return r;
}

template <typename MatrixLike, typename VectorLike>
std::vector<double> getMatrixVectorProduct(const MatrixLike& m, const VectorLike& v, size_t numRows, size_t numColumns)
{
    std::vector<double> r = {};
    for(size_t i = 0; i < numRows; i++)
    {
        double sum = 0;
        for(size_t j = 0; j < numColumns; j++)
        {
            sum += (m[i][j] * v[j]);
        }
        r.push_back(sum);
    }
    return r;
}

template <typename VectorLike, typename MatrixLike>
std::vector<double> getVectorMatrixProduct(const VectorLike& v, const MatrixLike& m, size_t numRows, size_t numColumns)
{
    std::vector<double> r = {};
    for(size_t j = 0; j < numColumns; j++)
    {
        double sum = 0;
        for(size_t k = 0; k < numRows; k++)
        {
            sum += (v[k] * m[k][j]);
        }
        r.push_back(sum);
    }
    return r;
}

template <typename MatrixLike>
std::string getMatrixText(const MatrixLike& m, size_t numRows, size_t numColumns)
{
    size_t maxLen = 0;
    std::vector<std::vector<std::string> > matStr = {};
    // Determine the maximum length of an element's string representation.
    for(size_t i = 0; i < numRows; i++)
    {
        matStr.push_back({});
        for(size_t j = 0; j < numColumns; j++)
        {
            std::string elemStr = std::to_string(m[i][j]);
            matStr[i].push_back(elemStr);
            maxLen = (maxLen < elemStr.length()) ? elemStr.length() : maxLen;
        }
    }
    std::string matText = "";
    for(size_t i = 0; i < numRows; i++)
    {
        for(size_t j = 0; j < numColumns; j++)
        {
            size_t lenDiff = maxLen - matStr[i][j].length();
            std::string paddedElemStr = matStr[i][j] + ((lenDiff > 0) ? std::string(lenDiff, ' ') : "");
            matText += (paddedElemStr + " ");
        }
        matText += "\n";
    }
    return matText;
}

template <typename VectorLikeA, typename VectorLikeB>
double getDotProduct(const VectorLikeA& va, const VectorLikeB& vb, size_t n)
{
    double sum = 0;
    for(size_t i = 0; i < n; i++)
    {
        sum += (va[i] * vb[i]);
    }
    return sum;
}

template <typename VectorLike>
std::string getVectorText(const VectorLike& v, size_t n)
{
    size_t maxLen = 0;
    std::vector<std::string> vecStr = {};
    for(size_t i = 0; i < n; i++)
    {
        std::string elemStr = std::to_string(v[i]);
        maxLen = (maxLen < elemStr.length()) ? elemStr.length() : maxLen;
        vecStr.push_back(elemStr);
    }
    std::string vecText = "";
    for(size_t i = 0; i < n; i++)
    {
        size_t lenDiff = maxLen - vecStr[i].length();
        std::string paddedElemStr = vecStr[i] + ((lenDiff > 0) ? std::string(lenDiff, ' ') : "");
        vecText += (paddedElemStr + " ");
    }
    return vecText;
}

#endif