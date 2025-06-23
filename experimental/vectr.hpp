#ifndef VECTR_HPP
#define VECTR_HPP

#include <vector>

class Vector
{
    std::vector<double> m_data;
public:
    Vector();
    Vector(const std::vector<double>& data);
};

#endif