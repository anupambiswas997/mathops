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