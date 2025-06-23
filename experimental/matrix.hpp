#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix
{
    std::vector<std::vector<double> > m_data;
public:
    Matrix();
    Matrix(const std::vector<std::vector<double> >& data);
    std::vector<double>& operator[](size_t i);
    const std::vector<double>& operator[](size_t i) const;
    Matrix operator+(double c) const;
    Matrix operator+(const Matrix& m) const;
};

#endif