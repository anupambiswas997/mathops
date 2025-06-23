#include "matrix.hpp"
#include <cassert>

Matrix::Matrix()
{
    m_data = {};
}

Matrix::Matrix(const std::vector<std::vector<double> >& data)
{
    m_data = data;
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