#include "Controller.h"

vector<Detail> userdetails,compdetails;
vector<Move> moves;
void writeToJSON(string winner){
    cout << "{" << endl;
    cout << "\t\"details\" : {" << endl;
    cout << "\t\t\t\"UserBoats\" : [" << endl;
    for(unsigned int i = 0 ; i < userdetails.size(); i++){
        cout << "\t\t\t{" << endl;
        cout << "\t\t\t\t\"startRow\" : \"" << userdetails[i].startRow << "\","<< endl;
        cout << "\t\t\t\t\"startColumn\" : \"" << userdetails[i].startColumn << "\","<< endl;
        cout << "\t\t\t\t\"endRow\" : \"" << userdetails[i].endRow << "\","<< endl;
        cout << "\t\t\t\t\"endColumn\" : \"" << userdetails[i].endColumn << "\","<< endl;
        cout << "\t\t\t\t\"Boat\" : \"" << userdetails[i].boat << "\""<< endl;
        cout << "\t\t\t}";
        if(i != userdetails.size() - 1)
            cout << "," << endl;
        else
            cout << endl;
    }
    cout << "\t\t]," << endl;
    cout << "\t\t\"ComputerBoats\" : [" << endl;
    for(unsigned int i = 0 ; i < userdetails.size(); i++){
        cout << "\t\t\t{" << endl;
        cout << "\t\t\t\t\"startRow\" : \"" << compdetails[i].startRow << "\","<< endl;
        cout << "\t\t\t\t\"startColumn\" : \"" << compdetails[i].startColumn << "\","<< endl;
        cout << "\t\t\t\t\"endRow\" : \"" << compdetails[i].endRow << "\","<< endl;
        cout << "\t\t\t\t\"endColumn\" : \"" << compdetails[i].endColumn << "\","<< endl;
        cout << "\t\t\t\t\"Boat\" : \"" << compdetails[i].boat << "\""<< endl;
        cout << "\t\t\t}";
        if(i != compdetails.size() - 1)
            cout << "," << endl;
        else
            cout << endl;
    }
    cout << "\t\t]" << endl;
    cout << "\t}," << endl;
    cout << "\t\"moves\" : [" << endl;
    for(unsigned int i = 0; i < moves.size(); i++){
        cout << "\t\t{" << endl;
        cout << "\t\t\t\"player\" : \"" << moves[i].player << "\"," << endl;
        cout << "\t\t\t\"row\" : \"" << moves[i].row << "\"," << endl;
        cout << "\t\t\t\"column\" : \"" << moves[i].column << "\"," << endl;
        cout << "\t\t\t\"hit\" : " << moves[i].hit << endl;
        cout << "\t\t}";
        if(i != moves.size() - 1)
            cout << "," << endl;
        else
            cout << endl;
    }
    cout << "\t]" << endl;
    cout << "}";
}
Controller::Controller(UserBot *ub,ComputerBot *cb) {
    userBot = ub;
    computerBot = cb;
    srand(time(NULL));
}

int Controller::getBoatSize(Boat boat) {

    switch(boat.type){
    case GameConfig::AIRCRAFT:
        return GameConfig::AIRCRAFT_SIZE;

    case GameConfig::BATTLESHIP:
        return GameConfig::BATTLESHIP_SIZE;

    case GameConfig::DESTROYER:
        return GameConfig::DESTROYER_SIZE;

    case GameConfig::PATROL:
        return GameConfig::PATROL_SIZE;

    case GameConfig::SUBMARINE:
        return GameConfig::SUBMARINE_SIZE;
    }
    return -1;
}

bool Controller::validateBoatPosition(Boat boats[]) {
    if(GameConfig::NBOATS != GameConfig::NBOATS) {
        return false;
    }

    // Validating each boat is placed only once...

    vector<GameConfig::BoatType> allBoatTypes;

    for(int i=0;i<GameConfig::NBOATS;i++){
        for(unsigned int j = 0; j < allBoatTypes.size(); j++)
            if(allBoatTypes[j] == boats[i].type){
                return false;
        }
        allBoatTypes.push_back(boats[i].type);
    }

    for(int i=0;i<GameConfig::NBOATS;i++){
        // Validating horizontal constraint or vertical constraint...
        //cout << boats[i].getStartBlock().getX() << " " << boats[i].getEndBlock().getX() << " " << boats[i].getStartBlock().getY() << " " << boats[i].getEndBlock().getY() << endl;
        if(!((boats[i].getStartBlock().getX() == boats[i].getEndBlock().getX() ) || (boats[i].getStartBlock().getY() == boats[i].getEndBlock().getY()))){
            //cout << "Diagonal Constraint" << endl;
            return false;

        }

        // Validating size...
        if(!(getBoatSize(boats[i]) == boats[i].getBoatSizeBlock())){

            //cout << "Size " << boats[i].getBoatSizeBlock() <<  getBoatSize(boats[i]) << endl;
            return false;
        }
    }

    // overlaping boat...

    for(int row = 0 ; row<GameConfig::ROWS;row++){
        for(int column =0; column<GameConfig::COLUMNS;column++){
            bool flag=false;
            for(int iBoat =0; iBoat < GameConfig::NBOATS ;iBoat++){
                if(boats[iBoat].isBlockInBoat(Block(row,column))){
                    if(flag== false){
                        flag = true;
                    }
                    else{
                        //cout << "Overlapping" << endl;
                        return false;
                    }
                }
            }
        }
    }




    return true;
}


