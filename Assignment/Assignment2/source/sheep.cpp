#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 3
 * 
 * Place a copy of this Sheep onto nextGrid at the specified position.
 * You may implement this similar to Grass::putSelf(), and call setNextSelf() accordingly.
 * Hint: putAnimal() can be used.
*/
void Sheep::putSelf(Grid* nextGrid, const int x, const int y) {
    //std:: cout<<"Debugging message: Sheep putSelf called\n";
    Sheep* new_sheep = new Sheep(*this);

    if (putAnimal(new_sheep, nextGrid, x, y)==true){
        //std::cout<<"Debugging message: Sheep putAnimal\n";
        Entity:: setNextSelf(new_sheep);
    }
    
}

/**
 * TODO: TASK 3
 * 
 * Place a brand new Sheep onto nextGrid at the specified position.
 * You may implement this similar to Grass::putClone().
 * Hint: putAnimal() can be used.
*/
void Sheep::putClone(Grid* nextGrid, const int x, const int y) const {
    //std:: cout<<"Debugging message: Sheep putClone called\n";
    Sheep* new_sheep = new Sheep(this->getBoard());

    putAnimal(new_sheep, nextGrid,x,y);
}

/**
 * TODO: TASK 3
 * 
 * Check if any adjacent cell of current Grid points to Grass.
 * If a Grass is found and has not been removed, destroy it using removeSelf(),
 * and reset the hungerCounter to full.
 * Exit from the function since a Sheep can only eat at most once per turn.
 * 
 * The code has been partially completed so that adjacent cells are checked in the order of adjacency index.
*/
void Sheep::eat(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        //Grass* new_grassy = dynamic_cast<Grass*>(adjEntity);

        if ((adjEntity)){
            //Grass* new_grassy = dynamic_cast<Grass*>(adjEntity);
            //Sheep* new_sheepy = dynamic_cast<Sheep*>(adjEntity);
            ////if (new_grassy == nullptr){std::cout<<"Hello World\n";} // error message
            
            //char s [] = "5Sheep";
            //char g [] = "5Grass";
            //char w [] = "4Wolf";
            /*
            if(strcmp(w,typeid(*adjEntity).name())==0){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                continue;
            }

            if(strcmp(s,typeid(*adjEntity).name())==0){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                continue;
            }
            */
            

            //if(strcmp(g,typeid(*adjEntity).name())==0){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                //std::cout<<"Found Grass! \n";
                if(dynamic_cast<Grass*>(adjEntity)){
                //if(typeid(*adjEntity) == typeid(Grass)){
                    //std::cout<<"Hello World\n";
                
                adjEntity->removeSelf(nextGrid);
                //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") eats Grass at ("<<adjEntity->getX()<<","<<adjEntity->getY()<<")\n";
                setHungerCounter(getHungerCooldown());
                return;}
            //}
            
        }
        // ?
        //std:: cout<<"Debugging message: Sheep eat called\n";
        
    }
    //putSelf(nextGrid,this->getX(),this->getY());
}

/**
 * TODO: TASK 3
 * 
 * Check if any adjacent cell of current Grid points to Sheep.
 * If a Sheep is found, try to spawn a new Sheep on an adjacent cell.
 * You can use the getRandomMovementIndex() function to get an available adjacent cell.
 * If a cell is found, spawn a new Sheep at that position and reset the breedCounter to full.
 * Exit from the function since a Sheep can only breed at most once per turn.
 * 
 * The code has been partially completed so that adjacent cells are checked in the order of adjacency index.
*/
void Sheep::breed(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
        //std:: cout<<"Debugging message: Sheep breed called\n";
        if (adjEntity){
            /*
            char s [] = "5Sheep";
            char g [] = "5Grass";
            char w [] = "4Wolf";
            if(strcmp(w,typeid(*adjEntity).name())==0){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                continue;
            }

            if(strcmp(g,typeid(*adjEntity).name())==0){
                continue;
            }
            */
            

            //if(strcmp(s,typeid(*adjEntity).name())==0){
                if(dynamic_cast<Sheep*>(adjEntity)){
                   //std::cout<<"Hello World\n";
                //if(typeid(*adjEntity) == typeid(Sheep)){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                //adjEntity->removeSelf(nextGrid);
                //std::cout<<"Hello World\n";
                int x = getRandomMovementIndex(nextGrid);
                switch(x) {
                    case 0:
                        // code block
                        putClone(nextGrid,this->getX()-1,this->getY()-1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 1:
                        // code block
                        putClone(nextGrid,this->getX()-1,this->getY());
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 2:
                        // code block
                        putClone(nextGrid,this->getX()-1,this->getY()+1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 3:
                        // code block
                        putClone(nextGrid,this->getX(),this->getY()-1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 5:
                        // code block
                        putClone(nextGrid,this->getX(),this->getY()+1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 6:
                        // code block
                        putClone(nextGrid,this->getX()+1,this->getY()-1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 7:
                        // code block
                        putClone(nextGrid,this->getX()+1,this->getY());
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    case 8:
                        // code block
                        putClone(nextGrid,this->getX()+1,this->getY()+1);
                        //std::cout<<"Spawn sheep!\n";
                        break;
                    default:
                        // code block
                        std::cout<<"Error!\n";
                }
                setBreedCounter(getBreedCooldown());
                return;
            }
            //}

            
            
        }
    }
}

/**
 * TODO: TASK 3
 * 
 * Get a random available adjacent cell to move to using getRandomMovementIndex().
 * If there is an adjacent cell, place the copy of this Sheep there.
 * Otherwise, place it in the current position.
*/
void Sheep::move(Grid* nextGrid) {
    //std:: cout<<"Debugging message: Sheep move called\n";
    int x = getRandomMovementIndex(nextGrid);
    switch(x) {
        case 0:
            // code block
            putSelf(nextGrid,this->getX()-1,this->getY()-1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()-1<<","<<this->getY()-1<<")\n";
            break;
        case 1:
            // code block
            putSelf(nextGrid,this->getX()-1,this->getY());
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()-1<<","<<this->getY()<<")\n";
            break;
        case 2:
            // code block
            putSelf(nextGrid,this->getX()-1,this->getY()+1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()-1<<","<<this->getY()+1<<")\n";
            break;
        case 3:
            // code block
            putSelf(nextGrid,this->getX(),this->getY()-1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()<<","<<this->getY()-1<<")\n";
            break;
        case 5:
            // code block
            putSelf(nextGrid,this->getX(),this->getY()+1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()<<","<<this->getY()+1<<")\n";
            break;
        case 6:
            // code block
            putSelf(nextGrid,this->getX()+1,this->getY()-1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()+1<<","<<this->getY()-1<<")\n";
            break;
        case 7:
            // code block
            putSelf(nextGrid,this->getX()+1,this->getY());
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()+1<<","<<this->getY()<<")\n";
            break;
        case 8:
            // code block
            putSelf(nextGrid,this->getX()+1,this->getY()+1);
            //std::cout<<"Moved sheep!\n";
            //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") moves to ("<<this->getX()+1<<","<<this->getY()+1<<")\n";
            break;
        default:
            // code block
            std::cout<<"Error!\n";
            return;
            putSelf(nextGrid,this->getX(),this->getY());
    }

    //setMoveCounter(getBreedCooldown());
    return;
}