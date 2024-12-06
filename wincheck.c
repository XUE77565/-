#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
int player;
int wincheck();
int check_row(int i,int j);
int check_col(int i,int j);
int check_A_to_D(int i,int j);
int check_B_to_C(int i,int j);
int input(int);
int arrayForInnerBoardLayout[SIZE][SIZE];

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
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // 检查位�? j 的左右两侧最�? 4 个位�?
    int start = j - 4 > 0 ? j - 4 : 0;
    int end = j + 4 < 14 ? j + 4 : 14;

    for (k = start; k <= j; k++) {
        int win = 1;
        for (r = 0; r < 5; r++) {
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] != c) {
                win = 0;
                break;
            }
        }
        if (win) {
            out = c;
            break;
        }
    }
    return out;
}

int check_col(int i, int j) {
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // 检查位�? j 的左右两侧最�? 4 个位�?
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
            out = c;
            break;
        }
    }
    return out;
}


// int check_col(int i,int j){
//     int out=0;
//     int c=arrayForInnerBoardLayout[i][j];
//     int k,q,r;
//     if(i<4){
//         q=0;
//         for(k=-i;k<=0;k++){
//             q=0;
//             for(r=0;r<5;r++){
//                 if(arrayForInnerBoardLayout[i+k+r][j]!=c)
//                     break;
//                 else
//                     q++;  
//             }
//             if(q==5){out=c;break;}
//         }
//         return out;
//     }
//     else if(i>=4 && i<=10){
//         q=0;
//         for(k=-4;k<=0;k++){
//             q=0;
//             for(r=0;r<5;r++){
//                 if(arrayForInnerBoardLayout[i+k+r][j]!=c)
//                     break;
//                 else
//                     q++;
//             }
//             if(q==5){out=c;break;}
//         }
//         return out;
//     }
//     else{
//         for(k=-4;(k+i)<=10;k++){
//             q=0;
//             for(r=0;r<5;r++){
//                 if(arrayForInnerBoardLayout[i+k+r][j]!=c)
//                     break;
//                 else
//                     q++;
//             }
//             if(q==5){out=c;break;}
//         }
//         return out;
//     }
// }

int check_A_to_D(int i, int j){
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
            out = c;
            break;
        }
    }
    return out;
}

int check_B_to_C(int i, int j){
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k;

    for(k = -4; k <= 0; k++){
        int count = 0;
        int r;
        int start_i = i - k;
        int start_j = j + k;

        // �����ʼλ���Ƿ�Խ��?
        if(start_i >= SIZE || start_j < 0)
            continue;

        // ������λ���Ƿ�Խ��
        if(start_i - 4 < 0 || start_j + 4 >= SIZE)
            continue;

        // ������������λ��
        for(r = 0; r < 5; r++){
            if(arrayForInnerBoardLayout[start_i - r][start_j + r] != c)
                break;
            else
                count++;
        }
        if(count == 5){
            out = c;
            break;
        }
    }
    return out;
}
