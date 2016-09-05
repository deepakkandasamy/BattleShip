#ifndef BOAT_H_INCLUDED
#define BOAT_H_INCLUDED
#include <cmath>
using namespace std;
#include "Block.h"
class Boat {
private:
	GameConfig::BoatType type;
	Block startBlock;
	Block endBlock;
	int boatLife;
    friend class Board;
    friend class Controller;
    Boat(){};
	void setBoat(GameConfig::BoatType type, Block startBlock, Block endBlock) {
		this->type = type;
		this->startBlock = startBlock;
		this->endBlock = endBlock;
	}

	int getBoatSizeBlock(){
		if(this->startBlock.getX() == this->endBlock.getX()){
			return int(abs(double(this->startBlock.getY() - this->endBlock.getY()))) + 1;
		}
		else{
			return int(abs(double(this->startBlock.getX() - this->endBlock.getX()))) + 1 ;
		}
	}

	bool isBoatAttacked(Block block) {
		if(block.getX() >= startBlock.getX() && block.getX() <= endBlock.getX() &&
				block.getY() >= startBlock.getY() && block.getY() <= endBlock.getY()){
			return true;
		}
		return false;
	}

	bool isBlockInBoat(Block block){
		if(block.getX() >= startBlock.getX() && block.getX() <= endBlock.getX() &&
				block.getY() >= startBlock.getY() && block.getY() <= endBlock.getY()){
			return true;
		}
		return false;
	}

	void decrementBoatLife(){
		boatLife--;
	}

	void setBoatLife(int boatLife) {
		this->boatLife = boatLife;
	}

	bool isDestoyed(){
		if(boatLife == 0){
			return true;
		}

		return false;
	}

public:
    Block getStartBlock() {
		return startBlock;
	}

	Block getEndBlock(){
		return endBlock;
	}

	void setStartBlock(Block startBlock) {
		this->startBlock = startBlock;
	}

	void setEndBlock(Block endBlock) {
		this->endBlock = endBlock;
	}
};


#endif // BOAT_H_INCLUDED
