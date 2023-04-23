#if !defined(__MY_MAtRIX__)
#define __MY_MAtRIX__
#include <algorithm>
#include <iostream>
#include "myExceptions.h"
template <class T>
class matrix
{
private:
    int theRows, theColumns;
    T *element;

public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(const matrix<T> &m);
    ~matrix() { delete[] element; }
    int rows() const { return theRows; }
    int columns() const { return theColumns; }
    T &operator()(int i, int j) const;
    matrix<T> &operator=(const matrix<T> &);
    matrix<T> operator+() const;
    matrix<T> operator+(const matrix<T> &) const;
    matrix<T> operator-() const;
    matrix<T> operator-(const matrix<T> &) const;
    matrix<T> operator*(const matrix<T> &) const;
    matrix<T> operator+=(const T &);
};
template <class T>
matrix<T>::matrix(int theRows, int theColumns) : theRows(theRows), theColumns(theColumns)
{
    if (theRows < 0 || theColumns < 0)
    {
        ;
    }
    element = new T[theRows * theColumns];
}
template <class T>
matrix<T>::matrix(const matrix<T> &m) : theRows(m.theRows), theColumns(m.theColumns)
{
    element = new T[theRows * theColumns];
    std::copy(m.columns, m.element + theRows * theColumns, element);
}

template <class T>
T &matrix<T>::operator()(int i, int j) const
{
    return element[(i - 1) * theColumns + j - 1];
}
template <class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &m)
{
    if (this != &m) // 地址不相等
    {
        delete[] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows * theRows];
        std::copy(m.columns, m.element + theRows * theColumns, element);
    }
    return *this;
}

template <class T>
inline matrix<T> matrix<T>::operator+() const
{
    return *this;
}
template <class T>
inline matrix<T> matrix<T>::operator+(const matrix<T> & m) const
{
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        w.element[i] = m.element[i]+element[i];
    return w;
}
template <class T>
inline matrix<T> matrix<T>::operator-() const
{
    matrix<T> m(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i++)
        m.element[i] = -element[i];
    return m;
}
#endif // __MY_MAtRIX__
