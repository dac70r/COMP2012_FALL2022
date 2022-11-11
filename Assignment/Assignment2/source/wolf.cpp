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
                    //std::cout<<"Hello Sheep\n";
                
                adjEntity->removeSelf(nextGrid);
                //std::cout<<"Sheep at ("<<this->getX()<<","<<this->getY()<<") eats Grass at ("<<adjEntity->getX()<<","<<adjEntity->getY()<<")\n";
                setHungerCounter(getHungerCooldown());
                return;
            }
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
            //std::cout<<"Hello Wolf\n";
        //if(typeid(*adjEntity) == typeid(Wolf)){
                //std::cout<<"Found "<<typeid(*adjEntity).name()<<"\n";
                //adjEntity->removeSelf(nextGrid);
                //std::cout<<"Breeding Wolf\n";
                //std::cout<<"Hello Wolf\n";
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
    //std::cout<<this->getX()<<" ";
    //std::cout<<this->getY()<<" this \n";
    //std::cout<<"All wolves move\n";
    double shortest_distance_squared = 0;
    double current_distance_squared = 0;
    int shortest_sheep_x = 0;
    int shortest_sheep_y = 0;

    Grid* this_grid = this->getBoard()->getGrid();

    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {
            Entity* new_entity = this_grid->getCell(x,y);
            /*
            if(dynamic_cast<Sheep*>(new_entity)){
                std::cout<<"Found Sheep at ("<<new_entity->getX()<<","<<new_entity->getY()<<")\n";
            }*/
            
            // ?
            
            double wolf_x = this->getX();
            double wolf_y = this->getY();
            
            //if (new_entity!= nullptr){
            //    std::cout<<x<<"\n";
            //   std::cout<<y<<"\n";
            //}

            //std::cout<<"We are not at ("<<x<<","<<y<<") and it is "<<new_entity<<"\n";
            
            if(dynamic_cast<Sheep*>(new_entity)){
                // debugging message 
                //std::cout<<"Wolf is currently at ("<<this->getX()<<","<<this->getY()<<")\n";
                //std::cout<<"Found Sheep at ("<<new_entity->getX()<<","<<new_entity->getY()<<")\n";
                double new_entity_x = new_entity->getX();
                double new_entity_y = new_entity->getY();
                double euclidean_x = (wolf_x - new_entity_x) * (wolf_x - new_entity_x);
                double euclidean_y = (wolf_y - new_entity_y) * (wolf_y - new_entity_y);
                current_distance_squared = (euclidean_x + euclidean_y);
                if (shortest_distance_squared == 0){
                    shortest_distance_squared = current_distance_squared;
                    //std::cout<<"Shortest distance: "<<shortest_distance_squared<<"\n";
                    shortest_sheep_x = new_entity->getX();
                    shortest_sheep_y = new_entity->getY();
                }
                if(current_distance_squared<shortest_distance_squared){
                    shortest_distance_squared = current_distance_squared;
                    shortest_sheep_x = new_entity->getX();
                    shortest_sheep_y = new_entity->getY();
                }   
            }
            
            
        }
    }
    //std::cout<<"Shortest Distance Squared :"<<shortest_distance_squared<<"\n";
    if (shortest_distance_squared) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        //shortest_distance_squared = current_distance_squared;
        
        // ?
        int new_x = 0;
        int new_y =0;
        if(shortest_sheep_x>this->getX()){
            new_x = this->getX()+1;
        }
        if (shortest_sheep_x<this->getX()){
            new_x = this->getX()-1;
        }
        if(shortest_sheep_y>this->getY()){
            new_y = this->getY()+1;
        }
        if(shortest_sheep_y<this->getY()){
            new_y = this->getY()-1;
        }
        this->putSelf(nextGrid,new_x,new_y);
        return;
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