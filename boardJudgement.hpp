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
    int *check[8];
    void Judge();
    int* CheckX(int, int, int);
    int* CheckY(int, int, int);
    int* CheckXY(int, int, int);
    int* CheckYX(int, int, int);
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
                check[0] = CheckX(i, j, me);    //橫的
                check[1] = CheckY(i, j, me);    //直的
                check[2] = CheckXY(i, j, me);   //左上右下
                check[3] = CheckYX(i, j, me);   //右上左下
                check[4] = CheckX(i, j, -me);
                check[5] = CheckY(i, j, -me);
                check[6] = CheckXY(i, j, -me);
                check[7] = CheckYX(i, j, -me);
                
                if(i == 6 && j == 6){
                    check[0] = CheckX(i, j, me);    //橫的
                    //cout << endl << check[0][0] << endl;
                    check[1] = CheckY(i, j, me);    //直的
                    check[2] = CheckXY(i, j, me);   //左上右下
                    check[3] = CheckYX(i, j, me);   //右上左下
                    //cout << endl << check[0][0] << endl;
                    check[4] = CheckX(i, j, -me);
                    
                    check[5] = CheckY(i, j, -me);
                    check[6] = CheckXY(i, j, -me);
                    check[7] = CheckYX(i, j, -me);

                    /*
                    cout << me << endl;
                    for(int w = 0; w < 8; w++){
                        cout << check[w][0] << " ";
                    }
                    cout << endl;
                    */
                }
                
                weight[i][j] = getWeight();
                if(weight[i][j] > max){
                    maxi = i;
                    maxj = j;
                    max = weight[i][j];
                }
                //printf("%d ", weight[i][j]);
                //cout << check[0][1] << " ";
            }
            else{
                //printf("- ");
            }
        }
        //puts("");
    }
}

int* boardJudgement::CheckX(int m, int n, int me){
    static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    i = n+1;        //往右找
    while(i<size){
        if(board->table[m][i] == me){
            num++;
            i++;
        }
        else{
            break;
        }
    }
    if(board->table[m][i] == -me || i == size){
        flag++;
    }
    i = n-1;
    while(i>=0){
        if(board->table[m][i] == me){
            num++;
            i--;
        }
        else{
            break;
        }
    }
    if(board->table[m][i] == -me || i == -1){
        flag++;
    }
    result[0] = num;
    result[1] = flag;
    
    return result;
}



int* boardJudgement::CheckY(int m, int n, int me){
    static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i;
    
    i = m+1;
    while(i<size){
        if(board->table[i][n] == me){
            num++;
            i++;
        }
        else{
            break;
        }
    }
    if(board->table[i][n] != me || i == size){
        flag++;
    }
    i = m-1;
    while(i>=0){
        if(board->table[i][n] == me){
            num++;
            i--;
        }
        else{
            break;
        }
    }
    if(board->table[i][n] != me || i == -1){
        flag++;
    }
    result[0] = num;
    result[1] = flag;
    
    return result;
}

int* boardJudgement::CheckXY(int m, int n, int me){
    static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    
    i = m+1;
    j = n+1;
    while(i<size && j<size){
        if(board->table[i][j] == me){
            num++;
            i++;
            j++;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] != me || i == size || j==size){
        flag++;
    }
    i = m-1;
    j = n-1;
    while(i>=0 && j>=0){
        if(board->table[i][j] == me){
            num++;
            i--;
            j--;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] != me || i == -1 || j==-1){
        flag++;
    }
    result[0] = num;
    result[1] = flag;
    
    return result;
}

int* boardJudgement::CheckYX(int m, int n, int me){
    static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    
    i = m-1;
    j = n+1;
    while(i>=0 && j<size){
        if(board->table[i][j] == me){
            num++;
            i--;
            j++;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] != me || i == -1 || j==size){
        flag++;
    }
    i = m+1;
    j = n-1;
    while(i<size && j>=0){
        if(board->table[i][j] == me){
            num++;
            i++;
            j--;
        }
        else{
            break;
        }
    }
    if(board->table[i][j] != me || i == size || j==-1){
        flag++;
    }
    result[0] = num;
    result[1] = flag;
    
    return result;
}

int boardJudgement::getWeight(){
    //cout << "GGGGGG" << endl;
    int tempWeight = 0;
    int c3 = 0, c2 = 0;
    //檢查自己的連子情況
    for(int i = 0; i < 4; i++){
        switch ( check[i][0] ) {
            case 5:
                tempWeight += 50000;
                break;
                
            case 4:
                if(check[i][1] == 0)  //活4 多+30
                    tempWeight += 1500;
                else tempWeight += 1250;
                break;
                
            case 3:
                if(check[i][1] == 0){ //活3
                    c3++;
                    tempWeight += 5;
                    if(c3 > 1){
                        tempWeight += 50;
                    }
                }
                else{
                    tempWeight += 1;
                }
                break;
                
            case 2:
                //if(check[i][1] == 0)
                    tempWeight += 1;
                break;
                
            default:
                break;
        }
    }
    //檢查敵人
    c3 = 0;
    c2 = 0;
    for(int i = 4; i < 8; i++){
        switch ( check[i][0] ) {
            case 5:
                tempWeight += 6250;
                break;
                
            case 4:
                if(check[i][1]==0) //敵人下一步活4
                    tempWeight += 250;
                //else if(flag==1) //死4
                //tempWeight += 40;
                break;
                
            case 3:
                if(check[i][1] == 0){ //活3
                    c3++;
                    tempWeight += 3;
                    if(c3 > 1){
                        tempWeight += 10;
                    }
                }
                break;
                
            case 2:
                //if(check[i][1] == 0)
                    tempWeight += 1;
                break;
                
            default:
                break;
        }
    }
    
    return tempWeight;
}




#endif /* boardJudgement_hpp */
