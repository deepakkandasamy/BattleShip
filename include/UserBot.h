#ifndef USERBOT_H_INCLUDED
#define USERBOT_H_INCLUDED
#include <cstdlib>
#include <ctime>
#include<stack>
using namespace std;
#include "Bot.h"

class UserBot: public Bot{
    public:
    int prevx,prevy,pPrevx,pPrevy;
    int up,down,left,right;
    int direction,minsize;
    int numBoatsDestroyed;
    bool prevState[5];
    int hitCount;
    stack <pair<int,int> > st;
    pair<int, int> stackpoint;
    vector<vector<int> > boardTraversed;
	UserBot():boardTraversed(GameConfig::ROWS,vector<int>(GameConfig::COLUMNS,-1)){
	hitCount=0;
	numBoatsDestroyed=0;
	up=down=left=right=0;
	minsize=2;
	direction=0;
    }
    UserBot(UserBot const &uc){}
    Block makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]);
    Boat* positionBoats(Boat boats[]);
};



#endif // USERBOT_H_INCLUDED
