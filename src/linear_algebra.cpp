#include "linear_algebra.hpp"
#include <cassert>

RowTransformer::Transform::Transform(int row, int row2, std::vector<std::pair<int, double> > multipliers)
{
    m_row = row;
    // m_row2 == -1 indicates a swap transform.
    m_row2 = (multipliers.size() == 0) ? row2 : -1;
    m_rowLinearMultipliers = multipliers;
}

RowTransformer::RowTransformer()
{
    m_transforms = {};
}

void RowTransformer::swap(int rowi, int rowj)
{
    m_transforms.push_back(Transform(rowi, rowj));
}

void RowTransformer::modify(int row, const std::vector<std::pair<int, double> >& rowMultipliers)
{
    m_transforms.push_back(Transform(row, -1, rowMultipliers));
}

void RowTransformer::apply(Matrix& mat)
{
}

/*
The implementation of matrix multiplication is a naive one. In
future, this will be changed to a more efficient one, probably
employing Strassen's algorithm.
*/
Matrix multiplyMatrices(const Matrix& mat0, const Matrix& mat1)
{
    Dimension dim0 = getMatrixDimensions(mat0);
    Dimension dim1 = getMatrixDimensions(mat1);
    assert(dim0.second == dim1.first);
    Matrix result = {};
    for(int i = 0; i< dim0.first; i++)
    {
        Vector row = {};
        for(int j = 0; j < dim1.second; j++)
        {
            double sum = 0;
            for(int k = 0; k < dim0.second; k++)
            {
                sum += mat0[i][k] * mat1[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}

Matrix getMatrixInverse(const Matrix& mat)
{
    // No inspection is performed here to verify if the matrix mat is square.
    int size = mat.size();
    assert (size > 0);
    Matrix iden = getIdentityMatrix(size);
    return {};
}

Matrix getTranspose(const Matrix& mat)
{
    Matrix result = {};
    Dimension dim = getMatrixDimensions(mat);
    for(int j = 0; j < dim.second; j++)
    {
        Vector row = {};
        for(int i = 0; i < dim.first; i++)
        {
            row.push_back(mat[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

Vector multiplyMatrixAndVector(const Matrix& mat, const Vector& vec)
{
    Vector result = {};
    Dimension dim = getMatrixDimensions(mat);
    assert(dim.second == vec.size());
    for(int i = 0; i < dim.first; i++)
    {
        double sum = 0;
        for(int j = 0; j < dim.second; j++)
        {
            sum += mat[i][j] * vec[j];
        }
        result.push_back(sum);
    }
    return result;
}

bool isValidMatrix(const Matrix& mat)
{
    // A Matrix object is valid when all the rows have the same length.
    int length = 0;
    bool first = true;
    for(auto row: mat)
    {
        if(!first && (length != row.size()))
        {
            return false;
        }
        length = row.size();
        first = false;
    }
    return true;
}

bool isInvertibleMatrix(const Matrix& mat)
{
    return true;
}

Dimension getMatrixDimensions(const Matrix& mat)
{
    /*
    Note: No check is performed to verify if all the rows of mat
    have identical length. If required, that should be done using
    isValidMatrix.
    */
    int numCols = (mat.size() > 0) ? mat[0].size() : 0;
    return Dimension(mat.size(), numCols);
}

Matrix getIdentityMatrix(int size)
{
    Matrix result = {};
    for(int i = 0; i < size; i++)
    {
        Vector vec(size, 0);
        vec[i] = 1;
        result.push_back(vec);
    }
    return result;
}