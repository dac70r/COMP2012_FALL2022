#include "grass.h"
#include "helper.h"

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
    
    return false;
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
    
}