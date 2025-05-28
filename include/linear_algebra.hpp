#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

/*
This header will have declarations of functions used for simple
matrix operations, like matrix multiplications, and computing
matrix inverses, etc.
A vector of vectors will be used to represent a matrix.
*/

#include <vector>

typedef std::vector<std::vector<double> > Matrix;

Matrix multiplyMatrices(const Matrix& mat0, const Matrix& mat1);
Matrix getMatrixInverse(const Matrix& mat);
Matrix getTranspose(const Matrix& mat);
bool isValidMatrix(const Matrix& mat);
bool isInvertibleMatrix(const Matrix& mat);

#endif