#include "linear_algebra.hpp"
#include <cassert>
#include <algorithm>

RowTransformer::Transform::Transform(int row, int row2, std::vector<std::pair<int, double> > multipliers)
{
    m_row = row;
    // multipliers.size() == 0 indicates a swap transform
    // hence when multipliers.size() == 0 and row2 == -1 should not happen at the same time
    // when multipliers.size() == 0, row2 should indicate valid row-id
    m_row2 = (multipliers.size() == 0) ? row2 : -1;
    m_rowLinearMultipliers = multipliers;
}

RowTransformer::RowTransformer()
{
    m_transforms = {};
}

void RowTransformer::recordSwap(int rowi, int rowj)
{
    m_transforms.push_back(Transform(rowi, rowj));
}

void RowTransformer::performSwap(int rowi, int rowj, Matrix& mat)
{
    int numCols = mat[0].size();
    for(int j = 0; j < numCols; j++)
    {
        std::swap(mat[rowi][j], mat[rowj][j]);
    }
    recordSwap(rowi, rowj);
}

void RowTransformer::recordRowModification(int row, const std::vector<std::pair<int, double> >& rowMultipliers)
{
    m_transforms.push_back(Transform(row, -1, rowMultipliers));
}

void RowTransformer::performRowModification(int row, const std::vector<std::pair<int, double> >& rowMultipliers, Matrix& mat, int columnStart, int columnEnd)
{
    columnEnd = (columnEnd == -1) ? mat[0].size() : columnEnd;
    int increment = (columnEnd > columnStart) ? 1 : -1;
    for(int j = columnStart; (increment == 1 && j < columnEnd) || (increment == -1 && j > columnEnd); j = j + increment)
    {
        double sum = 0;
        for(auto& rowMultiplier: rowMultipliers)
        {
            int row = rowMultiplier.first;
            double multiplier = rowMultiplier.second;
            sum += mat[row][j] * multiplier;
        }
        mat[row][j] = sum;
    }
    recordRowModification(row, rowMultipliers);
}

Matrix& RowTransformer::apply(Matrix& mat)
{
    int numCols = mat[0].size();
    for(auto &transform: m_transforms)
    {
        if(transform.m_row2 != -1) // swap
        {
            performSwap(transform.m_row, transform.m_row2, mat);
        }
        else // linear combination
        {
            performRowModification(transform.m_row, transform.m_rowLinearMultipliers, mat);
        }
    }
    return mat;
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
    RowTransformer rowTransformer;
    Matrix matDup = duplicateMatrix(mat);
    bool matrixInvertible = true; // assumed at the start
    for(int i = 0; i < size; i++)
    {
        if(matDup[i][i] == 0) // better condition possible (TODO)
        {
            int nonZeroPivotRow = -1;
            for(int i2 = (i+1); i2 < size; i2++)
            {
                if(matDup[i2][i] != 0) // this may be improved, as comparison to 0 may not be optimal
                {
                    nonZeroPivotRow = i2;
                    break;
                }
            }
            if(nonZeroPivotRow != -1)
            {
                rowTransformer.performSwap(i, nonZeroPivotRow, matDup);
            }
            else
            {
                matrixInvertible = false;
                // at this point return - no need to proceed further
            }
        }
        if(matrixInvertible)
        {
            RowMultVector rowMults = {RowMultiplier(i, 1 / matDup[i][i])};
            rowTransformer.performRowModification(i, rowMults, matDup, i);
            for(int i2 = (i+1); i2 < size; i2++)
            {
                rowMults = {RowMultiplier(i2, 1), RowMultiplier(i, -matDup[i2][i])};
                rowTransformer.performRowModification(i2, rowMults, matDup, i);
            }
        }
    }
    for(int i = (size-1); i >=0; i--)
    {
        for(int i2 = (i-1); i2 >= 0; i2--)
        {
            RowMultVector rowMults = {RowMultiplier(i2, 1), RowMultiplier(i, -matDup[i2][i])};
            rowTransformer.performRowModification(i2, rowMults, matDup, i, (i2-1));
        }
    }
    return rowTransformer.apply(iden);
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

Matrix duplicateMatrix(const Matrix& mat)
{
    Matrix dup = {};
    for(int i = 0; i < mat.size(); i++)
    {
        std::vector<double> rowVec = mat[i];
        dup.push_back(rowVec);
    }
    return dup;
}