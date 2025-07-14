#ifndef VECTR_HPP
#define VECTR_HPP

#include <vector>
#include <string>

class Matrix;
class SparseVector;

class Vector
{
    std::vector<double> m_data;
public:
    Vector();
    Vector(const std::vector<double>& data);
    double& operator[](size_t i);
    const double& operator[](size_t i) const;

    // Addition and subtraction methods
    Vector operator+(double c) const;
    Vector operator-(double c) const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator+(const SparseVector& sv) const;
    Vector operator-(const SparseVector& sv) const;

    // Multiplication methods
    Vector operator*(double c) const;
    double dot(const Vector& v) const;
    // intended use for the following multiplication with Matrix object:
    // as a row-vector being multiplied with a matrix
    Vector operator*(const Matrix& m) const;

    const std::vector<double>& getData() const;
    std::string getText() const;
    size_t size() const;
};

#endif