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
    int player;
    
    cout << "Black or White Chess? (Black: 1, White: -1)";
    cin  >> player;
    bj.setMe(-player);
    
    while(true){
        if(((gameBoard.getTurn() % 2) * 2 - 1) == player){
            if(player == 1) cout << "Black: ";
            else cout << "White: ";
            
            cin >> r;
            row = r - 'A';
            if(row == -1) break;
            cin >> col;
            if(col == -1) break;
            
            gameBoard.addChess(row, col);
        }
        else{
            if(player == 1) cout << "White: " << endl;
            else cout << "Black: " << endl;
            
            if(gameBoard.getTurn() == 1) gameBoard.addChess(6, 7);
            else{
                
                /*cout << bj.CheckX(6, 6, -player)[0] << " " << bj.CheckY(6, 6, -player)[0] << " "
                << bj.CheckXY(6, 6, -player)[0] <<  " " << bj.CheckYX(6, 6, -player)[0] << endl;
                
                cout << bj.CheckX(6, 6, player)[0] << " " << bj.CheckY(6, 6, player)[0] << " "
                << bj.CheckXY(6, 6, player)[0] <<  " " << bj.CheckYX(6, 6, player)[0] << endl;
                
                bj.check[0] = bj.CheckX(6, 6, -player);
                bj.check[1] = bj.CheckY(6, 6, -player);
                bj.check[2] = bj.CheckXY(6, 6, -player);
                bj.check[3] = bj.CheckYX(6, 6, -player);
                bj.check[4] = bj.CheckX(6, 6, -player);
                bj.check[5] = bj.CheckY(6, 6, player);
                bj.check[6] = bj.CheckXY(6, 6, player);
                bj.check[7] = bj.CheckYX(6, 6, player);
                int w = bj.getWeight();
                cout << w << endl;*/
                //return 0;
                

                bj.Judge();
                gameBoard.addChess(bj.maxi, bj.maxj);
                
                cout << endl << endl;
            }
            
        }
        
        if(gameBoard.getState() == 0) gameBoard.printBoard();
        else if(gameBoard.getState() == 1) break;
        else if(gameBoard.getState() == -1) cout << "Repeated Chess!" << endl;
        else cout << "Error Input!" << endl;
    }
    
    if(gameBoard.getState() == 1) {
        if(gameBoard.getTurn()%2) cout << "Game Over! Winner: Black" << endl;
        else cout << "Game Over! Winner: White" << endl;
    }
    else cout << "Game Over! Winner: N/A" << endl;
    gameBoard.printBoard();
    
    
    
    return 0;
}

/*int max = 0;
for(int i=0; i<15;i++){
    for(int j=0; j<15; j++){
        if(gameBoard.table[i][j] == 0){
            bj.check[0] = bj.CheckX(i, j, -player);
            bj.check[1] = bj.CheckY(i, j, -player);
            bj.check[2] = bj.CheckXY(i, j, -player);
            bj.check[3] = bj.CheckYX(i, j, -player);
            bj.check[4] = bj.CheckX(i, j, player);
            bj.check[5] = bj.CheckY(i, j, player);
            bj.check[6] = bj.CheckXY(i, j, player);
            bj.check[7] = bj.CheckYX(i, j, player);
            
            bj.weight[i][j] = bj.getWeight();
            if(bj.weight[i][j] > max){
                bj.maxi = i;
                bj.maxj = j;
                max = bj.weight[i][j];
            }
            printf("%d ", bj.weight[i][j]);
            //cout << check[0][1] << " ";
        }
        else{
            printf("- ");
        }
    }
    puts("");
}*/


