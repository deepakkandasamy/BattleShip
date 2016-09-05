#include "Block.h"
int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}

GameConfig::BlockStatus Block::getStatus() {
    return status;
}

void Block::setStatus(GameConfig::BlockStatus newStatus) {
    this->status = newStatus;
}

bool Block::isBlasted() {
    if(status == GameConfig::BLASTED)
        return true;
    return false;
}

void Block::setBlock(int x, int y){
    this->x = x;
    this->y = y;
}

Block::Block(int x, int y){
    this->x = x;
    this->y = y;
    this->status = GameConfig::UNTOUCHED; // initially no block is touched
}

Block::Block(Block const &B) {
    this->x = B.x;
    this->y = B.y;
    this->status = B.status;
}

Block::Block(){
    this->status = GameConfig::UNTOUCHED;
}
