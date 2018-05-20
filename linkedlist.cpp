#include "linkedlist.h"
#include <iostream>

using namespace std;

// Whether to print when destructing a link
bool Link::pDtor = true;

/**
 * @brief Link::Link
 * @param v Value of the link
 * Initialise values (no allocation is needed this time)
 */
Link::Link(int v)
{
   value = v;
   next = nullptr;
}

/**
 * @brief Link::~Link
 * Desctuctor for each link.
 * Don't change this function, it lets me see when a
 *   link is destroyed.
 */
Link::~Link()
{
    if(Link::pDtor == true)
        cout << "Destroyed " << value << endl;
}

/**
 * @brief LinkedList::LinkedList
 * Initialise values (no allocation is needed this time)
 */
LinkedList::LinkedList()
{
    head = nullptr;
   // cout << head->value << endl;
}

/**
 * @brief LinkedList::~LinkedList
 * Traverse the list and deallocate all the links in it
 */
LinkedList::~LinkedList()
{
    Link *curr, *tmp;
    curr = head;
    
        while (curr!=nullptr)
        {
            tmp = curr;
            curr = curr->next;
            delete tmp;
        }
}

/**
 * @brief LinkedList::printList
 * Print the list to cout
 * It should have the following format:
 * [val1,val2...]\n
 * There should be no other output
 */
void LinkedList::printList() const
{
    
    if (head == nullptr)
    {
        cout << "[]" << endl ;
    }
    else
    {
        Link *curr = head;
        cout << "[";
        do
        {
            cout << curr->value;
            if (curr->next != nullptr)
            {
                cout << ",";
            }
            curr = curr->next;
        }
        while (curr != nullptr);
        cout << "]" << endl;
    }
    
}

/**
 * @brief LinkedList::addToFront
 * @param value Value to be prepended.
 * Prepend a value to the front of the list.
 */
void LinkedList::addToFront(int value)
{
        Link *p = new Link(value);
        Link *tmp = this->head;
        this->head = p;
        p->next = tmp;
}

/**
 * @brief LinkedList::addToBack
 * @param value Value to be appended.
 * Append a value to the back of the list.
 */
void LinkedList::addToBack(int value)
{
    Link *curr = head;
    Link *newLink = new Link(value);
    if (head == nullptr)
    {
        head = newLink;
    }
    else
    {
          while (curr != nullptr )
          {
              if (curr->next == nullptr)
              {
                  curr->next = newLink;
                  curr = curr->next;
              }
              curr = curr->next;
         }
    }
}

/**
 * @brief LinkedList::deleteLast
 * Delete the last item in the list.
 */
void LinkedList::deleteLast()
{
    if (head != nullptr)
    {
        Link *curr = head;
        if (curr->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Link *tmp = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            while (tmp->next != curr)
            {
                tmp = tmp->next;
            }
            tmp->next = nullptr;
            delete curr;
        }
    }
    
    
    //Tahseens Code
    /*  Link *curr = head;
     if (head != nullptr)
     {
     if (head->next == nullptr)
     {
     delete head;
     head = nullptr;
     }
     else
     {
     Link *tmp = head;
     int counter = 0;
     while (curr->next != nullptr)
     {
     curr = curr->next;
     counter++;
     }
     for (int i = 0; i < counter-1; i++)
     {
     tmp = tmp->next;
     }
     
     tmp->next = nullptr;
     delete curr;
     }
     
     }*/

}

/**
 * @brief LinkedList::deleteFirst
 * Delete the first item in the list.
 */
void LinkedList::deleteFirst()
{
    if (head !=nullptr)
    {
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Link *tmp = head->next;
            delete head;
            head = tmp;
        }
    }
}

/**
 * @brief LinkedList::insertItem
 * @param index
 * @param value
 * Insert a value before index.
 */
