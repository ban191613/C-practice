#if !defined(__LINERALIST__)
#define __LINERALIST__

#include <iostream>
#include <sstream>
#include <string>
#include <myExceptions.h>
#include <algorithm>
#include <iterator>

template <class T>
class linearList
{
private:
public:
    linearList(){};
    virtual ~linearList(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int theIndex) const = 0;
    virtual int indexof(const T &theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T &theElement) = 0;
    virtual void output(std::ostream &out) const = 0;
    // iterator for arrayList
    class iterator
    {
    public:
        // typedefs required by C++ for a bidirectional iterator
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // constructor
        iterator(T *thePosition = 0) { position = thePosition; }

        // dereferencing operators
        T &operator*() const { return *position; }
        T *operator->() const { return &*position; }

        // increment
        iterator &operator++() // preincrement
        {
            ++position;
            return *this;
        }
        iterator operator++(int) // postincrement
        {
            iterator old = *this;
            ++position;
            return old;
        }

        // decrement
        iterator &operator--() // predecrement
        {
            --position;
            return *this;
        }
        iterator operator--(int) // postdecrement
        {
            iterator old = *this;
            --position;
            return old;
        }

        // equality testing
        bool operator!=(const iterator right) const
        {
            return position != right.position;
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }

    protected:
        T *position;
    }; // end of iterator class
};

template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    if (newLength < 0)
    {
        throw illegalParameterValue("new length must be>=0");
    }
    T *temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}
template <class T>
class arrayList : public linearList<T>
{
private:
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T> &);

    ~arrayList() { delete[] element; };
    // ADT方法
    bool empty() const { return listSize == 0; };
    int size() const { return listSize; };
    T &get(int theIndex) const;
    int indexof(const T &theElement) const;
    void erase(int theIndex);
    void insert(int hreIndex, const T &theElement);
    void output(std::ostream &out) const;
    int capacity() const { return arrayLength; };

protected:
    void checkIndex(int theIndex) const;
    T *element;
    int arrayLength;
    int listSize;
};
// 构造函数
template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity=" << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}
template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index=" << theIndex << "size==" << listSize;
        throw illegalIndex(s.str());
    }
}
template <class T>
T &arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}
template <class T>
int arrayList<T>::indexof(const T &theElement) const
{
    int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
    {
        return -1;
    }
    else
        return theIndex;
}
template <class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);

    element[--listSize].~T();
}
template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "index =" << theIndex << "size=" << listSize;
        throw illegalIndex(s.str());
    }
    if (listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}
template <class T>
void arrayList<T>::output(std::ostream &cout) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(cout, " "));
}
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}

template <class T>
class extendedLinearList : public linearList<T>
{
public:
    virtual ~extendedLinearList() {}
    virtual void clear() = 0;
    virtual void push_back(const T &theElement) = 0;
};

#endif // __LINERALIST__
