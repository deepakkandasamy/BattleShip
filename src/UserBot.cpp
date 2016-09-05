#include"UserBot.h"
int prevx,prevy,pPrevx,pPrevy;
int up,down,left,right;
int direction,minsize;
int numBoatsDestroyed;
bool prevState[5];
int hitCount;
stack <pair<int,int> > st;
pair<int, int> stackpoint;
vector<vector<int> > boardTraversed;
Block UserBot::makeMove(bool isLastMoveHit, bool isBoatsDestroyed[]){
	int tempCount=0;
	for(int i=0;i<GameConfig::NBOATS;i++){
		if(isBoatsDestroyed[i]){
			tempCount++;
		}
	}
	if(isLastMoveHit == true&&tempCount==numBoatsDestroyed){
		boardTraversed[prevx][prevy]=1;
		if(stackpoint.first==-1 && stackpoint.second==-1){
			stackpoint=make_pair(prevx,prevy);
			if(up+down+1>=minsize&&up>0){
				direction=1;
				prevx=stackpoint.first;
				prevy=stackpoint.second+1;
				return Block(stackpoint.first,stackpoint.second+1);
			}
			else if(up+down+1>=minsize&&down>0){
				direction=2;
				prevx=stackpoint.first;
				prevy=stackpoint.second-1;
				return Block(stackpoint.first,stackpoint.second-1);
			}
			else if(left+right+1>=minsize&&right>0){
				direction=3;
				prevx=stackpoint.first+1;
				prevy=stackpoint.second;
				return Block(stackpoint.first+1,stackpoint.second);
			}
			else if(left+right+1>=minsize&&left>0){
				direction=4;
				prevx=stackpoint.first-1;
				prevy=stackpoint.second;
				return Block(stackpoint.first-1,stackpoint.second);
			}
		}
		else{
			switch (direction){
				case 1:{
					       if(up>0){
						       up--;
						       prevx=prevx;
						       prevy=prevy+1;
						       return Block(prevx,prevy);
					       }
					       else{
						       direction=2;
					       }
				       }
				case 2:{
					       if(down>0){
						       down--;
						       prevx=prevx;
						       prevy=prevy-1;
						       return Block(prevx,prevy);
					       }
					       else{
						       stackpoint=make_pair(-1,-1);
						       up=down=left=right=0;
						       bool flag=1;
						       while(flag) {
							       int x=rand()%GameConfig::ROWS;
							       int y=rand()%GameConfig::COLUMNS;
							       if(boardTraversed[x][y]==-1){
								       int minsize=0;
								       for(int i=GameConfig::BoatType::PATROL;i>=GameConfig::BoatType::BATTLESHIP;i--){
									       if(i==4){
										       minsize=2;
									       }
									       else if(i==3||i==2){
										       minsize=3;
									       }
									       else minsize++;
									       if(!isBoatsDestroyed[i]){
										       break;
									       }
								       }
								       up=left=right=down=0;
								       int i=1;
								       /*traverse up and down to find the first hit or mis
									 add up and down to find weather min sizeship can be accomodated
									 in this range.
									 If everything is fine then make flag as false and return that block*/
								       while(i<minsize&&x+i<GameConfig::COLUMNS){
									       if(boardTraversed[x+i][y]!=-1){
										       break;
									       }
									       i++;
									       up++;
								       }
								       i=1;
								       while(i<minsize&&x-i>=0){
									       if(boardTraversed[x-i][y]!=-1){
										       break;
									       }
									       i++;
									       down++;
								       }
								       while(i<minsize&&y+i<GameConfig::ROWS){
									       if(boardTraversed[x][y+i]!=-1){
										       break;
									       }
									       i++;
									       right++;
								       }
								       i=1;
								       while(i<minsize&&y-i>=0){
									       if(boardTraversed[x][y-i]!=-1){
										       break;
									       }
									       i++;
									       left++;
								       }
								       if(up+down+1>=minsize||left+right+1>=minsize){
									       prevx=x;
									       prevy=y;
									       return Block(x,y);
								       }
							       }
						       }
					       }
				       }
				case 3:{
					       if(left>0){
						       left--;
						       prevx=prevx-1;
						       prevy=prevy;
						       return Block(prevx,prevy);
					       }
					       else{
						       direction=4;
					       }
				       }
				case 4:{
					       if(right>0){
						       right--;
						       prevx=prevx+1;
						       prevy=prevy;
					       }
					       else{
						       stackpoint=make_pair(-1,-1);
						       up=down=left=right=0;
						       bool flag=1;
						       while(flag) {
							       int x=rand()%GameConfig::ROWS;
							       int y=rand()%GameConfig::COLUMNS;
							       if(boardTraversed[x][y]==-1){
								       int minsize=0;
								       for(int i=GameConfig::BoatType::PATROL;i>=GameConfig::BoatType::BATTLESHIP;i--){
									       if(i==4){
										       minsize=2;
									       }
									       else if(i==3||i==2){
										       minsize=3;
									       }
									       else minsize++;
									       if(!isBoatsDestroyed[i]){
										       break;
									       }
								       }
								       up=left=right=down=0;
								       int i=1;
								       /*traverse up and down to find the first hit or mis
									 add up and down to find weather min sizeship can be accomodated
									 in this range.
									 If everything is fine then make flag as false and return that block*/
								       while(i<minsize&&x+i<GameConfig::COLUMNS){
									       if(boardTraversed[x+i][y]!=-1){
										       break;
									       }
									       i++;
									       up++;
								       }
								       i=1;
								       while(i<minsize&&x-i>=0){
									       if(boardTraversed[x-i][y]!=-1){
										       break;
									       }
									       i++;
									       down++;
								       }
								       i=1;
								       while(i<minsize&&y+i<GameConfig::ROWS){
									       if(boardTraversed[x][y+i]!=-1){
										       break;
									       }
									       i++;
									       right++;
								       }
								       i=1;
								       while(i<minsize&&y-i>=0){
									       if(boardTraversed[x][y-i]!=-1){
										       break;
									       }
									       i++;
									       left++;
								       }
								       if(up+down+1>=minsize||left+right+1>=minsize){
									       prevx=x;
									       prevy=y;
									       return Block(x,y);
								       }
							       }
						       }
					       }
				       }
			}
		}
	}
	else if(isLastMoveHit==true&&tempCount!=numBoatsDestroyed){
		boardTraversed[prevx][prevy]=1;
		numBoatsDestroyed++;
		stackpoint=make_pair(-1,-1);
		up=down=left=right=0;
		bool flag=1;
		while(flag) {
			int x=rand()%GameConfig::ROWS;
			int y=rand()%GameConfig::COLUMNS;
			if(boardTraversed[x][y]==-1){
				int minsize=0;
				for(int i=GameConfig::BoatType::PATROL;i>=GameConfig::BoatType::BATTLESHIP;i--){
					if(i==4){
						minsize=2;
					}
					else if(i==3||i==2){
						minsize=3;
					}
					else minsize++;
					if(!isBoatsDestroyed[i]){
						break;
					}
				}
				up=left=right=down=0;
				int i=1;
				/*traverse up and down to find the first hit or mis
				  add up and down to find weather min sizeship can be accomodated
				  in this range.
				  If everything is fine then make flag as false and return that block*/
				while(i<minsize&&x+i<GameConfig::COLUMNS){
					if(boardTraversed[x+i][y]!=-1){
						break;
					}
					i++;
					up++;
				}
				i=1;
				while(i<minsize&&x-i>=0){
					if(boardTraversed[x-i][y]!=-1){
						break;
					}
					i++;
					down++;
				}
				while(i<minsize&&y+i<GameConfig::ROWS){
					if(boardTraversed[x][y+i]!=-1){
						break;
					}
					i++;
					right++;
				}
				i=1;
				while(i<minsize&&y-i>=0){
					if(boardTraversed[x][y-i]!=-1){
						break;
					}
					i++;
					left++;
				}
				if(up+down+1>=minsize||left+right+1>=minsize){
					prevx=x;
					prevy=y;
					return Block(x,y);
				}
			}
		}
	}
	else{
		if(stackpoint.first==-1 && stackpoint.second==-1){
			//call randomly and check the points
			bool flag=1;
			int x,y;
			stackpoint=make_pair(-1,-1);
			while(flag) {
				x=rand()%GameConfig::ROWS;
				y=rand()%GameConfig::COLUMNS;
				if(boardTraversed[x][y]==-1){
					minsize=0;
					for(int i=GameConfig::BoatType::PATROL;i>=GameConfig::BoatType::BATTLESHIP;i--){
						if(i==4){
							minsize=2;
						}
						else if(i==3||i==2){
							minsize=3;
						}
						else minsize++;
						if(!isBoatsDestroyed[i]){
							break;
						}
					}
					up=left=right=down=0;
					int i=1;
					/*traverse up and down to find the first hit or mis
					  add up and down to find weather min sizeship can be accomodated
					  in this range.
					  If everything is fine then make flag as false and return that block*/
					while(i<minsize&&x+i<GameConfig::COLUMNS){
						if(boardTraversed[x+i][y]!=-1){
							break;
						}
						i++;
						up++;
					}
					i=1;
					while(i<minsize&&x-i>=0){
						if(boardTraversed[x-i][y]!=-1){
							break;
						}
						i++;
						down++;
					}
					i=1;
					while(i<minsize&&y+i<GameConfig::ROWS){
						if(boardTraversed[x][y+i]!=-1){
							break;
						}
						i++;
						right++;
					}
					i=1;
					while(i<minsize&&y-i>=0){
						if(boardTraversed[x][y-i]!=-1){
							break;
						}
						i++;
						left++;
					}
					if(up+down+1>=minsize||left+right+1>=minsize){
						prevx=x;
						prevy=y;
						return Block(x,y);
					}
				}
			}
		}
		else{
			boardTraversed[prevx][prevy]=0;
			if(direction==1){
				if(down>0)
					direction=2;
				else if(left+right+1>minsize){
					direction=3;
				}
				else direction=-1;
			}
			else if(direction==2){
				if(left+right+1>minsize){
					direction=3;
				}
				else direction=-1;
			}
			else if(direction==3){
				if(right>0){
					direction=4;
				}
				else direction=-1;
			}
			switch (direction){
				case 2:{
					       if(down>0){
						       down--;
						       prevx=prevx;
						       prevy=prevy-1;
						       return Block(prevx,prevy);
					       }
				       }
				case 3:{
					       if(left>0){
						       left--;
						       prevx=prevx-1;
						       prevy=prevy;
						       return Block(prevx,prevy);
					       }
				       }
				case 4:{
					       if(right>0){
						       right--;
						       prevx=prevx+1;
						       prevy=prevy;
						       return Block(prevx,prevy);
					       }
				       }
				case -1:{
						bool flag=1;
						int x,y;
						while(flag){
							x=rand()%GameConfig::ROWS;
							y=rand()%GameConfig::COLUMNS;
							if(boardTraversed[x][y]==-1){
								minsize=0;
								for(int i=GameConfig::BoatType::PATROL;i>=GameConfig::BoatType::BATTLESHIP;i--){
									if(i==4){
										minsize=2;
									}
									else if(i==3||i==2){
										minsize=3;
									}
									else minsize++;
									if(!isBoatsDestroyed[i]){
										break;
									}
								}
								up=left=right=down=0;
								int i=1;
								/*traverse up and down to find the first hit or mis
								  add up and down to find weather min sizeship can be accomodated
								  in this range.
								  If everything is fine then make flag as false and return that block*/
								while(i<minsize&&x+i<GameConfig::COLUMNS){
									if(boardTraversed[x+i][y]!=-1){
										break;
									}
									i++;
									up++;
								}
								i=1;
								while(i<minsize&&x-i>=0){
									if(boardTraversed[x-i][y]!=-1){
										break;
									}
									i++;
									down++;
								}
								i=1;
								while(i<minsize&&y+i<GameConfig::ROWS){
									if(boardTraversed[x][y+i]!=-1){
										break;
									}
									i++;
									right++;
								}
								i=1;
								while(i<minsize&&y-i>=0){
									if(boardTraversed[x][y-i]!=-1){
										break;
									}
									i++;
									left++;
								}
								if(up+down+1>=minsize||left+right+1>=minsize){
									prevx=x;
									prevy=y;
									return Block(x,y);
								}
							}
						}
					}
			}
		}
	}
}
Boat* UserBot::positionBoats(Boat boats[]) {
    for(int i = 0; i<GameConfig::NBOATS;i++){

    }
    return boats;
}

