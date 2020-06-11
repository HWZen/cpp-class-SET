#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <cstdlib>
#include <algorithm>
#include <iostream>
/*
    拷贝2维数组 
*/
inline void Copy2DArray(const int *const *src, size_t rows, size_t cols, int **&dest)
{
    dest = new int *[rows];
    for (size_t r = 0; r < rows; ++r)
    {
        dest[r] = new int[cols];
        for (size_t c = 0; c < cols; ++c)
        {
            dest[r][c] = src[r][c];
        }
    }
}

/*
    矩阵类
*/
class Matrix
{
public:
    int **array; /*矩阵内部的2维数组*/
    size_t rowCount /*行数*/, colCount /*列数*/;

    Matrix()
    {
        array = nullptr;
        rowCount = 0;
        colCount = 0;
    }

    /*构造指定行数和列数的0矩阵*/
    Matrix(size_t rowCount, size_t colCount)
        : rowCount(rowCount),
          colCount(colCount)
    {
        array = new int *[rowCount];
        for (size_t i = 0; i < rowCount; i++)
        {
            array[i] = new int[colCount];
            for (size_t j = 0; j < colCount; j++)
            {
                array[i][j] = 0;
            }
        }
    }

    /*按二维数组构造矩阵*/
    Matrix(const int *const *argarray, size_t rowCount, size_t colCount)
        : rowCount(rowCount),
          colCount(colCount)
    {
        Copy2DArray(argarray, rowCount, colCount, this->array);
    }

    /*拷贝构造矩阵*/
    Matrix(const Matrix &other)
        : rowCount(other.rowCount),
          colCount(other.colCount)
    {
        Copy2DArray(other.array, other.rowCount, other.colCount, this->array);
    }

    /*拷贝赋值*/
    Matrix &operator=(Matrix other)
    {
        std::swap(this->array, other.array);
        rowCount = other.rowCount;
        colCount = other.colCount;
        return *this;
    }

    ~Matrix()
    {
        if (array != nullptr)
        {
            for (size_t r = 0; r < rowCount; ++r)
            {
                delete[] array[r];
            }
            delete[] array;
        }
    }

    /*求矩阵和，行数列数必须相等*/
    Matrix operator+(const Matrix &right) const
    {
        Matrix left = *this;
        if (left.colCount != right.colCount || left.rowCount != right.rowCount)
        {
            throw "Cannot add.";
        }

        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                left.array[i][j] += right.array[i][j];
            }
        }
        return left;
    }

    /*求矩阵积，左边行数必须等于右边列数*/
    Matrix operator*(const Matrix &right) const
    {
        Matrix left = *this;
        if (left.colCount != right.rowCount)
        {
            throw "Cannot multiply.";
        }
        const size_t p = left.colCount;
        Matrix result(left.rowCount, right.colCount);
        for (size_t i = 0; i < result.rowCount; i++)
        {
            for (size_t j = 0; j < result.colCount; j++)
            {
                for (size_t k = 0; k < p; k++)
                {
                    result.array[i][j] += left.array[i][k] * right.array[k][j];
                }
            }
        }
        return result;
    }

    /*返回单位阵*/
    static Matrix Identity(size_t order)
    {
        Matrix result(order, order);
        for (size_t i = 0; i < order; i++)
        {
            result.array[i][i] = 1;
        }
        //result.ToConsole();
        return result;
    }

    /*Debug专用函数，输出矩阵*/
    void ToConsole()
    {
#define DO_NOT_PRINT_MATRIX
#ifndef DO_NOT_PRINT_MATRIX
        for (size_t i = 0; i < rowCount; i++)
        {
            for (size_t j = 0; j < colCount; j++)
            {
                std::cout << array[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
#endif
#undef DO_NOT_PRINT_MATRIX
    }
};

/*图*/
class Graph
{
public:
    Matrix nb; /*邻接矩阵*/

    Graph(const Matrix &neighour_matrix, bool isDirected)
    {
        if (neighour_matrix.colCount != neighour_matrix.rowCount)
        {
            throw "Neighbouring matrix invalid";
        }
        nb = neighour_matrix;
    }

    Matrix GetAccessMatrix() /*返回可达性矩阵*/
    {
        Matrix Term = Matrix::Identity(nb.colCount) + nb;
        Matrix TermPower = Term;
        Matrix Sum = Term;
        for (size_t i = 1; i < nb.colCount - 1; i++)
        {
            Sum.ToConsole();
            TermPower = TermPower * Term;
            TermPower.ToConsole();
            Sum = Sum + TermPower;
        }
        return Sum;
    }

    bool CanReach(size_t node1, size_t node2) //返回node1到node2节点是否可达
    {
        return GetAccessMatrix().array[node1][node2];
    }
};

#endif