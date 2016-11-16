//
//  boardJudgement.hpp
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#ifndef boardJudgement_hpp
#define boardJudgement_hpp

#include "board.h"

using namespace std;

class boardJudgement
{
public:
    boardJudgement(Board* b);
    //int *check1, *check2, *check3, check4;
    int check[8][2];
    void Judge();
    void CheckX(int, int, int);
    void CheckY(int, int, int);
    void CheckXY(int, int, int);
    void CheckYX(int, int, int);
    int getWeight();
    void setMe(int player);
    int weight[15][15];
    int max = 0, maxi, maxj;
    
private:
    Board* board;
    int size = 15;
    int me = 1;
};

boardJudgement::boardJudgement(Board* b){
    board = b;
}

void boardJudgement::setMe(int player){
    me = player;
}

void boardJudgement::Judge(){
    max = 0;
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            if(board->table[i][j] == 0){
                CheckX(i, j, me);    //橫的
                CheckY(i, j, me);    //直的
                CheckXY(i, j, me);   //左上右下
                CheckYX(i, j, me);   //右上左下
                CheckX(i, j, -me);
                CheckY(i, j, -me);
                CheckXY(i, j, -me);
                CheckYX(i, j, -me);
                
                /*if(i == 6 && j == 6){
                    CheckX(i, j, me);    //橫的
                    cout << endl << check[0][0] << endl;
                    CheckY(i, j, me);    //直的
                    CheckXY(i, j, me);   //左上右下
                    CheckYX(i, j, me);   //右上左下
                    
                    CheckX(i, j, -me);
                    cout << endl << check[0][0] << endl;
                    CheckY(i, j, -me);
                    CheckXY(i, j, -me);
                    CheckYX(i, j, -me);

                    
                    cout << me << endl;
                    for(int w = 0; w < 8; w++){
                        cout << check[w][0] << " ";
                    }
                    cout << endl;
                }*/
                
                weight[i][j] = getWeight();
                if(weight[i][j] > max){
                    maxi = i;
                    maxj = j;
                    max = weight[i][j];
                }
                printf("%d ", weight[i][j]);
                //cout << check[0][1] << " ";
            }
            else{
                printf("- ");
            }
        }
        puts("");
    }
}

void boardJudgement::CheckX(int m, int n, int player){
    //static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    i = n+1;        //往右找
    while(i<size){
        if(board->table[m][i] == player){
            num++;
            i++;
        }
        else{
            break;
        }
    }
    if(board->table[m][i] == -player || i == size){
        flag++;
    }
    i = n-1;
    while(i>=0){
        if(board->table[m][i] == player){
            num++;
            i--;
        }
        else{
            break;
        }
    }
    if(board->table[m][i] == -player || i == -1){
        flag++;
    }
    //result[0] = num;
    //result[1] = flag;
    
    if(player == me){
        //check[0] = {num, flag};
        
        check[0][0] = num;
        check[0][1] = flag;
    }
    else{
        check[4][0] = num;
        check[4][1] = flag;
    }
    
}



void boardJudgement::CheckY(int m, int n, int player){
    //static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i;
    
    i = m+1;
    while(i<size){
        if(board->table[i][n] == player){
            num++;
            i++;
        }
        else{
            break;
        }
    }
    if(board->table[i][n] == -player || i == size){
        flag++;
    }
    i = m-1;
    while(i>=0){
        if(board->table[i][n] == player){
            num++;
            i--;
        }
        else{
            break;
        }
    }
    if(board->table[i][n] == -player || i == -1){
        flag++;
    }
    //result[0] = num;
    //result[1] = flag;
    if(player == me){
        check[1][0] = num;
        check[1][1] = flag;
    }
    else{
        check[5][0] = num;
        check[5][1] = flag;
    }
}

void boardJudgement::CheckXY(int m, int n, int player){
    //static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    
    i = m+1;
    j = n+1;
    while(i<size && j<size){
        if(board->table[i][j] == player){
            num++;
            i++;
            j++;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] == -player || i == size || j==size){
        flag++;
    }
    i = m-1;
    j = n-1;
    while(i>=0 && j>=0){
        if(board->table[i][j] == player){
            num++;
            i--;
            j--;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] == -player || i == -1 || j==-1){
        flag++;
    }
    //result[0] = num;
    //result[1] = flag;
    if(player == me){
        check[2][0] = num;
        check[2][1] = flag;
    }
    else{
        check[6][0] = num;
        check[6][1] = flag;
    }
}

void boardJudgement::CheckYX(int m, int n, int player){
    //static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    
    i = m-1;
    j = n+1;
    while(i>=0 && j<size){
        if(board->table[i][j] == player){
            num++;
            i--;
            j++;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] == -player || i == -1 || j==size){
        flag++;
    }
    i = m+1;
    j = n-1;
    while(i<size && j>=0){
        if(board->table[i][j] == player){
            num++;
            i++;
            j--;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] == -player || i == size || j==-1){
        flag++;
    }
    //result[0] = num;
    //result[1] = flag;
    if(player == me){
        check[3][0] = num;
        check[3][1] = flag;
    }
    else{
        check[7][0] = num;
        check[7][1] = flag;
    }
}

int boardJudgement::getWeight(){
    //cout << "GGGGGG" << endl;
    int tempWeight = 0;
    int fourContD = 0;
    int threeContD = 0, threeCont = 0, twoCont = 0;

    //檢查自己的連子情況
    for(int i = 0; i < 4; i++){
        switch ( check[i][0] ) {
            case 5:
                tempWeight += 50000;
                break;
                
            case 4:
                if(check[i][1] == 0)  //活4
                    tempWeight += 1500;
                else if(check[i][1] == 1){
                    fourContD++;
                    tempWeight += 1250;
                }
                break;
                
            case 3:
                if(check[i][1] == 0){ //活3
                    threeCont++;
                    tempWeight += 5;
                    if(threeCont > 1){
                        tempWeight += 50;
                    }
                }
                else if(check[i][1] == 1){
                    threeContD ++;
                    tempWeight += 1;
                }
                break;
                
            case 2:
                if(check[i][1] == 0){
                }
                tempWeight += 1;
                break;
                
            default:
                break;
        }
    }
    //檢查死4活3
    if(fourContD >= 1 && threeCont >= 1) tempWeight += 1250;
    
    //檢查敵人
    threeCont = 0;
    twoCont = 0;
    threeContD = 0;
    fourContD = 0;
    
    for(int i = 4; i < 8; i++){
        switch ( check[i][0] ) {
            case 5:
                tempWeight += 6250;
                break;
                
            case 4:
                if(check[i][1]==0) //敵人下一步活4
                    tempWeight += 250;
                else if(check[i][1] == 1){ //死4
                    fourContD++;
                    tempWeight += 1;
                }
                break;
                
            case 3:
                //cout << "敵人活3: " << check[i][1] << endl;
                if(check[i][1] == 0){ //活3
                    threeCont++;
                    tempWeight += 3;
                    if(threeCont > 1){
                        tempWeight += 10;
                    }
                }
                else if(check[i][1] == 1){
                    threeContD ++;
                    tempWeight += 1;
                }
                break;
                
            case 2:
                if(check[i][1] == 0){
                }
                tempWeight += 1;
                break;
                
            default:
                break;
        }
    }
    if(fourContD >= 1 && threeCont >= 1) tempWeight += 250;
    
    return tempWeight;
}




#endif /* boardJudgement_hpp */
