#include "matrix.hpp"
#include "vectr.hpp"
#include <cassert>
#include <iostream>

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
}

Matrix::Matrix(const std::vector<std::vector<double> >& data)
{
    m_data = data;
    assert(isDataValid());
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
    for(size_t i = 0; i < m_data.size(); i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_data[i].size(); j++)
        {
            r[i].push_back(m_data[i][j] + c);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator+(const Matrix& m) const
{
    assert(m_data.size() == m.m_data.size());
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_data.size(); i++)
    {
        r.push_back({});
        assert(m_data[i].size() == m.m_data[i].size());
        for(size_t j = 0; j < m_data[i].size(); j++)
        {
            r[i].push_back(m_data[i][j] + m.m_data[i][j]);
        }
    }
    return Matrix(r);
}

Matrix Matrix::operator*(double c) const
{
    std::vector<std::vector<double> > r = {};
    for(size_t i = 0; i < m_data.size(); i++)
    {
        r.push_back({});
        for(size_t j = 0; j < m_data[i].size(); j++)
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
    for(size_t i = 0; i < m_data.size(); i++)
    {
        assert(m_data[i].size() == d.size());
        r.push_back({});
        for(size_t j = 0; j < d[0].size(); j++)
        {
            double s = 0;
            for(size_t k = 0; k < m_data[i].size(); k++)
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
    for(size_t i = 0; i < m_data.size(); i++)
    {
        assert(m_data[i].size() == d.size());
        double sum = 0;
        for(size_t j = 0; j < m_data[i].size(); j++)
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
    std::vector<std::vector<double> > inv = {};
    std::cout << "Matrix::getInverse() not yet implemented" << std::endl;
    return Matrix(inv);
}

Matrix Matrix::getTranspose() const
{
    std::vector<std::vector<double> > r = {};
    for(size_t j = 0; j < m_data[0].size(); j++)
    {
        r.push_back({});
        for(size_t i = 0; i < m_data.size(); i++)
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