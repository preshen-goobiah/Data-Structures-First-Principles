#include "arrstack.h"

void ArrStack::push(int val)
{
    data.push_back(val);
}

int ArrStack::pop()
{
    int out = data.back();
    // vector<T>::pop_front() just removes the front item, doesn't return it
    data.pop_back();
    return out;
}

int ArrStack::peek()
{
    return data.back();
}

int ArrStack::size() const
{
    return data.size();
}

bool ArrStack::empty() const
{
    return data.empty();
}
