#include "matrix.hpp"
#include "vectr.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>

bool Matrix::isDataValid() const
{
    // Empty data denotes a null matrix, which is valid.
    if(m_data.size() == 0)
    {
        return true;
    }
    bool first = true;
    size_t lastSize = 0;
    for(const auto& cur: m_data)
    {
        // If the first row is found to be of length 0, it is not a valid matrix, as
        // a matrix cannot have a non-zero number of rows and 0 columns at the same time.
        // Because there is a second check in which the current row's length is compared
        // with the previous row's length, the zero-length check can be done just once
        // at the beginning - that's sufficient.
        if(first && (cur.size() == 0))
        {
            std::cout << "Matrix has row with 0 length!" << std::endl;
            return false;
        }
        if(!first && (lastSize != cur.size()))
        {
            std::cout << "Matrix has rows with unequal length!" << std::endl;
            return false;
        }
        lastSize = cur.size();
        first = false;
    }
    return true;
}

Matrix::Matrix()
{
    m_data = {};
    // At this point, the matrix is a null-matrix, hence it has 0 dimensions.
    m_numRows = 0;
    m_numColumns = 0;
}

Matrix::Matrix(const std::vector<std::vector<double> >& data)
{
    m_data = data;
    assert(isDataValid());
    m_numRows = m_data.size();
    m_numColumns = m_data[0].size();
}

std::vector<double>& Matrix::operator[](size_t i)
{
    return m_data[i];
}

const std::vector<double>& Matrix::operator[](size_t i) const
{
    return m_data[i];
}

