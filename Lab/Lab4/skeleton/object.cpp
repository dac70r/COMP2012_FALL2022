#include <iostream>
#include "object.h"


const Pair Object::getSize() const
{
    return _size;
}

const Pair Object::getPosition() const  //Task 2
{   
    Object* pointer = this->_parent; // this object's parent
    //cout<<" get Position called: "<<this->getName();
    if(this->_parent == nullptr){
        return _position;
    }
    else{
        Pair dennis;
        dennis.x = _position.x;
        dennis.y = _position.y;
        while (pointer != nullptr){
        //cout<<pointer->getName()<<endl;
            dennis.x += pointer->_position.x;
            dennis.y += pointer->_position.y;
            //dennis.x += pointer->getPosition().x;
            //dennis.y += pointer->getPosition().y; 
            pointer = pointer->_parent;
        }
        return dennis;
    }
    /*
    if(this->_parent == nullptr){
        return _position;
    }
    
    else{
        Pair dennis, young;
        dennis.x = _position.x;
        dennis.y = _position.y;
        while (pointer != nullptr){
            //cout<<pointer->getName()<<endl;
            young = pointer->getPosition();
            dennis.x += young.x;
            dennis.y += young.y;
            //dennis.x += pointer->getPosition().x;
            //dennis.y += pointer->getPosition().y; 
            pointer = pointer->_parent;
        }

        return dennis;
    }
    */
    
    
    
    
}

const char* Object::getName() const
{
    return _name;
}

void Object::setSize(int x, int y)  //Task 3
{
    if (x < 0 || y < 0 || x > SCREEN_RESOLUTION.x || y > SCREEN_RESOLUTION.y ){
        cout<< "Invalid size of "<<this->getName();
        cout<<"\n";
    }
    else
    {
        _size.x = x;   
        _size.y = y;
    }

}

void Object::setPosition(int x, int y)  //Task 3
{
    // x is out of bounds horizontally 
    // cout<<"Input x:"<<x<<"Input y: "<<y;
    // cout<<"\n"<<endl;

    if (x > SCREEN_RESOLUTION.x || y > SCREEN_RESOLUTION.y || x < 0 || y < 0){
        cout<< "Invalid position of "<<this->getName();
        cout<<"\n";
    }
    else{
        //this->getPosition();
        //this->_position.x = this->getPosition().x + x;
        this->_position.x = x;
        this->_position.y = y;
        //cout<<"Set pos x"; 
    }
    
}

void Object::setName(const char*name)
{
    for(int i = 0;i<MAX_NAME_LENGTH; i++)
    {
        _name[i] = name[i];
        if(name[i]=='\0') break;
    }
}

void Object::setParent(Object* parent)
{
    _parent = parent;
}

void Object::displayBasic() const
{
    cout << "\n\tName: ["<< getName()<<"]"; 
    cout <<"\n\tPosition: ("<< getPosition().x << ", "<< getPosition().y<<")";
    cout <<"\n\tSize: (" <<  getSize().x << ", "<< getSize().y<<") ";
}

Object::Object() : _size{0,0}, _position{0,0}, _parent{nullptr}
{
    _name = new char[MAX_NAME_LENGTH];
    _name[0]='\0';
}

Object::~Object()
{
    if (_name != nullptr) 
        delete [] _name;
}