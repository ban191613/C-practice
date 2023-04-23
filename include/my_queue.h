#if !defined(MY_QUEUE)
#define MY_QUEUE
#include <iostream>
template <class T>
class queue
{
public:
    queue() {}
    virtual ~queue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &front() = 0;
    virtual T &back() = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
};
template <class T>
class array_queue : public queue<T>
{
public:
    array_queue(int capacity = 10);
    ~array_queue();
    bool empty() const { return (end == -1); }
    int size() const { return (end - begin + 1); }
    T &front() { return array[begin]; }
    T &back() { return array[end]; }
    void pop() { front++; }
    void push(const T &theElement);

protected:
    int capacity = 0;
    T *array;
    int begin = 0;
    int end = -1;
};

template <class T>
inline array_queue<T>::array_queue(int capacity) : capacity(capacity)
{
    array = new T[capacity];
}

template <class T>
inline array_queue<T>::~array_queue()
{
    delete[] array;
}
template <class T>
void array_queue<T>::push(const T &theElement)
{
    if ((end + 1) == capacity)
    { // 整体挪动
        for (int j ,i  = 0,begin; i <= end; i++ ,j++)
        {
            array[j] = array[i];
        }
        end = end - begin;
        begin = 0;
    }
    end++;
    array[end] = theElement;
}
#endif // MY_QUEUE
