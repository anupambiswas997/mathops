#include "vectr.hpp"

Vector::Vector()
{
    m_data = {};
}

Vector::Vector(const std::vector<double>& data)
{
    m_data = data;
}