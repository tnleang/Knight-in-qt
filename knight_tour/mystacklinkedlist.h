#ifndef MYSTACKLINKEDLIST_H
#define MYSTACKLINKEDLIST_H
#include <iostream>

enum MYSTACK_ERRORS {STACK_EMPTY , STACK_FULL , STACK_BAD_SIZE};

template <typename T>
struct Node
{
    T data;
    Node *next;

    Node(T item)
    {
        data = item;
    }
};

template <typename T>
class MyStack
{
    public:
        MyStack( size_t c = 10);
        ~MyStack();
        MyStack( const MyStack<T> &other);
        MyStack<T>& operator =(const MyStack<T> &other);

        bool empty();
        bool full();
        void push (const T& x);
        T pop();
        T peek();
        void clear();
        size_t size();


    private:
        Node<T> *head;
        int tos;
        size_t myCapacity;

        void copy(const MyStack<T> &other);
        void deleteAll();

};


//==========================================================================
//                              DEFINITION
//==========================================================================




template<typename T>
MyStack<T>::MyStack(size_t c) : head(NULL)
{
    if(c < 2)
        throw STACK_BAD_SIZE;
    myCapacity = c;
    tos = -1;
}


template<typename T>
MyStack<T>::~MyStack()
{
    deleteAll();
    tos = -1;
}

template<typename T>
MyStack<T>::MyStack( const MyStack<T> &other)
{
    copy(other);
}

template<typename T>
MyStack<T>& MyStack<T>::operator =(const MyStack<T> &other)
{
    if (this != &other)
    {
        deleteAll();
        copy(other);
    }
    return *this;
}

template<typename T>
bool MyStack<T>::empty()
{
    return !head;
}

template<typename T>
bool MyStack<T>::full()
{
    return tos+1 >= myCapacity;
}

template<typename T>
void MyStack<T>::push (const T& x)
{
    if  (full())
        throw STACK_FULL;
    Node<T>* insert = new Node<T>(x);
    insert->next = head;
    head = insert;
}

template<typename T>
T MyStack<T>::pop()
{
    if  (empty())
        throw STACK_EMPTY;
    T data = head->data;
    Node<T>* toKill = head;
    head = head->next;
    delete toKill;
    return data;
}

template<typename T>
T MyStack<T>::peek()
{
    if  (empty())
        throw STACK_EMPTY;
    return head->data;
}

template<typename T>
void MyStack<T>::clear()
{
    deleteAll();
    tos= -1;
}

template<typename T>
size_t MyStack<T>::size()
{
    return tos + 1;
}

template<typename T>
void MyStack<T>::copy(const MyStack<T> &other)
{
    tos = other.tos;
    Node<T>* walker = other.head;
    Node<T>* copy_head = NULL;
    Node<T>* copy_walker = copy_head;
    while (walker != NULL)
    {
        //1. create new node(item)
        //2. make temp point to *after_me point
        /*   head                   2000                          4000
                -----------         ------------------           ----------------------
                 2000        --->                  |4    --->                       |
                -----------                        |0                               |
                                                   |0                               |0
                ------------                       |0                               |
                          |         ------------------           ---------------------
                  item    |0
                          |
                          |
                ------------
                7000
            */
        //3. make after_me point to temp one
        /*   head                   2000                          4000
                -----------         ------------------           ----------------------
                 2000        --->                  |4    --->                       |
                -----------                        |0                               |
                                                   |0                               |0
                               -->                 |0                               |
                ------------   |                   |                                |
                          |2   |    ------------------           ---------------------
                  item    |0 --|
                          |0
                          |0
                ------------
                7000
            */
        //4. move walker to the next one
        /*   head                   2000                          4000
                -----------         ------------------           ----------------------
                 7000                              |4    --->                       |
                -----------                        |0                               |
                     |                             |0                               |0
                     V         -->                 |0                               |
                ------------   |                   |                                |
                          |2   |    ------------------           ---------------------
                  item    |0 --|
                          |0
                          |0
                ------------
                7000
            */
        Node<T> *temp = new Node<T>(walker->data);
        temp->next = copy_walker->next;
        copy_walker->next =temp;
        walker = walker->next;
    }
    head = copy_head;

}

template<typename T>
void MyStack<T>::deleteAll()
{
    Node<T>* next;
    while ( head != NULL)  //if the head is NULL, then the list is empty, nothing to delete
    {
        next = head->next;    //point the next to next one
        delete head;                //delete the current one
        head = next;                //move the current one to the next one
    }

}



#endif // MYSTACKLINKEDLIST_H