void LinkedList::insertItem(int index, int value)
{
    Link *curr,*newLink, *tmp;
    newLink = new Link(value);
    if (index != 0)
    {
        curr = head;
        newLink = new Link(value);
        for (int i = 0; i < (index-1); i++)
        {
            curr = curr->next;
        }
        
        tmp = curr->next;
        curr->next = newLink;
        curr = curr->next;
        curr->next = tmp;
    }
    else
    {
        this->addToFront(value);
    }
    
    /* Marcs Simpler Method
     
        
        Link *newLink = new Link(value);
        if (index!=0)
        {
            Link *current = head;
            Link *before = head;
            
            for (int i = 0; i<index; i++)
            {
                before = current;
                current = current->next;
                
            }
            before->next = newLink;
            newLink->next = current;
        }
        
        else
        {
            
            addToFront(value);
            
        }
     */
}

/**
 * @brief LinkedList::deleteItem
 * @param index
 * Delete the item at index.
 */
void LinkedList::deleteItem(int index)
{
    Link *curr,*newLink, *tmp;

    if (index != 0)
    {
        curr = head;
        for (int i = 0; i < (index-1); i++)
        {
            curr = curr->next;
        }
        tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
        
    }
    else
    {
        this->deleteFirst();
    }
    
    /* Marcs  simpler method
     
     Link *curr = head;
     Link *before = head;
     if (index == 0 ) {
     Link *tmp = head;
     
     delete head;
     
     head= tmp->next;
     }else{
     
     for (int i =0 ; i<index; i++) {
     before = curr;
     curr = curr->next;
     
     
     
     }
     
     before->next = curr->next;
     delete curr;
     }*/
     
}

/**
 * @brief LinkedList::copyList
 * @return Pointer to a new copy of the list.
 * Allocate a new list and copy elements from this one.
 */
LinkedList *LinkedList::copyList() const
{
    LinkedList *newList = new LinkedList();
    if (head != nullptr)
    {
        Link *curr = head;
        do
        {
            newList->addToBack(curr->value);
            curr = curr->next;
        }
        while (curr->next != nullptr);
        
        newList->addToBack(curr->value);

    }
    
    return newList;
}

/**
 * @brief LinkedList::reverseList
 * Reverse the values in the list.
 * This should be done by swapping pointers, not by swapping values!
 */
void LinkedList::reverseList()
{
    if (head !=nullptr)
    {
        Link *curr = head;
        Link* memory[length()];
        int size = length();
        int i= 0;
        while (curr !=nullptr)
        {
            memory[i] =curr;
            curr = curr->next;
            i++;
        }
        
        head  = memory[size-1];
        curr = head;
        
        for (int i = (size-2); i > -1 ; i--)
        {
            curr->next = memory[i];
            curr = curr->next;
        }
        
        curr->next = nullptr;
    }
    
}

/**
 * @brief LinkedList::swap
 * @param index1
 * @param index2
 * Swap 2 links in the list - there are some special cases.
 */
void LinkedList::swap(int index1, int index2)
{
    Link *tmp1, *curr1, *curr2;
    curr1 = head;
    curr2 = head;
    for (int i = 0; i < index1; i++)
    {
        curr1 = curr1->next;
    }
    for (int i = 0; i < index2; i++)
    {
        curr2 = curr2->next;
    }
    
    int tmp = curr1->value;
    curr1->value = curr2->value;
    curr2->value = tmp;
    
}
/**
 * @brief LinkedList::getLink
 * @param index
 * @return A pointer to the link at index.
 */
Link* LinkedList::getLink(int index)
{
    Link *newLink;
    if (head != nullptr)
    {
        
        Link *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        newLink = curr;
    }
    return newLink;
}

/**
 * @brief LinkedList::getValue
 * @param index
 * @return The value of the link at index.
 */
int& LinkedList::getValue(int index)
{
    return getLink(index)->value;
}

/**
 * @brief LinkedList::operator []
 * @param index
 * @return A reference to the value at index.
 * This allows myList[i] get operations.
 */
int& LinkedList::operator[](int index)
{
    return getValue(index);
}

/**
 * @brief LinkedList::length
 * @return Returns the length of the list.
 */
int LinkedList::length() const
{
    int count=0;
    Link *curr = head;
    while (curr!=nullptr)
    {
        curr=curr->next;
        count = count + 1;
    }
    return count;
}

