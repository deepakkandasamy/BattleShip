#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include <vector>
#include <fstream>
using namespace std;
#include "ComputerBot.h"
#include "UserBot.h"
struct Detail{
    int startRow;
    int startColumn;
    int endRow;
    int endColumn;
    int boat;
};
struct Move{
    string player;
    int row;
    int column;
    int hit;
};
void writeToJSON(string winner);
class Controller {

	UserBot *userBot;
	ComputerBot *computerBot;
	int currentTurn;
public:
    Controller(UserBot*,ComputerBot*);

	int getBoatSize(Boat boat);

	bool validateBoatPosition(Boat boats[]);

	void start();

	/*
	 * The below function provides the default positioning of the boats in a board
	 * To be changed later
	 */
	void initialBoatArrangement(Boat boats[]);

	int declareWinner(Board *userBoard, Board *computerBoard);

	/*
	 * The below function keeps the game continuing until any one of the board has lost its ships
	 */
	void play(Board *userBoard, Board *computerBoard);

	void makeMove(Board *userBoard, Board *computerBoard);
};



#endif // CONTROLLER_H_INCLUDED
