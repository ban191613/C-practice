#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "linearList.h"
#include "myExceptions.h"
template <class T>
class vectorList : public linearList<T>
{
private:
    /* data */
public:
    // 构造和复制函数和解析函数
    vectorList(int initialCapacity = 10);

    vectorList(const vectorList<T> &);

    ~vectorList() { delete element; }
    // // ADT方法
    bool empty() const { return element->empty(); }
    int size() const { return (int)element->size(); }
    T &get(int theIndex) const;
    int indexof(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;

    int capacity() const { return (int)element->capacity(); }

    typedef typename std::vector<T>::iterator iterator;
    iterator begin() { return element->begin(); }
    iterator end() { return element.end(); }

protected:
    void checkIndex(int theIndex) const;
    std::vector<T> *element;
};
template <class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initilal capacity=" << initialCapacity << "must be > 0";
        throw illegalParameterValue(s.str());
    }
    element = new vector<T>;
    // create an empty vector with capacity 0
    element->reserve(initialCapacity);
    // increase vector capacity from 0 to initialCapacity
}
template <class T>
vectorList<T>::vectorList(const vectorList<T> &theList)
{
    element = new vector<T>(*theList.element);
}

template <class T>
T &vectorList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return (*element)[theIndex];
}

template <class T>
int vectorList<T>::indexof(const T &theElement) const
{

    // int i = 0;
    // for (vectorList::iterator it = vectorList::begin(); it < vectorList::end();it++)
    // {
    //     if (theElement == *it)
    //     {
    //         return i;
    //     }
    //     i++;
    // }
    // return -1;
    int theIndex = (int)(find(element->begin(), element->end(),theElement) -element->begin());
    // check if theElement was found
    if (theIndex == size())
        // not found
        return -1;
    else
        return theIndex;
}

template <class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

template <class T>
void vectorList<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex < 0 || theIndex > size())
    {
        std::ostringstream s;
        s << "index =" << theIndex << "size =" << size();
        throw illegalIndex(s.str());
    }
    element->insert(element->begin() + theIndex, theElement);
}

template <class T>
void vectorList<T>::output(std::ostream &out) const
{ // Put the list into the stream out.
    copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
std::ostream &operator<<(std::ostream &out, const vectorList<T> &x)
{
    x.output(out);
    return out;
}

template <class T>
void vectorList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex > size())
    {
        std::ostringstream s;
        s << "index =" << theIndex << "size =" << size();
        throw illegalIndex(s.str());
    }
}
