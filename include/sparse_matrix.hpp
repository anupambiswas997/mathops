#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <map>
#include <vector>
#include "sparse_vector.hpp"
#include <string>

class Matrix;
class Vector;

class SparseMatrix
{
    std::map<size_t, SparseVector> m_data;
    double m_defaultValue;
    size_t m_numRows;
    size_t m_numColumns;
    const SparseVector m_defaultRowVector;
public:
    SparseMatrix(double defaultValue=0, size_t numRows=0, size_t numColumns=0);
    size_t getNumRows() const;
    size_t getNumColumns() const;
    const SparseVector& operator[](size_t i) const;
    SparseVector& operator[](size_t i);

    // Addition and subtraction methods
    SparseMatrix operator+(double c) const;
    SparseMatrix operator-(double c) const;
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    SparseMatrix operator+(const SparseMatrix& sm) const;
    SparseMatrix operator-(const SparseMatrix& sm) const;

    // Multiplication methods
    SparseMatrix operator*(double c) const;
    Matrix operator*(const std::vector<std::vector<double> >& d) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(const SparseMatrix& sm) const;
    Vector operator*(const std::vector<double>& d) const;
    Vector operator*(const Vector& v) const;
    Vector operator*(const SparseVector& sv) const;

    Matrix getFullMatrix() const;
    std::string getText() const;
};

#endif