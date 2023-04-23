#if !defined(__MY_STACK__)
#define __MY_STACK__
#include <iostream>
#include "myExceptions.h"
#include "linearList.h"
#include "chainList.h"
template <class T>
class stack
{
private:
public:
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &top() const = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
};

template <class T>
class derivedArrayStack : private arrayList<T>, public stack<T>
{
private:
public:
    derivedArrayStack(int initalCapacity = 10);
    ~derivedArrayStack();
    bool empty() const { return arrayList<T>::empty(); }
    int size() const { return arrayList<T>::size(); }
    T &top() { return get(arrayList<T>::get(arrayList<T>::size() - 1)); }
    void pop() { arrayList<T>::erase(arrayList<T>::size() - 1); }
    void push(const T &theElement) { arrayList<T>::insert(arrayList<T>::size(), theElement); }
};

template <class T>
inline derivedArrayStack<T>::derivedArrayStack(int initalCapacity) : arrayList<T>(initalCapacity)
{
}

template <class T>
inline derivedArrayStack<T>::~derivedArrayStack()
{
}

template <class T>
class arrayStack : public stack<T>
{
private:
    int stackTop;
    int arrayLength;
    T *stack;

public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() { delete[] stack; }
    void push(const T& theElement);
};
template <class T>
inline arrayStack<T>::arrayStack(int initialCapacity)
{
    stack = new T[initialCapacity];
    arrayLength = initialCapacity;
    stackTop = -1;
}
template <class T>
inline void arrayStack<T>::push(const T& theElement)
{
    if(stackTop==arrayLength-1)
    {
        changeLength1D(stack,arrayLength,2*arrayLength);
        arrayLength=2*arrayLength;
    }
    stack[++stackTop]=theElement;
}
template<class T>
class linkedStack: public stack<T>
{
private:
    int stackSize;
    chainNode<T>* stackTop;
public:
    linkedStack(int initialCapacity=10);
    ~linkedStack();
    bool empty()const{ return stackSize==0;}
    int size()const{return stackSize;}
    T& top();
    void pop();
    void push(const T& theElement);
};
template<class T>   
linkedStack<T>::linkedStack(int initialCapacity)
{
    stackSize=0; stackTop=NULL;
}
template<class T>  
linkedStack<T>::~linkedStack()
{
    while (stackTop!=NULL)
    {
        chainNode<T>* nextNode=stackTop->next;
        delete stackTop;
        stackTop=nextNode;
    }
    
}
template<class T>   
T& linkedStack<T>::top()
{

    return stackTop->element;
    
}
template<class T>   
void linkedStack<T>::pop()
{
    chainNode<T>* Node(stackTop->next);
    delete stackTop;
    stackTop=Node;
    stackSize--;

}
template<class T>   
void linkedStack<T>::push(const T& theElement)
{
    stackTop =new chainNode<T>(theElement,stackTop); 
    stackSize++;
}
#endif

