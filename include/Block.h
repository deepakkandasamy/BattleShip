#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "GameConfig.h"
class Block {
private:
    int x;
	int y;
	GameConfig::BlockStatus status;
public:
	int getX();
	int getY();
	GameConfig::BlockStatus getStatus();
	void setStatus(GameConfig::BlockStatus newStatus);
	bool isBlasted();
	void setBlock(int x, int y);
	Block(int x, int y);
	Block(Block const &B);
	Block();
};


#endif // BLOCK_H_INCLUDED