Matrix Matrix::operator+(double c) const
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            r[i].push_back(m_data[i][j] + c);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator+(const Matrix& m) const
{
    assert(m_numRows == m.m_numRows);
    assert(m_numColumns == m.m_numColumns);
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            r[i].push_back(m_data[i][j] + m.m_data[i][j]);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator*(double c) const
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            r[i].push_back(m_data[i][j] * c);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator*(const std::vector<std::vector<double> >& d) const
{
    bool bothMatricesNull = (m_data.size() == 0) && (d.size() == 0);
    bool bothMatricesNotNull = (m_data.size() != 0) && (d.size() != 0);
    assert(bothMatricesNull || bothMatricesNotNull);
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        assert(m_numColumns == d.size());
        r.push_back({});
        for(size_t j = 0; j < d[0].size(); j++)
        {
            double s = 0;
            for(size_t k = 0; k < m_numColumns; k++)
            {
                s += m_data[i][k] * d[k][j];
            }
            r[i].push_back(s);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator*(const Matrix& m) const
{
    return (*this) * m.m_data;
}

Vector Matrix::operator*(const std::vector<double>& d) const
{
    std::vector<double> r = {};
    for(size_t i = 0; i < m_numRows; i++)
    {
        assert(m_numColumns == d.size());
        double sum = 0;
        for(size_t j = 0; j < m_numColumns; j++)
        {
            sum += m_data[i][j] * d[j];
        }
        r.push_back(sum);
    }
    return Vector(r);
}

Vector Matrix::operator*(const Vector& v) const
{
    return (*this) * v.getData();
}

const std::vector<std::vector<double> >& Matrix::getData() const
{
    return m_data;
}

Matrix Matrix::getInverse() const
{
    // Inverse is only possible for a square matrix.
    assert(m_numRows == m_numColumns);
    // It is required to make a copy of the matrix data because row transformations
    // will be done.
    std::vector<std::vector<double> > data = m_data;
    std::vector<std::vector<double> > inv = {};
    // Initialize the matrix as an identity matrix.
    for(size_t i = 0; i < m_numRows; i++)
    {
        inv.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            inv[i].push_back((i == j) ? 1 : 0);
        }
    }
    for(size_t i = 0; i < m_numRows; i++)
    {
        // First, check if the pivot element (i, i) is 0. If so, find
        // a row i2, such that, element(i2, i) is non-zero. Then swap the rows
        // i and i2.
        // In future, the following check may be replaced by a check for a very
        // small number, as it is unlikely that a floating point value will have
        // the exact bit representation of 0, when it is practically so.
        if(data[i][i] == 0)
        {
            bool nonZeroPivotFound = false;
            size_t i2;
            for(i2 = (i + 1); i2 < m_numRows; i2++)
            {
                if(data[i2][i] != 0)
                {
                    nonZeroPivotFound = true;
                    break;
                }
            }
            assert(nonZeroPivotFound);
            // Perform the row-swap. It is not required to do the swapping of values
            // which are for columns smaller than i, as they are 0 for both rows.
            for(size_t j = i; j < m_numColumns; j++)
            {
                std::swap(data[i][j], data[i2][j]);
            }
            for(size_t j = 0; j < m_numColumns; j++)
            {
                std::swap(inv[i][j], inv[i2][j]);
            }
        }
        // At this point, the pivot element(i, i) is non-zero. Divide the row
        // with this pivot element for the data matrix and the inverse matrix.
        double pivot = data[i][i];
        for(size_t j = i; j < m_numColumns; j++)
        {
            data[i][j] /= pivot;
        }
        for(size_t j = 0; j < m_numColumns; j++)
        {
            inv[i][j] /= pivot;
        }
        // Apply row transformation to both data and inverse matrices, such that all
        // non-diagonal terms below the pivot element is 0 in the data matrix.
        for(size_t i2 = (i + 1); i2 < m_numRows; i2++)
        {
            double factor = data[i2][i];
            for(size_t j = i; j < m_numColumns; j++)
            {
                data[i2][j] = data[i2][j] - factor * data[i][j];
            }
            for(size_t j = 0; j < m_numColumns; j++)
            {
                inv[i2][j] = inv[i2][j] - factor * inv[i][j];
            }
        }
    }
    // Now, the data matrix is upper triangular, because the diagonal terms are
    // all 1, and all elements below the diagonal are 0. The next steps will change the
    // data matrix to an identity matrix, and the exact same steps will be applied to the
    // inverse matrix.
    for(size_t i = (m_numRows - 1); i > 0; i--)
    {
        for(size_t i2 = (i - 1); ; i2--)
        {
            double factor = data[i2][i];
            /*
            for(size_t j = i; j >= i2; j--)
            {
                data[i2][j] = data[i2][j] - factor * data[i][j];
            }//*/
            // The above for-loop is unnecessary. It can be replaced simply
            // by the following.
            data[i2][i] = 0;
            for(size_t j = 0; j < m_numColumns; j++)
            {
                inv[i2][j] = inv[i2][j] - factor * inv[i][j];
            }
            if(i2 == 0)
            {
                break;
            }
        }
    }
    return Matrix(inv);
}

Matrix Matrix::getTranspose() const
{
    std::vector<std::vector<double> > r = {};
    for(size_t j = 0; j < m_numColumns; j++)
    {
        r.push_back({});
        for(size_t i = 0; i < m_numRows; i++)
        {
            r[j].push_back(m_data[i][j]);
        }
    }
    return Matrix(r);
}

double Matrix::t(size_t i, size_t j) const
{
    return m_data[j][i];
}

size_t Matrix::getNumRows() const
{
    return m_numRows;
}

size_t Matrix::getNumColumns() const
{
    return m_numColumns;
}

std::string Matrix::getText() const
{
    size_t maxLen = 0;
    std::vector<std::vector<std::string> > matStr = {};
    // Determine the maximum length of an element's string representation.
    for(size_t i = 0; i < m_numRows; i++)
    {
        matStr.push_back({});
        for(size_t j = 0; j < m_numColumns; j++)
        {
            std::string elemStr = std::to_string(m_data[i][j]);
            matStr[i].push_back(elemStr);
            maxLen = (maxLen < elemStr.length()) ? elemStr.length() : maxLen;
        }
    }
    std::string matText = "";
    for(size_t i = 0; i < m_numRows; i++)
    {
        for(size_t j = 0; j < m_numColumns; j++)
        {
            size_t lenDiff = maxLen - matStr[i][j].length();
            std::string paddedElemStr = matStr[i][j] + ((lenDiff > 0) ? std::string(lenDiff, ' ') : "");
            matText += (paddedElemStr + " ");
        }
        matText += "\n";
    }
    return matText;
}