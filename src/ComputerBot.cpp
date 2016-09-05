#include "ComputerBot.h"
Block ComputerBot::makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]){
    int x = rand()%GameConfig::ROWS;
    int y = rand()%GameConfig::COLUMNS;
    return Block(x,y);
}

Boat* ComputerBot::positionBoats(Boat boats[]) {
    for(int i = 0; i<GameConfig::NBOATS;i++){
        //set boat blocks
    }
    return boats;
}
