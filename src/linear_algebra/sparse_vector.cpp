#include "sparse_vector.hpp"
#include <cassert>
#include "vectr.hpp"
#include "templates_linalg.hpp"

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

Vector SparseVector::operator+(const Vector& v) const
{
    assert(m_data.size() == v.size());
    return getVectorSum((*this), v.getData(), m_data.size());
}

Vector SparseVector::operator-(const Vector& v) const
{
    assert(m_data.size() == v.size());
    return getVectorDiff((*this), v.getData(), m_data.size());
}

SparseVector SparseVector::operator+(const SparseVector& sv) const
{
    assert(m_data.size() == sv.m_data.size());
    SparseVector r(m_defaultValue + sv.m_defaultValue, m_data.size());
    for(const auto& e: m_data)
    {
        size_t i = e.first;
        r[i] = e.second + sv[i];
    }
    for(const auto& e: sv.m_data)
    {
        size_t i = e.first;
        r[i] = (*this)[i] + sv[i];
    }
    return r;
}

SparseVector SparseVector::operator-(const SparseVector& sv) const
{
    assert(m_data.size() == sv.m_data.size());
    SparseVector r(m_defaultValue + sv.m_defaultValue, m_data.size());
    for(const auto& e: m_data)
    {
        size_t i = e.first;
        r[i] = e.second - sv[i];
    }
    for(const auto& e: sv.m_data)
    {
        size_t i = e.first;
        r[i] = (*this)[i] - sv[i];
    }
    return r;
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

const std::map<size_t, double>& SparseVector::getData() const
{
    return m_data;
}