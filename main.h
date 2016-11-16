//
//  main.h
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#ifndef main_h
#define main_h

#include <iostream>
using namespace std;

struct Points{int x, y;};

class Board
{
public:
    //Board();
    void addChess(int row, int col);
    bool checkBoard();
    void printBoard();
    list <Points> getValidMove();
    
private:
    int board[15][15] = {0};
    int turn = 1;
    
};

list <Points> Board::getValidMove(){
	list <Points> validMoves = list <Points>();
	int i, j;
	Points toBeAdd;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			if(board[i][j] == 0){
				toBeAdd.x = i;
				toBeAdd.y = j;
				validMoves.push_back(toBeAdd);
				//printf("in getValidMove: %d %d\n", i, j);
			}
		}
	}
	return validMoves;
}

void Board::addChess(int row, int col){
    board[row][col] = (turn % 2) * 2  - 1;
    
    if(checkBoard()){
        if(turn % 2) cout << "Game Over! Winner: Black." << endl;
        else cout << "Game Over! Winner: White." << endl;
    }
    
    turn ++;
}

void Board::printBoard(){
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            if (board[i][j] == 1)
                cout << 'B' << " " ;
            else if (board[i][j] == -1)
                cout << 'W' << " " ;
            else cout << '-' << " ";
        }
        cout << endl;
    }
}

bool Board::checkBoard(){
    int state;
    
    for (int r = 0; r < 15; r++){
        for (int c = 0; c < 11; c++){
            state = board[r][c] + board[r][c+1] + board[r][c+2] + board[r][c+3]
            + board[r][c+4];
            
            if (state == 5 || state == -5) return true;
        }
    }
    
    for (int c = 0; c < 15; c++){
        for (int r = 0 ; r < 11; r++){
            state = board[r][c] + board[r+1][c] + board[r+2][c] + board[r+3][c]
            + board[r+4][c];
            
            if (state == 5 || state == -5) return true;
        }
    }
    
    for (int r = 0; r < 11; r++){
        for (int c = 0; c < 11; c++){
            //board[r][c] = board[r+1][c+1] = board[r+2][c+2] = board[r+3][c+3]
            //= board[r+4][c+4] = 8;
            state = board[r][c] + board[r+1][c+1] + board[r+2][c+2] + board[r+3][c+3]
            + board[r+4][c+4];
            
            if (state == 5 || state == -5) return true;
        }
    }
    
    for (int r = 0; r < 11; r++){
        for (int c = 4; c < 15; c++){
            //board[r][c] = board[r+1][c-1] = board[r+2][c-2] = board[r+3][c-3]
            //= board[r+4][c-4] = 8;
            state = board[r][c] + board[r+1][c-1] + board[r+2][c-2] + board[r+3][c-3]
            + board[r+4][c-4];
            
            if (state == 5 || state == -5) return true;
        }
    }
    
    return false;
}

#endif /* main_h */
