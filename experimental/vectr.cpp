#include "vectr.hpp"
#include <cassert>
#include "matrix.hpp"

Vector::Vector()
{
    m_data = {};
}

Vector::Vector(const std::vector<double>& data)
{
    m_data = data;
}

double& Vector::operator[](size_t i)
{
    return m_data[i];
}

const double& Vector::operator[](size_t i) const
{
    return m_data[i];
}

Vector Vector::operator+(double c) const
{
    std::vector<double> r = {};
    for(const auto& x: m_data)
    {
        r.push_back(x + c);
    }
    return Vector(r);
}

Vector Vector::operator+(const Vector& v) const
{
    assert(m_data.size() == v.m_data.size());
    std::vector<double> r = {};
    for(size_t i = 0; i < m_data.size(); i++)
    {
        r.push_back(m_data[i] + v.m_data[i]);
    }
    return Vector(r);
}

Vector Vector::operator*(double c) const
{
    std::vector<double> r = {};
    for(const auto& x: m_data)
    {
        r.push_back(x * c);
    }
    return Vector(r);
}

double Vector::dot(const Vector& v) const
{
    assert(m_data.size() == v.m_data.size());
    double s = 0;
    for(size_t i = 0; i < m_data.size(); i++)
    {
        s += m_data[i] * v.m_data[i];
    }
    return s;
}

Vector Vector::operator*(const Matrix& m) const
{
    assert(m_data.size() == m.getData().size());
    std::vector<double> r = {};
    for(size_t j = 0; j < m.getData()[0].size(); j++)
    {
        double s = 0;
        for(size_t i = 0; i < m.getData().size(); i++)
        {
            s += m_data[i] * m.getData()[i][j];
        }
        r.push_back(s);
    }
    return Vector(r);
}