//
//  main.h
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#ifndef main_h
#define main_h

using namespace std;


//struct Points{int x, y;};

/*class Board
{
public:
    void addChess(int row, int col);
    void checkBoard();
    void printBoard();
    //list <Points> getValidMove();
    
    int getTurn();
    int getState();
    int table[15][15] = {0};
    
private:
    int turn = 1;
    int state = 0;
    
};*/

/*list <Points> Board::getValidMove(){
	list <Points> validMoves = list <Points>();
	int i, j;
	Points toBeAdd;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			if(table[i][j] == 0){
				toBeAdd.x = i;
				toBeAdd.y = j;
				validMoves.push_back(toBeAdd);
				//printf("in getValidMove: %d %d\n", i, j);
			}
		}
	}
	return validMoves;
}*/


#endif /* main_h */
