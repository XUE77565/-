/*
作者：薛翼�?
以下为对局面打分的函数
*/

#include "variable.h"
#include "score.h"
#include "shape.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "wincheck.h"
#include "checkban.h"



int evaluate_board(Evaluate *eval, int role){
    store_board(eval);
    point position;
    point score = {0,0};
    int c;
    int n=1;
    int black_score = 0;
    int white_score = 0;
    //��ʼ������, �����ķ�������0
    for(position.x = 0; position.x < SIZE; position.x++){
        for(position.y = 0; position.y < SIZE; position.y++){
            if((c=eval->board[position.x][position.y])!=EMPTY){//�ҵ�������������ӵĵ��������
                score = evaluate_position(eval, &position);
                read_board(eval);
                black_score += score.x;
                white_score += score.y;
            }
        }
    }
    int out;
    out = (role == BLACK) ? black_score - white_score*DEFENSE_RATE_BLACK : white_score - black_score*DEFENSE_RATE_WHITE;
    return out;
}


int check_in_board_range(point *position){//�ж�һ�����Ƿ������̵ķ�Χ��
    if(position->x >= 0 && position->x < SIZE && position->y >= 0 && position->y < SIZE){
        return 1;
    }
    else{
        return 0;
    }
}

int check_around(Evaluate *eval, point *position){
    point position1={position->x, position->y-1};//�����������Χ��??1?78����
    point position2={position->x, position->y+1};
    point position3={position->x+1, position->y};
    point position4={position->x-1, position->y};
    point position5={position->x+1, position->y+1};
    point position6={position->x+1, position->y-1};
    point position7={position->x-1, position->y+1};
    point position8={position->x-1, position->y-1};
    int check1 = check_in_board_range(&position1) && eval->board[position1.x][position1.y] != EMPTY;//������ڷ�Χ�ڲ��Ҳ��?1?70;
    int check2 = check_in_board_range(&position2) && eval->board[position2.x][position2.y] != EMPTY;
    int check3 = check_in_board_range(&position3) && eval->board[position3.x][position3.y] != EMPTY;
    int check4 = check_in_board_range(&position4) && eval->board[position4.x][position4.y] != EMPTY;
    int check5 = check_in_board_range(&position5) && eval->board[position5.x][position5.y] != EMPTY;
    int check6 = check_in_board_range(&position6) && eval->board[position6.x][position6.y] != EMPTY;
    int check7 = check_in_board_range(&position7) && eval->board[position7.x][position7.y] != EMPTY;
    int check8 = check_in_board_range(&position8) && eval->board[position8.x][position8.y] != EMPTY;
    int out = check1 || check2 || check3 || check4 || check5 || check6 || check7 || check8;
    return out;
}


point evaluate_position(Evaluate *eval, point *position){//��ʾ������λ�õķ���
    point score = {0,0};
    Evaluate temp = *eval;
    int c = eval->board[position->x][position->y];

        if(c == BLACK){
            score.x = calculate_score(&temp, position, BLACK);
            score.y = 0;
        }
        else{
            score.x = 0;
            score.y = calculate_score(&temp, position, WHITE);
        }
    return score;
}

int calculate_score(Evaluate *eval, point *position, int role){
    int score = 0;
    shape shape_position;
    int x = position->x;
    int y = position->y;
    if(role==BLACK){
        //����Ҫ�Ժ��ӵĽ��ֽ��м��??1?7
        if(check_ban(eval, x, y, BLACK)==1){
            return SCORE_BAN;
        }
        else{
            shape_position = check_shape(eval, position, BLACK);
        }
    }
    else{
        shape_position = check_shape(eval, position, WHITE);
    }
    int score_A5 = shape_position.A5 * SCORE_A5/5;
    int score_A4 = shape_position.A4 * SCORE_A4/4;
    int score_B4 = shape_position.B4 * SCORE_B4/4;
    int score_A3 = shape_position.A3 * SCORE_A3/3;
    int score_B3 = shape_position.B3 * SCORE_B3/3;
    int score_A2 = shape_position.A2 * SCORE_A2/2;
    int score_B2 = shape_position.B2 * SCORE_B2/2;
    score = score_A5 + score_A4 + score_B4 + score_A3 + score_B3 + score_A2 + score_B2;
    return score;
}

void store_board(Evaluate *eval){//����ǰ������״̬�ϴ������������??1?7
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            tempBoard[i][j] = eval->board[i][j];
        }
    }
}

void read_board(Evaluate *eval){//����ǰ������״̬�ϴ������������??1?7
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            eval->board[i][j] = tempBoard[i][j];
        }
    }
}



int check_must_block_attack(Evaluate *eval, int role){
    int oppo = opponent_select(role);
    int i,j;
    shape shape_check;
    point position;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(eval->board[i][j]==0){//���������ǲ�����Ч�Ŀ�λ
                position.x = i, position.y=j;
                arrayForInnerBoardLayout[i][j]=oppo;//ģ������
                if(check_ban(eval,i,j,oppo)){break;}
                // printf("CHECKING MUSTBLOCK(%d,%d)\n",i,j);
                shape_check = check_shape(eval, &position, oppo);
                if(shape_check.A5){//������������ֱ���γ������� ֱ�Ӷ�
                    arrayForInnerBoardLayout[i][j] = role;
                    if(role == 1){//��ֱ�Ӷ�����
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play1CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play1CurrentPic[1];
                    }
                    else{
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play2CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play2CurrentPic[1];
                    }
                    printf("AI places at (%d,%c)\n",i+1,'A'+j);
                    return 1;
                }else if(shape_check.A3 && shape_check.B4 ||shape_check.A3 && shape_check.A4){//������������ֱ���γ����ı�ʤ�֣� ֱ�Ӷ�
                    arrayForInnerBoardLayout[i][j] = role;
                    if(role == 1){//��ֱ�Ӷ�����
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play1CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play1CurrentPic[1];
                    }
                    else{
                        arrayForDisplayBoard[SIZE-i-1][2*j]=play2CurrentPic[0];
                        arrayForDisplayBoard[SIZE-i-1][2*j+1]=play2CurrentPic[1];
                    }
                    printf("AI places at (%d,%c)\n",i+1,'A'+j);
                    return 1;
                }else if(shape_check.A4){//������������ֱ���γɻ��ģ� ֱ�Ӷ�
                    arrayForInnerBoardLayout[i][j] = role;
                    if(role == 1){//��ֱ�Ӷ�����
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