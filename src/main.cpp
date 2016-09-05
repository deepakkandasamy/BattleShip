#include <iostream>
using namespace std;
#include "Controller.h"
int main()
{
    UserBot *ub = new UserBot();
    ComputerBot *cb = new ComputerBot();
    Controller *gameC = new Controller(ub,cb);
    gameC->start();

}

