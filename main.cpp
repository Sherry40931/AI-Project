//
//  main.cpp
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#include "main.h"
#include "boardJudgement.hpp"


Board gameBoard = Board();
boardJudgement bj = boardJudgement(&gameBoard);

int main(int argc, const char * argv[]) {
    
    char r;
    int row, col;
    
    while(true){
        if(gameBoard.getTurn()%2) cout << "Black: ";
        else cout << "White: ";
        cin >> r;
        row = r - 'A';
        if(row == -1) break;
        cin >> col;
        if(col == -1) break;
        
        gameBoard.addChess(row, col);
        
        if(gameBoard.getState() == 0) gameBoard.printBoard();
        else if(gameBoard.getState() == 1) break;
        else if(gameBoard.getState() == -1) cout << "Repeated Chess!" << endl;
        else cout << "Error Input!" << endl;
        
        bj.Judge();
        
    }
    
    
    if(gameBoard.getState() == 1) {
        if(gameBoard.getTurn()%2) cout << "Game Over! Winner: Black" << endl;
        else cout << "Game Over! Winner: White" << endl;
    }
    else cout << "Game Over! Winner: N/A" << endl;
    gameBoard.printBoard();
    
    
    
    return 0;
}



