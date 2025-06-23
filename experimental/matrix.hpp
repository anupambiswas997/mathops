#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix
{
    std::vector<std::vector<double> > m_data;
public:
    Matrix();
    Matrix(const std::vector<std::vector<double> >& data);
};

#endif