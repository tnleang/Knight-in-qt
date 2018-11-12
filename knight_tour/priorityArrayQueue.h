//
// Created by Titichot Nuntapramote on 3/26/18.
//

#ifndef PRIORITYQUEUE_PRIORITYARRAYQUEUE_H
#define PRIORITYQUEUE_PRIORITYARRAYQUEUE_H

#include <cstdlib>
#include <iostream>

template<typename T, typename Priority = int>
struct item
{
    T data;
    Priority priority;

    item()
    {
        data = T();
        priority = Priority();
    }

    item(const T& d,const Priority &p = Priority())
    {
        data = d;
        priority = p;
    }


};

enum QUEUE_ERRORS {Q_FULL, Q_EMPTY, Q_BAD_SIZE};

template<typename T, typename Priority = int>
class queue
{
public:
    queue(size_t cap = 10);
    ~queue();
    queue(const queue<T,Priority> &other);
    queue<T,Priority>&operator=(const queue<T,Priority> &other);

    bool full();
    bool empty();
    size_t size();
    size_t capacity();
    void resize(size_t newSize);
    T& peek();

    void enqueue(const T &d, const Priority &p = Priority());
    T& dequeue();
    queue<T,Priority>& operator <<(const T &d);
    queue<T,Priority>& operator >>(T &d);



private:

    item<T,Priority>* _queue;
    size_t mySize, myCapacity;

    void copy (const queue<T,Priority> &other);
    void nukem();


};


//==================================================================================
//                      FUNCTION DEFINITION
//==================================================================================

template <typename T, typename Priority>
queue<T,Priority>::queue(size_t cap)
{
    mySize = 0;
    myCapacity = cap;
    _queue = new item<T,Priority>[myCapacity];
}


template <typename T, typename Priority>
queue<T,Priority>::~queue()
{
    nukem();
}

template <typename T, typename Priority>
queue<T,Priority>::queue(const queue<T,Priority> &other)
{
    copy(other);
}

template <typename T, typename Priority>
queue<T,Priority>& queue<T,Priority>::operator=(const queue<T,Priority> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template <typename T, typename Priority>
bool queue<T,Priority>::full()
{
    return mySize == myCapacity;
}

template <typename T, typename Priority>
bool queue<T,Priority>::empty()
{
    return !mySize;
}

template <typename T, typename Priority>
size_t queue<T,Priority>::size()
{
    return mySize;
}

template <typename T, typename Priority>
size_t queue<T,Priority>::capacity()
{
    return myCapacity;
}

template <typename T, typename Priority>
T& queue<T,Priority>::peek()
{
    return _queue[mySize - 1].data;
}


// insert sort so that the most priority will be at the end of the array
template <typename T, typename Priority>
void queue<T,Priority>::enqueue(const T &d, const Priority &p)
{
    if (full())
        throw Q_FULL;
    item<T,Priority> newItem(d,p);
    if(empty())
        _queue[mySize++] = newItem;
    else
    {
        size_t i = 0;
        for (; i < mySize && p < _queue[i].priority; i++); //go to wanna insert point


        mySize++;
        /*
         * put the newItem to that insert and pend the rest
         */
        for (; i <= mySize; i++) {
            item<T, Priority> temp = _queue[i];
            _queue[i] = newItem;
            newItem = temp;
        }
    }
}

template <typename T, typename Priority>
T& queue<T,Priority>::dequeue()  //assuming the most priority will be at the end of the array
{
    if (empty())
        throw Q_EMPTY;
    T d;
    d = _queue[mySize - 1 ].data;
    mySize--;
    return d;
}

template <typename T, typename Priority>
queue<T,Priority>& queue<T,Priority>::operator <<(const T &d)
{
    enqueue(d);
    return *this;
}

template <typename T, typename Priority>
queue<T,Priority>& queue<T,Priority>::operator >>(T &d)
{
    dequeue(d);
    return *this;
};

template <typename T, typename Priority>
void queue<T,Priority>::copy (const queue<T,Priority> &other)
{
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    _queue = new item<T,Priority>[myCapacity];
    for ( size_t i = 0; i < mySize; i++)
        _queue[i] = other._queue[i];
}

template <typename T, typename Priority>
void queue<T,Priority>::nukem()
{
    for (size_t i = 0; i< myCapacity; ++i)
        _queue[i] = item<T,Priority>();
    mySize = myCapacity  = 0;
    delete [] _queue;
}

#endif //PRIORITYQUEUE_PRIORITYARRAYQUEUE_H
