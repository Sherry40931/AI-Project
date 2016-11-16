//
//  main.cpp
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#include "main.h"


Board gameBoard = Board();

int main(int argc, const char * argv[]) {
    
    int row, col;
    
    while(true){
        if(gameBoard.getTurn()%2) cout << "Black: ";
        else cout << "White: ";
        cin >> row;
        if(row == -1) break;
        cin >> col;
        if(col == -1) break;
        
        gameBoard.addChess(row, col);
        
        
        if(gameBoard.getState() >= 0){
            if(gameBoard.getState() == 1) {
                if(gameBoard.getTurn()%2) cout << "Game Over! Winner: Black" << endl;
                else cout << "Game Over! Winner: Winner" << endl;
            }
            gameBoard.printBoard();
        }
        else cout << "Error Input!" << endl;;
        
        
    }
    
    cout << "Game Over! Winner: N/A" << endl;
    gameBoard.printBoard();
    
    
    
    return 0;
}



