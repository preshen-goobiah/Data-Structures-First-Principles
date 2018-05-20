#include "manualstack.h"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

ManualStack::ManualStack()
    : cap(2), top(0), data(new int[cap])
{

}

ManualStack::~ManualStack()
{
    delete data;
}

void ManualStack::push(int val)
{
    if(is_full()){
        reallocate(cap*2);
    }
    data[top] = val;
    ++top;
}

int ManualStack::pop()
{
    if(empty()){
        throw std::runtime_error("Popped from an empty stack");
    }

    --top;
    return data[top];
}

int ManualStack::peek()
{
    if(empty()){
        throw std::runtime_error("Peeked from an empty stack");
    }
    return data[top-1];
}

int ManualStack::size() const
{
    return top;
}

bool ManualStack::empty() const
{
    return top == 0;
}

void ManualStack::reallocate(int new_capacity)
{
    cout << "Reallocating, new capacity: " << new_capacity << endl;
    // Make sure that we always have space for our items
    if(new_capacity < top){
        new_capacity = top;
    }

    // Allocate space
    int *tmp = new int[new_capacity];
    // Copy everything across
    for(int i = 0; i < top; ++i){
        tmp[i] = data[i];
    }

    // Dellocate the old memory
    delete data;
    // Update this object
    data = tmp;
    cap = new_capacity;
}

bool ManualStack::is_full() const
{
    return top == cap;
}