void Controller::start(){

    Board *userBoard = new Board();
    Board *computerBoard = new Board();

    Boat userBoats[GameConfig::NBOATS];
    initialBoatArrangement(userBoats);
    userBot->positionBoats(userBoats);

    if(validateBoatPosition(userBoats)){
        userBoard->placeBoats(userBoats);
        Detail detail;
        for(int i=0;i<GameConfig::NBOATS;i++){
            detail.startRow = userBoats[i].startBlock.getX();
            detail.startColumn = userBoats[i].startBlock.getY();
            detail.endRow = userBoats[i].endBlock.getX();
            detail.endColumn = userBoats[i].endBlock.getY();
            detail.boat = i;
            userdetails.push_back(detail);
        }
    }
    else {
        //cout << "not valid positioning" << endl;
        return;
    }
    Boat computerBoats[GameConfig::NBOATS];
    initialBoatArrangement(computerBoats);
    computerBot->positionBoats(computerBoats);
    if(validateBoatPosition(computerBoats)){
        computerBoard->placeBoats(computerBoats);
        Detail detail;
        for(int i=0;i<GameConfig::NBOATS;i++){
            detail.startRow = computerBoats[i].startBlock.getX();
            detail.startColumn = computerBoats[i].startBlock.getY();
            detail.endRow = computerBoats[i].endBlock.getX();
            detail.endColumn = computerBoats[i].endBlock.getY();
            detail.boat = i;
            compdetails.push_back(detail);
        }
    }
    else {
        //cout << "Not valid positioning" << endl;
        return;
    }
    srand(time(NULL));
    int x = rand()%2;
    currentTurn = x+1;

    play(userBoard,computerBoard);

    int winner = declareWinner(userBoard, computerBoard);
    if(winner == GameConfig::USERBOT)
        writeToJSON("UserBot");
    else if(winner == GameConfig::COMPUTERBOT)
        writeToJSON("CompBot");

}

/*
 * The below function provides the default positioning of the boats in a board
 * To be changed later
 */
void Controller::initialBoatArrangement(Boat boats[]) {
    boats[0].setBoat(GameConfig::AIRCRAFT,Block(5,2),Block(5,5));
    boats[1].setBoat(GameConfig::BATTLESHIP,Block(0,0),Block(4,0));
    boats[2].setBoat(GameConfig::DESTROYER,Block(1,9),Block(3,9));
    boats[3].setBoat(GameConfig::SUBMARINE,Block(7,2),Block(9,2));
    boats[4].setBoat(GameConfig::PATROL,Block(7,6),Block(8,6));
}

int Controller::declareWinner(Board *userBoard, Board *computerBoard){
    if(userBoard->isAllBoatsBlasted())
        return GameConfig::COMPUTERBOT;
    else
        return GameConfig::USERBOT;
}

/*
 * The below function keeps the game continuing until any one of the board has lost its ships
 */
void Controller::play(Board *userBoard, Board *computerBoard) {
    while(true){
        makeMove(userBoard, computerBoard);
        if(userBoard->isAllBoatsBlasted() || computerBoard->isAllBoatsBlasted()){
            break;
        }

    }

}

void Controller::makeMove(Board *userBoard, Board *computerBoard) {

    if(currentTurn == GameConfig::USERBOT){

        Block block = userBot->makeMove(computerBoard->getLastMoveStatus(), computerBoard->getAllBoatsStatus());

        GameConfig::MoveStatus hit = computerBoard->dropBombOnBlock(block);

        if(hit != GameConfig::HIT){ // if a boat has been hit, the bot gets one more turn, else turn goes to the opponent
            currentTurn = GameConfig::COMPUTERBOT;
        }
        if(hit != GameConfig::INVALID){
            Move move;
            move.player = "UserBot";
            move.row = block.getX();
            move.column = block.getY();
            move.hit = ((hit == GameConfig::HIT) ? "true" : "false");
            moves.push_back(move);
        }

    }
    else if(currentTurn == GameConfig::COMPUTERBOT){

        Block block = computerBot->makeMove(userBoard->getLastMoveStatus(), userBoard->getAllBoatsStatus());
        GameConfig::MoveStatus hit = userBoard->dropBombOnBlock(block);

        if(hit != GameConfig::HIT){ // if a boat has been hit, the bot gets one more turn, else turn goes to the opponent
            currentTurn = GameConfig::USERBOT;
        }
        if(hit != GameConfig::INVALID){
            Move move;
            move.player = "ComputerBot";
            move.row = block.getX();
            move.column = block.getY();
            move.hit = ((hit == GameConfig::HIT) ? "true" : "false");
            moves.push_back(move);
        }
    }
}
