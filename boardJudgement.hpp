//
//  boardJudgement.hpp
//  MCTS
//
//  Created by Angus on 2016/11/16.
//  Copyright © 2016年 Angus. All rights reserved.
//

#ifndef boardJudgement_hpp
#define boardJudgement_hpp

#include <stdio.h>
#include "main.h"

class boardJudgement
{
public:
    boardJudgement(Board* b);
    int *check1, *check2, *check3, check4;
    int *check[4];
    void Judge();
    int* CheckX(int, int, int);
    int* CheckY(int, int, int);
    int* CheckXY(int, int, int);
    int* CheckYX(int, int, int);
    
private:
    Board* board;
    int size = 15;
    int me=1;
    
};

boardJudgement::boardJudgement(Board* b){
    board = b;
}

void boardJudgement::Judge(){
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            if(board->table[i][j] == 0){
                check[0] = CheckX(i, j, me);
                check[1] = CheckY(i, j, me);
                check[2] = CheckXY(i, j, me);
                check[3] = CheckYX(i, j, me);
                printf("%d ", *check[0]);
            }
            else{
                printf("- ");
            }			
        }
        puts("");
    }
}

int* boardJudgement::CheckX(int m, int n, int me){
    static int result[2] = {};
    int flag = 0;
    int num = 1;
    int i, j;
    i = n+1;
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
    int i, j;
    
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


#endif /* boardJudgement_hpp */
