#include "sparse_vector.hpp"
#include <cassert>

SparseVector::SparseVector(double defaultValue, size_t size)
{
    m_defaultValue = defaultValue;
    m_size = size;
}

const double& SparseVector::operator[](size_t i) const
{
    assert(i < m_size);
    return (m_data.count(i) > 0) ? m_data.at(i) : m_defaultValue;
}

double& SparseVector::operator[](size_t i)
{
    m_size = (i < m_size) ? m_size : (i + 1);
    return m_data[i];
}

size_t SparseVector::size() const
{
    return m_size;
}

SparseVector SparseVector::operator+(double c) const
{
    SparseVector r(m_defaultValue + c, size());
    for(const auto& e: m_data)
    {
        r[e.first] = e.second + c;
    }
    return r;
}

SparseVector SparseVector::operator-(double c) const
{
    double negativeC = -c;
    return (*this) + negativeC;
}

SparseVector SparseVector::operator*(double c) const
{
    SparseVector r(m_defaultValue * c, size());
    for(const auto& e: m_data)
    {
        r[e.first] = c * e.second;
    }
    return r;
}