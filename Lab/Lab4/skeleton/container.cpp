#include "container.h"
#include <iostream>

void Container::addObject(Object *object)   //Task 1&3
{
    if (_num_object < MAX_OBJECT_NUM)
        _objects[_num_object++] = object;
    
}

void Container::display() const //Task 1
{
    std::cout << "\nContainer";
    this->displayBasic();
    std::cout <<"\n\t";
    //std::cout <<"\t";
    std::cout << "\nTextbox";
    this->displayBasic();
    std::cout <<"\n\t";
    std::cout <<"\t";
    
}

Container::Container() 
{
    for (int i = 0; i < MAX_OBJECT_NUM; i++)
        _objects[i] = nullptr;

    _num_object = 0;
}

Container::~Container()  //Task 1
{
    std::cout<<"\nDestructing Container "<<this->getName();
    for (int i = 0; i < _num_object; i++)
        if ( _objects[i] != nullptr)
            delete _objects[i];
    
}