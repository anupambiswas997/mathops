#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

/*
This header will have declarations of functions used for simple
matrix operations, like matrix multiplications, and computing
matrix inverses, etc.
A vector of vectors will be used to represent a matrix.
*/

#include "common_types.hpp"

Matrix multiplyMatrices(const Matrix& mat0, const Matrix& mat1);
Matrix getMatrixInverse(const Matrix& mat, bool debug=false);
Matrix getTranspose(const Matrix& mat);
Vector multiplyMatrixAndVector(const Matrix& mat, const Vector& vec);
bool isValidMatrix(const Matrix& mat);
bool isInvertibleMatrix(const Matrix& mat);
Dimension getMatrixDimensions(const Matrix& mat);
Matrix getIdentityMatrix(int size);
Matrix duplicateMatrix(const Matrix& mat);

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
        friend class RowTransformer;
    };
    std::vector<Transform> m_transforms;
    bool m_debug;
public:
    RowTransformer(bool debug=false);
    void recordSwap(int rowi, int rowj);
    void performSwap(int rowi, int rowj, Matrix& mat);
    void performAndRecordSwap(int rowi, int rowj, Matrix& mat);
    void recordModification(int row, const std::vector<std::pair<int, double> >& rowMultipliers);
    void performModification(int row, const std::vector<std::pair<int, double> >& rowMultipliers, Matrix& mat, int columnStart=0, int columnEnd=-1);
    void performAndRecordModification(int row, const std::vector<std::pair<int, double> >& rowMultipliers, Matrix& mat, int columnStart=0, int columnEnd=-1);
    Matrix& apply(Matrix& mat);
};

#endif