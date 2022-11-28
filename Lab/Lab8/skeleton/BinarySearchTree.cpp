#include "BinarySearchTree.h"

#include <algorithm>
#include <iostream>

BinarySearchTree::BinarySearchTree(int value)
    : value(value), leftSubTree(nullptr), rightSubTree(nullptr) {}

BinarySearchTree::~BinarySearchTree()
{
    if (leftSubTree != nullptr)
        delete leftSubTree;
    if (rightSubTree != nullptr)
        delete rightSubTree;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other): value(other.value)
{
    if (other.leftSubTree != nullptr)
        leftSubTree = new BinarySearchTree(*other.leftSubTree);
    if (other.rightSubTree != nullptr)
        rightSubTree = new BinarySearchTree(*other.rightSubTree);
}

void BinarySearchTree::add(int newValue)
{
    if (newValue < value)
    {
        //std::cout<<"New value < value: "<<newValue<<" "<<value<<"\n";
        if (leftSubTree != nullptr)
            leftSubTree->add(newValue);
        else
            leftSubTree = new BinarySearchTree(newValue);
    }
    else if (newValue > value)
    {
        //std::cout<<"New value > value: "<<newValue<<" "<<value<<"\n";
        if (rightSubTree != nullptr)
            rightSubTree->add(newValue);
        else
            rightSubTree = new BinarySearchTree(newValue);
    }
}

bool BinarySearchTree::hasValue(int valueToFind) const
{
    if (valueToFind == value)
        return true;
    if (valueToFind < value && leftSubTree != nullptr)
        return leftSubTree->hasValue(valueToFind);
    if (valueToFind > value && rightSubTree != nullptr)
        return rightSubTree->hasValue(valueToFind);
    return false;
}

void BinarySearchTree::print(int depth=0) const
{
    if(this == nullptr)
        return;
    rightSubTree->print(depth+1);
    for (int j = 0; j < depth; j++) // Print the node value
        std::cout << '\t';
    std::cout << value << std::endl;
    
    leftSubTree->print(depth+1); // Recursion: left sub-tree

}


//Task 1
bool BinarySearchTree::isSame(const BinarySearchTree* other)
{
    if (this == nullptr && other == nullptr){
        //std::cout<<"Debug 1\n";
        return 1;
    }

    else if (this == nullptr || other == nullptr){
        //std::cout<<"Debug 2\n";
        return 0;
    }

    else{

        if ( this->value == other->value && this->leftSubTree->isSame(other->leftSubTree) && this->rightSubTree->isSame(other->rightSubTree)){
            //std::cout<<"Debug 3\n";
            return 1;
        }
        else{
            //std::cout<<"Debug 4\n";
            return 0;
        }
    }
    
}

//Entry of task2
void BinarySearchTree::buildNewBST(BinarySearchTree* newBST, int newValue)
{
    if (!this->hasValue(newValue))
    {
        std::cout << "Invalid value!" << std::endl;
    }
    newBST->value = newValue;      
        // Hint: as the add function will ignore the existing nodes, 
        // you do not neet to consider the ruplicate "newValue" in the newBST  
    this->traverseAdd(newBST);
}

//Task 2
void BinarySearchTree::traverseAdd(BinarySearchTree* newBST)
{
    //if(this){
    //    newBST->add(this->value);
    //}

    if(this){
        this->leftSubTree->traverseAdd(newBST);
        newBST->add(this->value);
        this->rightSubTree->traverseAdd(newBST);
    }
    
}

/*
if(newBST){
    if(this->value < newBST->value){
        newBST->leftSubTree = new BinarySearchTree(this->value);
    }

    if(this->value > newBST->value){
        newBST->rightSubTree = new BinarySearchTree(this->value); 
    }
    }

if(newBST->value < this->value){
        newBST->rightSubTree = new BinarySearchTree(this->value); 
        std::cout<<"This -> rightSubTree -> value: "<<this->rightSubTree->value<<"\n";
        this->rightSubTree->traverseAdd(newBST->rightSubTree);
    }

    if(newBST->value > this->value){
        newBST->leftSubTree = new BinarySearchTree(this->value); 
        std::cout<<"This -> leftSubTree -> value: "<<this->leftSubTree->value<<"\n";
        this->leftSubTree->traverseAdd(newBST->leftSubTree);
    }
    */