#include "grass.h"
#include "helper.h"
#include <iostream>

/**
 * TODO: TASK 1
 * 
 * This function tries to set nextGrid's cell at position x, y to point to grass,
 * and returns a boolean of whether grass was placed successfully on nextGrid.
 * 
 * If the position is out of bounds or the cell is already pointing at another Entity,
 * grass should be deleted and the function returns false.
 * Otherwise, modify nextGrid accordingly and return true.
*/
bool putGrass(Grass* grass, Grid* nextGrid, const int x, const int y) {

    // If there is something in the cell (!= nullptr)
    // delete grass 
    // this function already checks for outofBounds
    // if out of bounds then return nullptr
    //std::cout<<"Hello World 1";
    if (nextGrid->getCell(x,y) != nullptr){
        delete grass;
        return false;
    }
    
    else{
        nextGrid->setCell(grass,x,y);
        return true;
    }  
    
}

/**
 * TODO: TASK 1
 * 
 * Place a copy of this Grass onto nextGrid at the specified position.
 * 
 * You should use the copy constructor to create a Grass object representing this Grass in the next step.
 * You may use putGrass() implemented above. If the copy was placed successfully, call setNextSelf()
 * to properly link this Grass with the copy for deletion if necessary.
*/
void Grass::putSelf(Grid* nextGrid, const int x, const int y) {
    //std::cout<<"Hello World 2";
    Grass* new_grass = new Grass(*this);
    //putGrass(new_grass,nextGrid,x,y);
    if (putGrass(new_grass, nextGrid, x, y)==true){
        
        Entity::setNextSelf(new_grass);
    }
    //Grass* copy_grass = Grass(*this);
    //putGrass(copy_grass,nextG
    
}

/**
 * TODO: TASK 1
 * 
 * Place a brand new Grass onto nextGrid at the specified position.
 * 
 * You should use the normal constructor to create a new Grass object.
 * You may use putGrass() implemented above.
*/
void Grass::putClone(Grid* nextGrid, const int x, const int y) const {
    //std::cout<<"Hello World 3";
    Grass* new_grass = new Grass(this->getBoard());
    //std::cout<<"Hello World 3.1";
    //nextGrid->setCell(new_grass,x,y);
    putGrass(new_grass,nextGrid,x,y);
    //std::cout<<"Hello World 3.2\n";
}

/**
 * TODO: TASK 1
 * 
 * Update the nextGrid according to the update rules of Grass. 
 * If the spread countdown is reached, spawn 4 Grasses onto the orthogonally adjacent tiles using putClone().
 * You may find the countdown() function in helper.cpp useful.
 * Otherwise, put a copy of this Grass onto this position using putSelf(). You don't need to worry about
 * checking if current cell has another Entity; it is done in putGrass().
*/
void Grass::update(Grid* nextGrid) {

   // this->getBoard()->print();
    bool countdownReached = countdown(spreadCounter, SPREAD_COOLDOWN);
    if (countdownReached) {
        // code that is executed once every COOLDOWN steps
        //std::cout<<"Hello World";
        //std::cout<<this->getX()<<"\n";
        //std::cout<<this->getY()<<"\n";
        int x_cor = this->getX();
        int y_cor = this->getY();
        putSelf(nextGrid,this->getX(),this->getY());
        putClone(nextGrid,x_cor+1,y_cor);
        putClone(nextGrid,x_cor-1,y_cor);
        putClone(nextGrid,x_cor,y_cor+1);
        putClone(nextGrid,x_cor,y_cor-1);
    }
    else {
        // code to be executed during "cooldown" steps
        //std::cout<<"Hello World 2";
        putSelf(nextGrid,this->getX(),this->getY());
    }
    //if(countdown(x,SPREAD_COOLDOWN)==true){
        //std::cout<<"Hello World YOLO\n";
        
        //putClone(nextGrid,this->getX(),this->getY());
        //putClone(nextGrid,this->getX(),this->getY()+1);
        //putClone(nextGrid,this->getX(),this->getY()-1);
        //if(nextGrid->getCell(this->getX(),this->getY())==nullptr){
        //    std::cout<<"NULL";
        //}
        //else
        //    std::cout<<"Got something here";
        //putClone(nextGrid,this->getX()+1,this->getY());
        //x++;
    //}
   //else
        //std::cout<<"Hello World 5";
}