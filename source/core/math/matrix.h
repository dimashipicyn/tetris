#pragma once

template<class T, size_t N>
class Matrix
{
public:
    Matrix(std::initializer_list<T> values);

    void Rotate()

private:
    T data[N][N];
};