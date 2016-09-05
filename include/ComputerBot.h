#ifndef COMPUTERBOT_H_INCLUDED
#define COMPUTERBOT_H_INCLUDED
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Bot.h"

class ComputerBot: public Bot{
    public:
    ComputerBot(){}
    ComputerBot(ComputerBot const &cb){}
	Block makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]);
	Boat* positionBoats(Boat boats[]);
};



#endif // COMPUTERBOT_H_INCLUDED
