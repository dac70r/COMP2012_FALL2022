#include "container.h"
#include <iostream>

void Container::addObject(Object *object)   //Task 1&3
{
    
}

void Container::display() const //Task 1
{
    
}

Container::Container() 
{
    for (int i = 0; i < MAX_OBJECT_NUM; i++)
        _objects[i] = nullptr;

    _num_object = 0;
}

Container::~Container()  //Task 1
{

}