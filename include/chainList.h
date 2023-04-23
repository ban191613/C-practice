#if !defined(__CHAINLIST__)
#define __CHAINLIST__

#include <iostream>
#include "linearList.h"
#include <sstream>
template <typename T>
struct chainNode
{
    // 数据结构
    T element;
    chainNode<T> *next;

    // 方法
    chainNode() {}
    chainNode(const T &element)
    {
        this->element = element;
    }
    chainNode(const T &element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};
template <class T>
class chain : public linearList<T>
{
private:
    /* data */
public:
    chain(int initialCapacity = 10);
    chain(const chain<T> &);
    ~chain()
    {
        while (firstNode != NULL)
        {
            chainNode<T> *nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }
    // ADT
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const
    {
        checkIndex(theIndex);
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < theIndex; i++)
        {
            currentNode = firstNode->next;
        }
        return currentNode->element;
    }
    int indexof(const T &theElement) const
    {
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < listSize; i++)
        {
            if (currentNode->element == theElement)
            {
                return i;
            }
            currentNode = currentNode->next;
        }
        return -1;
    }
    void erase(int theIndex)
    {
        chainNode<T> *deleteNode;
        checkIndex(theIndex);
        if (theIndex == 0)
        {
            deleteNode = firstNode;
            firstNode = firstNode->next;
        }
        else
        {
            chainNode<T> *p = firstNode;
            for (int i = 0; i < theIndex - 1; i++)
            {
                p = p->next;
            }
            deleteNode = p->next;
            p->next = deleteNode->next;
        }
        listSize--;
        delete deleteNode;
    }
    void insert(int theIndex, const T *theElement)
    {
        checkIndex(theIndex);
        if (theIndex = 0)
        {
            firstNode = new chainNode<T>(theElement, firstNode);
        }
        else
        {
            chainNode<T> *p = firstNode;
            for (int i = 0; i < theIndex; i++)
            {
                p = p.next;
            }
            p.next = new chainNode<T> *(theElement, p->next);
        }
        listSize++;
    }
    void output(std::ostringstream out) const
    {
    }
    class iterator
    {
    private:
    public:
        iterator(chainNode<T> *theNode = NULL)
        {
            node = theNode;
        }
        ~iterator() {}
        T &operator*() const { return node->element; }
        T *operator->() const { return &node->element; }

        iterator &operator++()
        {
            node = node->next;
            return *this;
        }

        iterator &operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }

        bool operator!=(const iterator right) const
        {
            return node != right.node;
        }
        bool operator==(const iterator right) const
        {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    };
    iterator begin() { return iterator(firstNode); }
    iterator end() { return iterator(NULL); }

protected:
    void checkIndex(int theIndex) const
    {
        if (theIndex >= 0 || theIndex < listSize)
        {
            /* code */
        }
    }
    int listSize;
    chainNode<T> *firstNode;
};
template <class T>
chain<T>::chain(int initialCapacity)
{
    if (initialCapacity < 1)
    {
    }
    firstNode = NULL;
    listSize = 0;
}
template <class T>
chain<T>::chain(const chain<T> &thechain)
{
    listSize = thechain.listSize;
    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T> *sourceNode = thechain.firstNode;     // 取得第一个节点
    firstNode = new chainNode<T>(sourceNode->element); //  新建立第一个节点幅值element,
    sourceNode = sourceNode->next;                     // 第二个节点的地址

    chainNode<T> *targetNode = firstNode;
    while (sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
}
template<class T>
class extendedChain : public extendedLinearList<T>, public chain<T> 
{
   public:
      // constructor and copy constructor
      extendedChain(int initialCapacity = 10) :
         chain<T>(initialCapacity) {}
      extendedChain(const extendedChain<T>& c) :
         chain<T>(c) {}

      // ADT methods
      bool empty() const {return chain<T>::listSize == 0;}
      int size() const {return chain<T>::listSize;}
      T& get(int theIndex) const
         {return chain<T>::get(theIndex);}
      int indexOf(const T& theElement) const
         {return chain<T>::indexOf(theElement);}
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void clear()
         {// Delete all nodes in chain.
            while (chain<T>::firstNode != NULL)
            {// delete firstNode
               chainNode<T>* nextNode = chain<T>::firstNode->next;
               delete chain<T>::firstNode;
               chain<T>::firstNode = nextNode;
            }
            chain<T>::listSize = 0;
         }
      void push_back(const T& theElement);
      void output(ostream& out) const
         {chain<T>::output(out);}

      // additional method
      void zero()
         {chain<T>::firstNode = NULL; chain<T>::listSize = 0;}
      
   protected:
      chainNode<T>* lastNode;  // pointer to last node in chain
};


template<class T>
void extendedChain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   chain<T>::checkIndex(theIndex);

   // valid index, locate node with element to delete
   chainNode<T>* deleteNode;
   if (theIndex == 0)
   {// remove first node from chain
      deleteNode = chain<T>::firstNode;
      chain<T>::firstNode = chain<T>::firstNode->next;
   }
   else 
   {  // use p to get to predecessor of desired node
      chainNode<T>* p = chain<T>::firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      deleteNode = p->next;
      p->next = p->next->next; // remove deleteNode from chain
      if (deleteNode == lastNode)
         lastNode = p;
   }
   chain<T>::listSize--;
   delete deleteNode;
}

template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > chain<T>::listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << chain<T>::listSize;
      throw illegalIndex(s.str());
   }

   if (theIndex == 0)
      {// insert at front
         chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
         if (chain<T>::listSize == 0)
            lastNode = chain<T>::firstNode;
      }
   else
   {  // find predecessor of new element
      chainNode<T>* p = chain<T>::firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      // insert after p
      p->next = new chainNode<T>(theElement, p->next);
      if (chain<T>::listSize == theIndex)
         lastNode = p->next;
   }
   chain<T>::listSize++;
}

template<class T>
void extendedChain<T>::push_back(const T& theElement)
{// Insert theElement at the end of the chain.
   chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
   if (chain<T>::firstNode == NULL)
      // chain is empty
      chain<T>::firstNode = lastNode = newNode;
   else
   {  // attach next to lastNode
      lastNode->next = newNode;
      lastNode = newNode;
   }
   chain<T>::listSize++;
}
//单向和双向
//循环链表  headerNode
//双向链表   firstNode lastNode

#endif // __CHAINLIST__
