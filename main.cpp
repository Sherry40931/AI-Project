//
//  main.cpp
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#include "main.h"
#include "MTCS.h"

Board gameBoard = Board();
MTCS mtcs = MTCS(gameBoard);

int main(int argc, const char * argv[]) {
    
    
    gameBoard.addChess(1, 5);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(2, 4);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(3, 3);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(4, 2);
    gameBoard.addChess(2, 1);
    gameBoard.addChess(5, 1);
    
    mtcs.Execute();
    
    gameBoard.printBoard();
    
    return 0;
}