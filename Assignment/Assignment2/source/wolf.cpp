#include "wolf.h"
#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 4
 * 
 * Place a copy of this Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putSelf().
*/
void Wolf::putSelf(Grid* nextGrid, const int x, const int y) {

    Wolf* new_wolf = new Wolf(*this);

    if (putAnimal(new_wolf, nextGrid, x, y)==true){
        //std::cout<<"Debugging message: Sheep putAnimal\n";
        Entity:: setNextSelf(new_wolf);
    }
    
}

/**
 * TODO: TASK 4
 * 
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
*/
void Wolf::putClone(Grid* nextGrid, const int x, const int y) const {
    //std:: cout<<"Debugging message: Sheep putClone called\n";
    Wolf* new_wolf = new Wolf(this->getBoard());

    putAnimal(new_wolf, nextGrid,x,y);
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::eat().
 * The only difference is that Wolf eats Sheep instead of Grass.
*/
void Wolf::eat(Grid* nextGrid) {
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
        if ((adjEntity)){
                //if(typeid(*adjEntity) == typeid(Sheep)){
                if(dynamic_cast<Sheep*>(adjEntity)){
                    //std::cout<<"Hello World\n";
                
                adjEntity->removeSelf(nextGrid);
                //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") eats Grass at ("<<adjEntity->getX()<<","<<adjEntity->getY()<<")\n";
                setHungerCounter(getHungerCooldown());
                return;}
            //}
            
        }
    }
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::breed().
 * The only difference is that Wolf breeds by finding a Wolf instead of Sheep.
*/
void Wolf::breed(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        //std::cout<<getX();
        //std::cout<<getY();
        //std::cout<<getAdjX(i);
        //std::cout<<getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
        if(dynamic_cast<Wolf*>(adjEntity)){
        //if(typeid(*adjEntity) == typeid(Wolf)){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                //adjEntity->removeSelf(nextGrid);
                //std::cout<<"Breeding Wolf\n";
                int x = getRandomMovementIndex(nextGrid);
                if (x>=0){
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
                        //std::cout<<"Error!\n";
                        return;     
                    }
                }
                setBreedCounter(getBreedCooldown());
                return;
            }
    }
}

/**
 * TODO: TASK 4
 * 
 * If there is at least one Sheep on the board, Wolf tries to move towards it.
 * 
 * You should loop over the board in the same order as Board calling update(), 
 * calculate Euclidean distance to each cell containing a Sheep, and keep track of the shortest distance found.
 * Ignore sheeps that have been eaten (removed).
 * No need to keep track of Sheeps with the same distance as shortest one found so far.
 * 
 * If a Sheep is found, move to the adjacent cell closest to that Sheep. If that cell is occupied with another Animal,
 * the Wolf stays at its position.
 * 
 * If no Sheep is found, the Wolf moves randomly like a Sheep.
 * 
 * You may follow the structure below to implement the function.
*/
void Wolf::move(Grid* nextGrid) {
    // First, find a sheep to target
    
    // ? 
    int shortest_distance = 0;
    
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {

            // ?
            
            Entity* new_entity = nextGrid->getCell(x,y);


        }
    }

    if (false) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        
        // ?
    }
    else {
        // No sheep found, move randomly
        int x = getRandomMovementIndex(nextGrid);
        if(x>=0){
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
            return;
            //std::cout<<"Error!\n";
            //putSelf(nextGrid,this->getX(),this->getY());
            }
        }
        
    }
    //setMoveCounter(getBreedCooldown());
    //std:: cout<<"Debugging message: Sheep move called\n";
}