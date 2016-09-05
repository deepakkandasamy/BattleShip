#ifndef GAMECONFIG_H_INCLUDED
#define GAMECONFIG_H_INCLUDED
#include <iostream>
using namespace std;
class GameConfig{
    public:
        static const int ROWS = 10;
        static const int COLUMNS = 10;
        static const int NBOATS = 5;
        enum BlockStatus{
            UNTOUCHED,
            BLASTED,
            NOT_BLASTED,
            VISITED
        };
        enum BoatType{
            BATTLESHIP,
            SUBMARINE,
            AIRCRAFT,
            DESTROYER,
            PATROL
        };
        enum MoveStatus{
            HIT,
            MISS,
            INVALID
        };
        static const int USERBOT = 1;
        static const int COMPUTERBOT = 2;

        static const int BATTLESHIP_SIZE = 5;
        static const int AIRCRAFT_SIZE = 4;
        static const int SUBMARINE_SIZE = 3;
        static const int DESTROYER_SIZE = 3;
        static const int PATROL_SIZE = 2;
};
#endif // GAMECONFIG_H_INCLUDED
