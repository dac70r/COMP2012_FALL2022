#include "container.h"
#include <iostream>

void Container::addObject(Object *object)   //Task 1&3
{

    if(this->getPosition().x + object->getSize().x>this->getSize().x || this->getPosition().y + object->getSize().y>this->getSize().y)
       {
            cout<<"The object "<< object->getName()<< " is too large and cannot be added to "<<this->getName();
       } 
    else{
        if (_num_object < MAX_OBJECT_NUM){
            _objects[_num_object++] = object;
        }
    }

    

        

    
    //debugging code
    //Object* parental_guidance;
    //cout<<"Adding an object under "<< this->getName()<<" called "<< object->getName()<<"\n";
    object->setParent(this);
    //object->setPosition(object->)
    //cout<<"Name of parent is :"<<_parent->getName();
    
}

void Container::display() const //Task 1
{
    std::cout << "\nContainer";
    this->displayBasic();
    std::cout<<"\n";
    if (_num_object != 0){
        std::cout<<"\t\t#objects: "<<_num_object;
        std::cout <<"\n";

        if(_num_object != 0){
            for(int k =0; k<_num_object;k++){
                _objects[k]->display();
            }
        }
    }
    else{
        std::cout <<"\n";
    }

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