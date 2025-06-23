#include "matrix.hpp"


Matrix::Matrix()
{
    m_data = {};
}

Matrix::Matrix(const std::vector<std::vector<double> >& data)
{
    m_data = data;
}