#ifndef SPARSE_VECTOR_HPP
#define SPARSE_VECTOR_HPP

#include <map>

class SparseVector
{
    std::map<size_t, double> m_data;
    size_t m_size;
    double m_defaultValue;
public:
    SparseVector(double defaultValue=0, size_t size=0);
    const double& operator[](size_t i) const;
    double& operator[](size_t i);
    size_t size() const;

    // Addition and subtraction methods
    SparseVector operator+(double c) const;
    SparseVector operator-(double c) const;

    // Multiplication methods
    SparseVector operator*(double c) const;

    const std::map<size_t, double>& getData() const;
};

#endif