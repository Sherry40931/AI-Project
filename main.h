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

class Board
{
public:
    //Board();
    void addChess(int row, int col);
    void checkBoard();
    void printBoard();
    int getTurn();
    int getState();
    
    
private:
    int board[15][15] = {0};
    int turn = 1;
    int state = 0;
    
};

int Board::getState(){
    return state;
}

int Board::getTurn(){
    return turn;
}

void Board::addChess(int row, int col){
    if(row < 0 || col < 0 || row > 14 || col > 14){
        state = -2;
    }
    else if(board[row][col] != 0){
        state = -1;
    }
    else{
        board[row][col] = (turn % 2) * 2  - 1;
        checkBoard();
        if(state == 0) turn++;
    }
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

void Board::checkBoard(){
    int point;
    
    for (int r = 0; r < 15; r++){
        for (int c = 0; c < 11; c++){
            point = board[r][c] + board[r][c+1] + board[r][c+2] + board[r][c+3]
            + board[r][c+4];
            
            if (point == 5 || point == -5){
                state = 1;
                return;
            }
        }
    }
    
    for (int c = 0; c < 15; c++){
        for (int r = 0 ; r < 11; r++){
            point = board[r][c] + board[r+1][c] + board[r+2][c] + board[r+3][c]
            + board[r+4][c];
            
            if (point == 5 || point == -5){
                state = 1;
                return;
            }
        }
    }
    
    for (int r = 0; r < 11; r++){
        for (int c = 0; c < 11; c++){
            //board[r][c] = board[r+1][c+1] = board[r+2][c+2] = board[r+3][c+3]
            //= board[r+4][c+4] = 8;
            point = board[r][c] + board[r+1][c+1] + board[r+2][c+2] + board[r+3][c+3]
            + board[r+4][c+4];
            
            if (point == 5 || point == -5){
                state = 1;
                return;
            }
        }
    }
    
    for (int r = 0; r < 11; r++){
        for (int c = 4; c < 15; c++){
            //board[r][c] = board[r+1][c-1] = board[r+2][c-2] = board[r+3][c-3]
            //= board[r+4][c-4] = 8;
            point = board[r][c] + board[r+1][c-1] + board[r+2][c-2] + board[r+3][c-3]
            + board[r+4][c-4];
            
            if (point == 5 || point == -5){
                state = 1;
                return;
            }
        }
    }
    
    state = 0;
}

#endif /* main_h */
