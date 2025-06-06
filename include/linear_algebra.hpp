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
typedef std::vector<double> Vector;
typedef std::pair<int, int> Dimension;

Matrix multiplyMatrices(const Matrix& mat0, const Matrix& mat1);
Matrix getMatrixInverse(const Matrix& mat);
Matrix getTranspose(const Matrix& mat);
Vector multiplyMatrixAndVector(const Matrix& mat, const Vector& vec);
bool isValidMatrix(const Matrix& mat);
bool isInvertibleMatrix(const Matrix& mat);
Dimension getMatrixDimensions(const Matrix& mat);
Matrix getIdentityMatrix(int size);

/*
RowTransformer helps to record a sequence of row transformations, so that they
can be applied again to another matrix. This is useful while computing matrix inverses
using an augmented matrix method.
*/
class RowTransformer
{
    class Transform
    {
        int m_row;
        std::vector<std::pair<int, double> > m_rowLinearMultipliers;
        int m_row2;
    public:
        Transform(int row, int row2, std::vector<std::pair<int, double> > multipliers = {});
        //friend class RowTransformer;
    };
    std::vector<Transform> m_transforms;
public:
    enum TransformationTypeEnum {LINEAR_COMBINATION, SWAP};
    RowTransformer();
    void swap(int rowi, int rowj);
    void modify(int row, const std::vector<std::pair<int, double> >& rowMultipliers);
    void apply(Matrix& mat);
};

#endif