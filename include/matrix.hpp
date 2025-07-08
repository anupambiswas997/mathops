#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

class Vector;

class Matrix
{
    std::vector<std::vector<double> > m_data;
    size_t m_numRows;
    size_t m_numColumns;
    bool isDataValid() const;
public:
    Matrix();
    Matrix(const std::vector<std::vector<double> >& data);
    std::vector<double>& operator[](size_t i);
    const std::vector<double>& operator[](size_t i) const;
    Matrix operator+(double c) const;
    Matrix operator-(double c) const;
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(double c) const;
    Matrix operator*(const std::vector<std::vector<double> >& d) const;
    Matrix operator*(const Matrix& m) const;
    Vector operator*(const std::vector<double>& d) const;
    Vector operator*(const Vector& v) const;
    const std::vector<std::vector<double> >& getData() const;
    Matrix getInverse() const;
    // getTranspose() creates a completely new Matrix, whereas
    // T(i, j) can be used read an element from its transpose directly
    Matrix getTranspose() const;
    double t(size_t i, size_t j) const;
    size_t getNumRows() const;
    size_t getNumColumns() const;
    std::string getText() const;
};

#endif