#include "vectr.hpp"
#include <cassert>
#include "matrix.hpp"
#include "templates_linalg.hpp"
#include "sparse_vector.hpp"

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

Vector Vector::operator-(double c) const
{
    double negativeC = -c;
    return (*this) + negativeC;
}

Vector Vector::operator+(const Vector& v) const
{
    assert(m_data.size() == v.m_data.size());
    return getVectorSum((*this), v.m_data, m_data.size());
}

Vector Vector::operator-(const Vector& v) const
{
    assert(m_data.size() == v.m_data.size());
    return getVectorDiff((*this), v.m_data, m_data.size());
}

Vector Vector::operator+(const SparseVector& sv) const
{
    assert(m_data.size() == sv.size());
    return getVectorSum(m_data, sv, m_data.size());
}

Vector Vector::operator-(const SparseVector& sv) const
{
    assert(m_data.size() == sv.size());
    return getVectorDiff(m_data, sv, m_data.size());
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
    return getDotProduct(m_data, v.m_data, m_data.size());
}

Vector Vector::operator*(const Matrix& m) const
{
    assert(m_data.size() == m.getData().size());
    return getVectorMatrixProduct(m_data, m.getData(), m.getNumRows(), m.getNumColumns());
}

const std::vector<double>& Vector::getData() const
{
    return m_data;
}

std::string Vector::getText() const
{
    return getVectorText(m_data, m_data.size());
}

size_t Vector::size() const
{
    return m_data.size();
}