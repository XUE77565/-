/*
作者：薛翼舟
以下为检查是否胜利的函数
*/


#include "wincheck.h"
#include "variable.h"
#include "checkban.h"
#include "shape.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15



int wincheck(){
    int i, j;
    int out = 0;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(checkpoint(i, j) != 0){
                return checkpoint(i,j);
            }
        }
    }
    return 0;
}



int checkpoint(int i,int j){
    if((check_row(i,j)!=0) ||(check_col(i,j)!=0) || (check_A_to_D(i,j)!=0) || (check_B_to_C(i,j)!=0))
        return arrayForInnerBoardLayout[i][j];
}


int check_row(int i, int j) {
    int check1 = 0;
    int check2 = 0;
    int out = 0;
    int win;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // ??d???? j ?????k??????? 4 ?????
    int start = j - 4 > 0 ? j - 4 : 0;
    int end = j + 4 < 14 ? j + 4 : 14;

    for (k = start; k <= j; k++) {
        win = 1;
        for (r = 0; r < 5; r++) {
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] != c) {
                win = 0;
                break;
            }
        }
        if (win) {//接下来检查是否这个五连珠的两端是否符合要求
            if(c==2){
                out = 2;
                break;//如果是白棋, 直接返回2
            }
            else{//如果是黑棋
                if(k-1<0 || arrayForInnerBoardLayout[i][k-1]!=1)//要求这个两端不能是自己的棋子
                    check1 = 1;
                if(k+5>14 || arrayForInnerBoardLayout[i][k+5]!=1)
                    check2 = 1;
                if(check1&&check2){
                    out = 1;
                    break;
                }
            }
        }
    }
    return out;
}

int check_col(int i, int j) {
    int check1 = 0, check2 = 0;
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // ??d???? j ?????k??????? 4 ?????
    int start = i - 4 > 0 ? i - 4 : 0;
    int end = i + 4 < 14 ? i + 4 : 14;

    for (k = start; k <= i; k++) {
        int win = 1;
        for (r = 0; r < 5; r++) {
            if (k + r > end || arrayForInnerBoardLayout[k+r][j] != c) {
                win = 0;
                break;
            }
        }
        if (win) {
            if(c==2)
                out = 2;
            else{//如果是黑棋
                if(k-1<0 || arrayForInnerBoardLayout[k-1][j]!=1)//要求这个两端不能是自己的棋子
                    check1 = 1;
                if(k+5>14 || arrayForInnerBoardLayout[k+5][j]!=1)
                    check2 = 1;
                if(check1&&check2){
                    out = 1;
                    break;
                }
            }  
        }
    }
    return out;
}



int check_A_to_D(int i, int j){
    int check1=0,check2=0;
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k;

    for(k = -4; k <= 0; k++){
        int count = 0;
        int r;
        int start_i = i + k;
        int start_j = j + k;

        
        if(start_i < 0 || start_j < 0)
            continue;

       
        if(start_i + 4 >= SIZE|| start_j + 4 >= SIZE)
            continue;

    
        for(r = 0; r < 5; r++){
            if(arrayForInnerBoardLayout[start_i + r][start_j + r] != c)
                break;
            else
                count++;
        }
        if(count == 5){
            if(c==2){
                out=2;
                break;
            }
            else {
                if(start_i-1<0 || start_j-1<0 || arrayForInnerBoardLayout[start_i-1][start_j-1]!=1)
                    check1 = 1;
                if(start_i+5>14 || start_j+5>14 || arrayForInnerBoardLayout[start_i+5][start_j+5]!=1)
                    check2 = 1;
                if(check1&&check2){
                    out = 1;
                    break;
                }
            }
        }
    }
    return out;
}

int check_B_to_C(int i, int j){
    int check1=0,check2=0;
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k;

    for(k = -4; k <= 0; k++){
        int count = 0;
        int r;
        int start_i = i - k;
        int start_j = j + k;

        // ???????f?????????
        if(start_i >= SIZE || start_j < 0)
            continue;

        // ???????f????????
        if(start_i - 4 < 0 || start_j + 4 >= SIZE)
            continue;

        // ?????????????f??
        for(r = 0; r < 5; r++){
            if(arrayForInnerBoardLayout[start_i - r][start_j + r] != c)
                break;
            else
                count++;
        }
        if(count == 5){
            if(c==2){
                out=2;
                break;
            }
            else {
                if(start_i+1>14 || start_j-1<0 || arrayForInnerBoardLayout[start_i+1][start_j-1]!=1)
                    check1 = 1;
                if(start_i-5<0 || start_j+5>14 || arrayForInnerBoardLayout[start_i-5][start_j+5]!=1)
                    check2 = 1;
                if(check1&&check2){
                    out = 1;
                    break;
                }
            }
        }
    }
    return out;
}

int check_absolute_win(Evaluate *eval, int role){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(eval->board[i][j]==0 && check_ban(eval,i,j,role)==0){//检查这个点是不是有效的空位
                arrayForInnerBoardLayout[i][j]=role;//模拟下子
                if(wincheck()){//如果下这里可以赢, 直接下
                    if(role == 1){
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play1CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play1CurrentPic[1];
                    }
                    else{
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play2CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play2CurrentPic[1];
                    }
                    printf("AI places at (%d,%c)\n",i+1,'A'+j);
                    return 1;
                }
                arrayForInnerBoardLayout[i][j]=0;
            }
        }
    }
    return 0;
}