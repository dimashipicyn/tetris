#pragma once

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <ostream>
#include <iomanip>

enum class MatrixRotateDir
{
    Left,
    Right
};

template<typename T, size_t Rows, size_t Cols = Rows>
class Matrix
{
public:
    Matrix() = default;
    constexpr Matrix(const std::initializer_list<T>& values)
    {
        // static_assert(values.size() == N * N, "Values size wrong!");
        std::copy(values.begin(), values.end(), (T*)m_data);
    }

    Matrix<T, Cols, Rows> Rotate(MatrixRotateDir dir)
    {
        auto transposed = Transpose();

        if (dir == MatrixRotateDir::Right)
        { // Reverse each row
            for (size_t i = 0; i < transposed.GetRows(); i++)
                std::reverse(&(transposed[i][0]), (&transposed[i][0]) + transposed.GetCols());
        }
        else
        {
            // Reverse each column
            for (size_t j = 0; j < transposed.GetCols(); j++)
            {
                for (size_t i = 0; i < transposed.GetRows() / 2; i++)
                {
                    std::swap(transposed[i][j], transposed[transposed.GetRows() - 1 - i][j]);
                }
            }
        }
        return transposed;
    }

    Matrix<T, Cols, Rows> Transpose()
    {
        Matrix<T, Cols, Rows> result;
        for (size_t i = 0; i < Rows; i++)
        {
            for (size_t j = 0; j < Cols; j++)
            {
                result[j][i] = m_data[i][j];
            }
        }
        return result;
    }

    constexpr T& Value(size_t row, size_t col)
    {
        // static_assert((row * N + col) < N * N, "Wrong index col or row!");
        return m_data[row][col];
    }

    constexpr const T& Value(size_t col, size_t row) const
    {
        // static_assert((row * N + col) < N * N, "Wrong index col or row!");
        return m_data[row][col];
    }

    static constexpr size_t GetRows()
    {
        return Rows;
    }

    static constexpr size_t GetCols()
    {
        return Cols;
    }

    T* operator[](int row) {
        return m_data[row];
    }

private:
    T m_data[Rows][Cols]{};
};

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& o, const Matrix<T, N>& m)
{
    o << "{" << std::endl;
    for (size_t i = 0; i < N; i++)
    {
        o << "\t";
        for (size_t j = 0; j < N; j++)
        {
            o << std::setw(3) << m.Value(j, i) << ", ";
        }
        o << std::endl;
    }
    o << "}";
    return o;
}