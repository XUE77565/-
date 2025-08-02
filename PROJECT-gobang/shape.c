/*
���ߣ�Ѧ����
����Ϊ��һ���������͵ĺ���
*/

#include "checkban.h"
#include "variable.h"
#include "checksimple.h"
#include "score.h"
#include<stdio.h>
#include<time.h>
#define SIZE 15

int opponent_select(int role){
    if(role==1){
        return 2;
    }
    else{
        return 1;
    }
}


shape check_shape(Evaluate *eval, point *position, int role){
    pivot++;
    time_t start = clock();
    shape out;
    out.A5 = 0;
    out.A4 = 0;
    out.B4 = 0;
    out.A3 = 0;
    out.B3 = 0;
    out.A2 = 0;
    out.B2 = 0;
    out.A2 = check_A2(eval, position, role);
    out.B2 = check_B2(eval, position, role);
    out.A3 = check_A3(eval, position, role);
    out.B3 = check_B3(eval, position, role);
    out.A4 = check_A4(eval, position, role);
    out.B4 = check_B4(eval, position, role);
    out.A5 = check_A5(eval, position, role);
    time_t end = clock();
    time_shape += ((double)end-start)/CLOCKS_PER_SEC;
    return out;
}


int check_A5(Evaluate *eval, point *position, int role) {
    int count;
    int i, x, y;
    for (i = 0; i < 4; i++) {
        count = 1; // ������ǰ??
        int dx = direction[i][0];
        int dy = direction[i][1];
        // �����??
        x = position->x + dx;
        y = position->y + dy;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && eval->board[x][y] == role) {
            // printf("nihao123\n");
            count++;
            x += dx;
            y += dy;
        }
        // �����??
        x = position->x - dx;
        y = position->y - dy;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && eval->board[x][y] == role) {
            count++;
            x -= dx;
            y -= dy;
        }
        if (count >= 5) {
            return 1; // ��������??
        }
    }
    return 0; // ������������
}


//�����ĵĺ���
int check_A4(Evaluate *eval, point *position, int role) {
    int i, count, block;
    int out = 0; // ���ڼ�¼���ĵ���??
    int x, y;

    for (i = 0; i < 4; i++) {
        count = 1; // ������ǰ??
        block = 0; // ��¼�����Ƿ���??

        int dx = direction[i][0];
        int dy = direction[i][1];

        // �����??
        x = position->x + dx;
        y = position->y + dy;

        int empty = 0; // ���ڱ���Ƿ�������λ

        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (eval->board[x][y] == role) {
                count++;
            } 
            else if (eval->board[x][y] == EMPTY) {
                empty++;
            } 
            else {
                // �����Է����ӣ������赲
                block++;
                break;
            }
            x += dx;
            y += dy;
        }

        // �����߽磬�����赲
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block++;
        }

        // �����飬�߼�ͬ��
        x = position->x - dx;
        y = position->y - dy;

        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (eval->board[x][y] == role) {
                count++;
            } 
            else if (eval->board[x][y] == EMPTY) {
                empty++;
            }  
            else {
                block++;
                break;
            }
            x -= dx;
            y -= dy;
        }

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block++;
        }

        // �ж��Ƿ��γɻ���
        if (count == 4 && block == 0 && empty == 2) {
            out++;
        }
    }

    return out;
}




//�������ֳ���, ����֮ǰ��checkban��д�ļ���ĵĺ�??
int check_B4(Evaluate *eval, point *position, int role){
    int out=0;
    int i = position->x, j = position->y;
    out = check_B4_row(eval,i,j,role)+check_B4_col(eval,i,j,role)+check_B4_AtoD(eval,i,j,role)+check_B4_BtoC(eval,i,j,role);
    return out;
}

int check_B4_row(Evaluate *eval,int i,int j, int role);
int check_B4_row(Evaluate *eval,int i,int j, int role){//������Ļ��Ļ��߳�??
    int count=0;
    int out=0;
    int check_available;
    int check_con=0;

    int k,r,q;
    int start = j - 4 > 0 ? j - 4 : 0;//��鿪ʼλ���Ƿ�Խ??0
    int end = j + 4 < 14 ? j + 4 : 14;//������λ���Ƿ�Խ??14
    int opponent = opponent_select(role);
    
    if(check_B4_str_row(eval,i,j,role)){//�����⵽һ��������ĳ�??
        return check_B4_str_row(eval,i,j,role);
    }

    for (k = start; k <= j; k++) {//��������Ƿ�??"�п�"��������
        count = 0;
        check_available = 0;
        check_con = 0;
        for(r = 0 ; r < 5; r++){
            if(eval->board[i][k+r] == role){
                count++;
                check_con++;
            }
            if(check_con = 4){
                count = 0;
                break;
            }
            if(eval->board[i][k+r] == 0){
                check_con = 0;
            }
            if (k + r > end || eval->board[i][k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 4){//����������λ�������ҵ��ĸ�, ����Ƿ��п�λ
                for(q = 0; q < 4; q++){
                    if(eval->board[i][k+q]==0){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//��������λ���������ĸ��Ӳ��������������Ч�Ŀ�??
            out ++;
        }
    }
    return out;
}

int check_B4_str_row(Evaluate *eval,int i,int j, int role);
int check_B4_str_row(Evaluate *eval,int i,int j, int role){//������������??, ��û�а�??(i,j)�ĺ������������
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);

    int start = j - 3 > 0 ? j - 3 : 0;
    int end = j + 3 < 14 ? j + 3 : 14;
    for (k = start; k <= j; k++) {
        int check = 1;

        for (r = 0; r < 4; r++) {
            if (k + r > end || eval->board[i][k + r] != role) {
                check = 0;
                break;
            }
        }

        if (check) {//���������������, ����ȥ��������������Ƿ��ǳ�??
            if(k-1>=0 && eval->board[i][k-1]==0 && (k+4>=SIZE || eval->board[i][k+4]==opponent)){//����Ƿ��п�λ, ��λ�����ǽ�??
                out = 1;
                break;
            }
            if(k+4<=14 && eval->board[i][k-1]==0 && (k-1<0 || eval->board[i][k-1]==opponent)){
                out = 1;
                break;
            }
        }
    }
    return out;
}

int check_B4_col(Evaluate *eval,int i,int j, int role);
int check_B4_col(Evaluate *eval,int i,int j, int role){//�������Ļ��Ļ��߳���
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);
    int check_con = 0;

    int k,r,q;
    int start = i - 4 > 0 ? i - 4 : 0;//��鿪ʼλ���Ƿ�Խ��0
    int end = i + 4 < 14 ? i + 4 : 14;//������λ���Ƿ�Խ��14

    if(check_B4_str_col(eval,i,j,role)){//�����⵽һ����Ч��������, ֱ�ӷ���1
        return check_B4_str_col(eval,i,j,role);
    }

    for (k = start; k <= i; k++) {//���������Ƿ���"�п�"��������
        count = 0;
        check_available = 0;
        check_con = 0;
        for(r = 0 ; r < 5; r++){
            if(eval->board[k+r][j] == role){
                count++;
                check_con ++;
            }
            if(eval->board[k+r][j] == 0){
                check_con = 0;
            }
            if(check_con == 4){
                count = 0;
                break;
            }
            if (k + r > end || eval->board[k + r][j] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 4){//����������λ�������ҵ��ĸ�, ����Ƿ��п�λ
                for(q = 0; q < 5; q++){
                    if(eval->board[k+q][j]==0){//����п�λ, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//��������λ���������ĸ��Ӳ��������������Ч�Ŀ�λ
            out ++;
        }
    }
    return out;
}

int check_B4_str_col(Evaluate *eval,int i,int j,int role);
int check_B4_str_col(Evaluate *eval,int i,int j,int role){//������������??, ��û�а�??(i,j)������������
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);
    int start = i - 3 > 0 ? i - 3 : 0;
    int end = i + 3 < 14 ? i + 3 : 14;

    for (k = start; k <= i; k++) {
        int check = 1;
        for (r = 0; r < 4; r++) {
            if (k + r > end || eval->board[k + r][j] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ�����Ч������??
            if(k-1>=0 && eval->board[k-1][j]==0 &&(k+4>=SIZE || eval->board[k+4][j]==opponent)){//����Ƿ��п�λ, ��λ�����ǽ�??
                out = 1;
                break;
            }
            if(k+4<=14 && eval->board[k+4][j]==0 && (k-1<0 || eval->board[k-1][j]==opponent)){
                out = 1;
                break;
            }
        }
    }
    return out;
}


int check_B4_AtoD(Evaluate *eval,int i,int j,int role);
int check_B4_AtoD(Evaluate *eval,int i,int j,int role){//���б��Ļ��Ļ��߳�??
    int count=0;
    int out=0;
    int check_available;
    int check_con = 0;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i - 4 > 0 ? i - 4 : 0;//��鿪ʼλ���Ƿ�Խ??0
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i + 4 < 14 ? i + 4 : 14;//������λ���Ƿ�Խ??14
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(check_B4_str_AtoD(eval,i,j,role)){//�����⵽һ����Ч������??, ֱ�ӷ���1
        return check_B4_str_AtoD(eval,i,j,role);
    }

    for (k = -4; k <= 0; k++) {//���б����Ƿ�??"�п�"��������
        if(i+k<0 || j+k<0)
            continue;//������ʼ���Ƿ�С��0

        count = 0;
        check_available = 0;
        check_con = 0;
        for(r = 0 ; r < 5; r++){
            if(eval->board[i+k+r][j+k+r] == role){
                count++;
                check_con++;
            }
            if(eval->board[i+k+r][j+k+r] == 0){
                check_con = 0;
            }
            if(check_con = 4){
                count = 0;
                break;
            }
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 4){//����������λ�������ҵ��ĸ�, ����Ƿ��п�λ
                for(q = 0; q < 5; q++){
                    if(eval->board[i+k+q][j+k+q]==0){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//��������λ���������ĸ��Ӳ��������λ����Ч�Ŀ�??
            out ++;
        }
    }
    return out;
}


int check_B4_str_AtoD(Evaluate *eval,int i,int j,int role);
int check_B4_str_AtoD(Evaluate *eval,int i,int j,int role){//������������??, ��û�а�??(i,j)��б��������
    int out = 0;
    int k, r;
    int opponent=opponent_select(role);

    int start_i = i - 3 > 0 ? i - 3 : 0;
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i + 3 < 14 ? i + 3 : 14;
    int end_j = j + 3 < 14 ? j + 3 : 14;

    for (k = -3; k <= 0; k++) {
        int check = 1;
        if(i+k<0 || j+k<0)
            continue;//�����ʼ��С??0, ֱ�ӽ�����һ��ѭ??

        for (r = 0; r < 4; r++) {
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] != opponent) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ�����Ч������??
            if(i+k-1>=0 && j+k-1>=0 && eval->board[i+k-1][j+k-1]==0 && (i+k+4>=SIZE || j+k+4>=SIZE || eval->board[i+k+4][j+k+4]==opponent)){//����Ƿ��п�λ, ��λ�����ǽ�??
                out = 1;
                break;
            }
            if(i+k+4<=14 && j+k+4<=14 && eval->board[i+k+4][j+k+4]==0 && (i+k-1<0 || j+k-1<0 || eval->board[i+k-1][j+k-1]==opponent)){
                out = 1;
                break;
            }
        }
    }
    return out;
}


int check_B4_BtoC(Evaluate *eval,int i,int j,int role);
int check_B4_BtoC(Evaluate *eval,int i,int j,int role){
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);
    int check_con = 0;

    int k,r,q;
    int start_i = i + 4 < 14 ? i + 4 : 14;//��鿪ʼλ���Ƿ�Խ??14
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i - 4 > 0 ? i - 4 : 0;//������λ���Ƿ�Խ??0
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(check_B4_str_BtoC(eval,i,j,role)){//�����⵽һ����Ч������??, ֱ�ӷ���1
        return check_B4_str_BtoC(eval,i,j,role);
    }

    for (k = -4; k <= 0; k++) {//���б����Ƿ�??"�п�"��������
        if(i-k>=SIZE || j+k<0)
            continue;//������ʼ���Ƿ�Ϸ�

        count = 0;
        check_con = 0;
        check_available = 0;
        for(r = 0 ; r < 5; r++){
            if(eval->board[i-k-r][j+k+r] == role){
                count++;
                check_con++;
            }
            if(eval->board[i-k-r][j+k+r] == 0){
                check_con = 0;
            }
            if(check_con == 4){
                count = 0;
                break;
            }
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 4){//����������λ�������ҵ��ĸ�, ����Ƿ��п�λ
                for(q = 0; q < 5; q++){
                    if(eval->board[i-k-q][j+k+q]==0){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//��������λ���������ĸ��Ӳ��������??
            out ++;
        }
    }
    return out;
}

int check_B4_str_BtoC(Evaluate *eval,int i,int j,int role);
int check_B4_str_BtoC(Evaluate *eval,int i,int j,int role){//������������??, ��û�а�??(i,j)��б��������
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);

    int start_i = i + 3 < 14 ? i + 3 : 14;
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i - 3 > 0 ? i - 3 : 0;
    int end_j = j + 3 < 14 ? j + 3 : 14;

    for (k = -3; k <= 0; k++) {
        int check = 1;
        if(i-k>=SIZE || j+k<0)
            continue;//�����ʼ�㲻�Ϸ�, ֱ�ӽ�����һ��ѭ??

        for (r = 0; r < 4; r++) {
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ�����Ч�ĳ���
            if(i-k+1<=14 && j+k-1>=0 && eval->board[i-k+1][j+k-1]==0 && (i-k-4<0 || j+k+4>=SIZE || eval->board[i-k-4][j+k+4]==opponent)){
                out = 1;
                break;
            }
            if(i-k-4>=0 && j+k+4<=14 && eval->board[i-k-4][j+k+4]==0 && (i-k+1>14 || j+k-1<0 || eval->board[i-k+1][j+k-1]==opponent)){
                out = 1;
                break;
            }
        }
    }
    return out;
}


int check_A3(Evaluate *eval, point *position, int role){
    int out=0;
    int i = position->x, j = position->y;
    out = check_A3_row(eval,i,j,role)+check_A3_col(eval,i,j,role)+check_A3_AtoD(eval,i,j,role)+check_A3_BtoC(eval,i,j,role);
    return out;
}

int check_A3_row(Evaluate *eval,int i,int j, int role);
int check_A3_row(Evaluate *eval,int i,int j, int role){//������Ļ���
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start = j - 3 > 0 ? j - 3 : 0;//��鿪ʼλ���Ƿ�Խ??0
    int end = j + 3 < 14 ? j + 3 : 14;//������λ���Ƿ�Խ??14

    if(check_A3_str_row(eval,i,j,role)){//�����⵽һ��������Ļ�??
        return check_A3_str_row(eval,i,j,role);
    }

    for (k = start; k <= j; k++) {//��������Ƿ�??"�п�"��������
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i][k+r] == role){
                count++;
            }
            if (k + r > end || eval->board[i][k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 3){//��������ĸ�λ�������ҵ�����, ����Ƿ��п�λ
                for(q = 0; q < 4; q++){
                    if(eval->board[i][k+q]==0){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//����������Ч�Ŀ�λ

            // upload_check_board(eval);
            if((k-1>=0) && eval->board[i][k-1]==0 && (k+4<=14) && eval->board[i][k+4]==0 ){//����������֮���γɵ��������Ƿ��ǻ���
                out++;
            }

        }
    }
    return out;
}

int check_A3_str_row(Evaluate *eval,int i,int j, int role);
int check_A3_str_row(Evaluate *eval,int i,int j, int role){//��������鵼�µĻ�??
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);

    int start = j - 2 > 0 ? j - 2 : 0;
    int end = j + 2 < 14 ? j + 2 : 14;

    for (k = start; k <= j; k++) {
        int check = 1;
        for (r = 0; r < 3; r++) {
            if (k + r > end || eval->board[i][k + r] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ���һ�������
            // upload_check_board(eval);
            if(k-1>=0 && eval->board[i][k-1]==0){//�����µ�����������
                eval->board[i][k-1]=role;
                if(k-2>=0 && eval->board[i][k-2]==0){//����֮�������������Ƿ���Ч
                    if(k+3<=14 && eval->board[i][k+3]==0 ){
                        out = 1;
                        eval->board[i][k-1]=0;
                        break;
                    }
                }
                eval->board[i][k-1]=0;
            }
            // upload_check_board(eval);
            if(k+3<=14 && eval->board[i][k+3]==0){//�����µ���������ұ�
                eval->board[i][k+3]=role;
                if(k+4<=14 && eval->board[i][k+4]==0){//����֮�����������Ҳ��Ƿ���??
                    if(k-1>=0 && eval->board[i][k-1]==0){
                        out = 1;
                        eval->board[i][k+3]=0;
                        break;
                    }
                }
                eval->board[i][k+3]=0;
            }
        }
    }
    return out;
}

int check_A3_col(Evaluate *eval,int i,int j, int role);
int check_A3_col(Evaluate *eval,int i,int j, int role){//�������Ļ���
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start = i - 3 > 0 ? i - 3 : 0;//��鿪ʼλ���Ƿ�Խ??0
    int end = i + 3 < 14 ? i + 3 : 14;//������λ���Ƿ�Խ??14

    if(check_A3_str_col(eval,i,j,role)){//�����⵽һ����Ч������??, ֱ�ӷ���1
        return check_A3_str_col(eval,i,j,role);
    }

    for (k = start; k <= i; k++) {//���������Ƿ�??"�п�"��������
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[k+r][j] == role){
                count++;
            }
            if (k + r > end || eval->board[k + r][j] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 3){//��������ĸ�λ�������ҵ�����, ����Ƿ��п�λ
                for(q = 0; q < 4; q++){
                    if(eval->board[k+q][j]==0 ){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//����������Ч�Ŀ�λ, �������λ������1
            eval->board[k+q][j]=role;
            // upload_check_board(eval);
            if((k-1>=0) && eval->board[k-1][j]==0&& (k+4<=14) && eval->board[k+4][j]==0){//����������֮���γɵ��������Ƿ��ǻ���
                out++;
            }
            eval->board[k+q][j]=0;
        }
    }
    return out;
}

int check_A3_str_col(Evaluate *eval,int i,int j, int role);
int check_A3_str_col(Evaluate *eval,int i,int j, int role){//��������鵼�µĻ�??
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);

    int start = i - 2 > 0 ? i - 2 : 0;
    int end = i + 2 < 14 ? i + 2 : 14;

    for (k = start; k <= i; k++) {
        int check = 1;
        for (r = 0; r < 3; r++) {
            if (k + r > end || eval->board[k + r][j] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ���һ�������
            // upload_check_board(eval);
            if(k-1>=0 && eval->board[k-1][j]==0){//�����µ�����������
                eval->board[k-1][j]=role;
                if(k-2>=0 && eval->board[k-2][j]==0){//����֮�������������Ƿ���Ч
                    if(k+3<=14 && eval->board[k+3][j]==0){
                        out = 1;
                        eval->board[k-1][j]=0;
                        break;
                    }
                }
                eval->board[k-1][j]=0;
            }
            if(k+3<=14 && eval->board[k+3][j]==0 ){//�����µ���������ұ�
                eval->board[k+3][j]=role;
                if(k+4<=14 && eval->board[k+4][j]==0){//����֮�����������Ҳ��Ƿ���??
                    if(k-1>=0 && eval->board[k-1][j]==0){
                        out = 1;
                        eval->board[k+3][j]=0;
                        break;
                    }
                }
                eval->board[k+3][j]=0;
            }
        }
    }
    return out;
}


int check_A3_AtoD(Evaluate *eval,int i,int j, int role);
int check_A3_AtoD(Evaluate *eval,int i,int j, int role){//���б��Ļ���
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i - 3 > 0 ? i - 3 : 0;//��鿪ʼλ���Ƿ�Խ??0
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i + 3 < 14 ? i + 3 : 14;//������λ���Ƿ�Խ??14
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(check_A3_str_AtoD(eval,i,j,role)){//�����⵽һ����Ч������??, ֱ�ӷ���1
        return check_A3_str_AtoD(eval,i,j,role);
    }

    for (k = -3; k <= 0; k++) {//���б����Ƿ�??"�п�"��������
        if(i+k<0 || j+k<0)
            continue;//������ʼ���Ƿ�С��0

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i+k+r][j+k+r] == role){
                count++;
            }
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 3){//��������ĸ�λ�������ҵ�����, ����Ƿ��п�λ
                for(q = 0; q < 4; q++){
                    if(eval->board[i+k+q][j+k+q]==0){//����п�??, ���������λ���ǽ���
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//����������Ч�Ŀ�λ, �������λ������1
            eval->board[i+k+q][j+k+q]=role;
            // upload_check_board(eval);
            if((i+k-1>=0) && (j+k-1>=0) && eval->board[i+k-1][j+k-1]==0&& (i+k+4<=14) && (j+k+4<=14) && eval->board[i+k+4][j+k+4]==0){//����������֮���γɵ��������Ƿ��ǻ���
                out++;
            }
            eval->board[i+k+q][j+k+q]=0;
        }
    }
    return out;
}

int check_A3_str_AtoD(Evaluate *eval,int i,int j, int role);
int check_A3_str_AtoD(Evaluate *eval,int i,int j, int role){//��������鵼�µĻ�??
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);

    int start_i = i - 2 > 0 ? i - 2 : 0;
    int start_j = j - 2 > 0 ? j - 2 : 0;
    int end_i = i + 2 < 14 ? i + 2 : 14;
    int end_j = j + 2 < 14 ? j + 2 : 14;

    for (k = -2; k <= 0; k++) {
        int check = 1;
        if(i+k<0 || j+k<0)
            continue;//�����ʼ��С??0, ֱ�ӽ�����һ��ѭ??

        for (r = 0; r < 3; r++) {
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//���������������, ����ȥ��������������Ƿ���һ�������
            // upload_check_board(eval);
            if(i+k-1>=0 && j+k-1>=0 && eval->board[i+k-1][j+k-1]==0){//�����µ������������??
                eval->board[i+k-1][j+k-1]=role;
                if(i+k-2>=0 && j+k-2>=0 && eval->board[i+k-2][j+k-2]==0){//����֮������������±��Ƿ���??
                    if(i+k+3<=14 && j+k+3<=14 && eval->board[i+k+3][j+k+3]==0){
                        out = 1;
                        eval->board[i+k-1][j+k-1]=0;
                        break;
                    }
                }
                eval->board[i+k-1][j+k-1]=0;
            }
            if(i+k+3<=14 && j+k+3<=14 && eval->board[i+k+3][j+k+3]==0){//�����µ������������??
                eval->board[i+k+3][j+k+3]=role;
                if(i+k+4<=14 && j+k+4<=14 && eval->board[i+k+4][j+k+4]==0){//����֮�������������ϱ��Ƿ���Ч
                    if(i+k-1>=0 && j+k-1>=0 && eval->board[i+k-1][j+k-1]==0){
                        out = 1;
                        eval->board[i+k+3][j+k+3]=0;
                        break;
                    }
                }
                eval->board[i+k+3][j+k+3]=0;
            }
        }
    }
    return out;
}

int check_A3_BtoC(Evaluate *eval,int i,int j, int role);
int check_A3_BtoC(Evaluate *eval,int i,int j, int role){//���б��Ļ���
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i + 3 < 14 ? i + 3 : 14;//��鿪ʼλ���Ƿ�Խ??14
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i - 3 > 0 ? i - 3 : 0;//������λ���Ƿ�Խ??0
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(check_A3_str_BtoC(eval,i,j,role)){//�����⵽һ����Ч������??, ֱ�ӷ���1
        return check_A3_str_BtoC(eval,i,j,role);
    }

    for (k = -3; k <= 0; k++) {//���б����Ƿ�??"�п�"��������
        if(i-k>=SIZE || j+k<0)
            continue;//������ʼ���Ƿ�Ϸ�

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i-k-r][j+k+r] == role){
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] == opponent) {//�����⵽�˱߽���߶Է�������, ֱ������ѭ��
                count = 0;
                break;
            }
        }
        if(count == 3){//��������ĸ�λ�������ҵ�����, ����Ƿ��п�λ
            for(q = 0; q < 4; q++){
                if(eval->board[i-k-q][j+k+q]==0){//����п�??, ���������λ���ǽ���
                    check_available = 1;
                    break;
                }
            }
        }
        if(check_available==1){//����������Ч�Ŀ�λ, �������λ������1
            eval->board[i-k-q][j+k+q]=role;
            // upload_check_board(eval);
            if((i-k+1<=14) && (j+k-1>=0) && eval->board[i-k+1][j+k-1]==0&& (i-k-4>=0) && (j+k+4<=14) && eval->board[i-k-4][j+k+4]==0 ){//����������֮���γɵ��������Ƿ��ǻ���
                out++;
            }
            eval->board[i-k-q][j+k+q]=0;
        }
    }
    return out;
}

int check_A3_str_BtoC(Evaluate *eval,int i,int j, int role);
int check_A3_str_BtoC(Evaluate *eval,int i,int j, int role){//��������鵼�µĻ�??
    int out = 0;
    int k, r;
    int opponent = opponent_select(role);
    int count = 0;

    int start_i = i + 2 < 14 ? i + 2 : 14;
    int start_j = j - 2 > 0 ? j - 2 : 0;
    int end_i = i - 2 > 0 ? i - 2 : 0;
    int end_j = j + 2 < 14 ? j + 2 : 14;

    for (k = -2; k <= 0; k++) {
        count = 0;
        if(i-k>=SIZE || j+k<0)
            continue;//�����ʼ�㲻�Ϸ�, ֱ�ӽ�����һ��ѭ??

        for (r = 0; r < 3; r++) {
            if (eval->board[i - k - r][j + k + r] == role) {
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] != role) {
                break;
            }
        }
        if (count==3) {//���������������, ����ȥ��������������Ƿ���һ�������
            // upload_check_board(eval);
            if(i-k+1<=14 && j+k-1>=0 && eval->board[i-k+1][j+k-1]==0){//����Ƿ��п�λ, ��λ�����ǽ�??
                eval->board[i-k+1][j+k-1]=role;
                if(i-k+2<=14 && j+k-2>=0 && eval->board[i-k+2][j+k-2]==0){//����Ƿ��п�λ, ��λ�����ǽ�??
                    if(i-k-3>=0 && j+k+3<=14 && eval->board[i-k-3][j+k+3]==0){
                        out = 1;
                        eval->board[i-k+1][j+k-1]=0;
                        break;
                    }
                }
                eval->board[i-k+1][j+k-1]=0;
            }
            if(i-k-3>=0 && j+k+3<=14 && eval->board[i-k-3][j+k+3]==0){//����Ƿ��п�λ, ��λ�����ǽ�??
                eval->board[i-k-3][j+k+3]=role;
                if(i-k-4>=0 && j+k+4<=14 && eval->board[i-k-4][j+k+4]==0){//����Ƿ��п�λ, ��λ�����ǽ�??
                    if(i-k+1<=14 && j+k-1>=0 && eval->board[i-k+1][j+k-1]==0){
                        out = 1;
                        eval->board[i-k-3][j+k+3]=0;
                        break;
                    }
                }
                eval->board[i-k-3][j+k+3]=0;
            }
        }
    }
    return out;
}


int check_B3(Evaluate *eval, point *position, int role);
int check_B3(Evaluate *eval, point *position, int role){
    int out = 0; // ���ڼ�¼����������
    int x, y;
    int dx, dy;
    int i, j;

    // �ĸ����򣺺����������Խ��ߡ����Խ���
    int direction[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (i = 0; i < 4; i++) {
        dx = direction[i][0];
        dy = direction[i][1];

        int count = 1; // ��ǰ���ӵļ���
        int block = 0; // �赲��
        int empty_count = 0; // ��λ����
        int max_empty = 1; // ���������λ��

        // ������
        for (j = 1; j <= 4; j++) {
            x = position->x + dx * j;
            y = position->y + dy * j;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
                if (eval->board[x][y] == role) {
                    count++;
                } else if (eval->board[x][y] == EMPTY) {
                    empty_count++;
                    if (empty_count > max_empty) {
                        break;
                    }
                } else {
                    block++;
                    break;
                }
            } else {
                block++;
                break;
            }
        }

        // ������
        empty_count = 0;
        for (j = 1; j <= 4; j++) {
            x = position->x - dx * j;
            y = position->y - dy * j;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
                if (eval->board[x][y] == role) {
                    count++;
                } else if (eval->board[x][y] == EMPTY) {
                    empty_count++;
                    if (empty_count > max_empty) {
                        break;
                    }
                } else {
                    block++;
                    break;
                }
            } else {
                block++;
                break;
            }
        }

        // �ж��Ƿ�Ϊ������������������
        if (count == 3 && block == 1) {
            out++;
        }
    }
    return out;
}

int check_A2(Evaluate *eval, point *position, int role);
int check_A2(Evaluate *eval, point *position, int role){
    int out = 0;
    int i, x, y;
    for (i = 0; i < 4; i++) {
        int dx = direction[i][0];
        int dy = direction[i][1];
        // �����??
        x = position->x + dx;
        y = position->y + dy;

        int count1 = 0;
        int empty1 = 0;
        int block1 = 0;
        int pivot1 = 0;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if(eval->board[x][y] == role){
                count1++;
            } else if (eval->board[x][y] == EMPTY) {
                if(count1==0){
                    int pivot1 = 1;
                }
                empty1++;
                if(empty1>=2)
                    break;
            } else {
                block1++;
                break;
            }
            x += dx;
            y += dy;
        }
        // �����??
        x = position->x - dx;
        y = position->y - dy;

        int count2 = 0;
        int empty2 = 0;
        int block2 = 0;
        int pivot2 = 0;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if(eval->board[x][y] == role){
                count2++;
            } else if (eval->board[x][y] == EMPTY){
                if(count2 == 0){
                    pivot2 = 1;
                }
                empty2++;
                if(empty2>=2)
                    break;
            } else {
                block2++;
                break;
            }
            x -= dx;
            y -= dy;
        }
        if (count1 == 1 && count2 == 0 && pivot1 == 0){//˵����һ���ж�����
            if ((empty1 >= 1 && empty2 == 2) || (empty1 ==2 && empty2 >=1)){
                out++;
            }
        }
        if (count1 == 1 && count2 == 0 && pivot1 == 1){//˵����һ�����пյ�
            if ((empty1 == 2 && empty2 >= 1)){
                out++;
            }
        }
        else if (count1 == 0 && count2 == 1 && pivot2 == 0){//˵����һ���ж�����
            if ((empty2 >= 1 && empty1 == 2) || (empty2 == 2  && empty1 >= 1)){
                out++;
            }
        }
        if (count1 == 0 && count2 == 1 && pivot2 == 1){//˵����һ�����пյ�
            if ((empty2 == 2 && empty1 >= 1)){
                out++;
            }
        }
    }
    return out;
}

int check_B2(Evaluate *eval, point *position, int role);
int check_B2(Evaluate *eval, point *position, int role) {
    int out = 0; // ���ڼ�¼�߶�������
    int x, y;

    // �ĸ����򣺺����������Խ��ߡ����Խ���
    int direction[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (int i = 0; i < 4; i++) {
        int dx = direction[i][0];
        int dy = direction[i][1];

        // ��ʼ��������
        int count1 = 0, count2 = 0;
        int empty1 = 0, empty2 = 0;
        int block1 = 0, block2 = 0;
        int pivot1 = 0, pivot2 = 0;

        // �����飨�Ҳࣩ
        x = position->x + dx;
        y = position->y + dy;

        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (eval->board[x][y] == role) {
                count1++;
            } else if (eval->board[x][y] == EMPTY) {
                if (count1 == 0) {
                    pivot1 = 1;
                }
                empty1++;
                if (empty1 >= 2) {
                    break;
                }
            } else {
                block1++;
                break;
            }
            x += dx;
            y += dy;
        }

        // ���߽����
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block1++;
        }

        // �����飨��ࣩ
        x = position->x - dx;
        y = position->y - dy;

        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (eval->board[x][y] == role) {
                count2++;
            } else if (eval->board[x][y] == EMPTY) {
                if (count2 == 0) {
                    pivot2 = 1;
                }
                empty2++;
                if (empty2 >= 2) {
                    break;
                }
            } else {
                block2++;
                break;
            }
            x -= dx;
            y -= dy;
        }

        // ���߽����
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block2++;
        }

        // �ж��Ƿ�Ϊ�߶�
        if (count1 == 1 && count2 == 0 && pivot1 == 0) { // ����������
            if ((empty1 == 0 && block1 == 1 && empty2 == 2) || (empty1 == 2 && block1 == 1 && empty2 == 0)) {
                out++;
            }
        }
        if (count1 == 1 && count2 == 0 && pivot1 == 1) { // ����
            if ((empty1 == 1 && block1 == 1 && empty2 >= 1) || (empty1 >= 1 && block1 == 1 && empty2 == 1)) {
                out++;
            }
        }
        if (count2 == 1 && count1 == 0 && pivot2 == 0) { // ����������
            if ((empty2 == 0 && block2 == 1 && empty1 == 2) || (empty2 == 2 && block2 == 1 && empty1 == 0)) {
                out++;
            }
        }
        if (count2 == 1 && count1 == 0 && pivot2 == 1) { // ����
            if ((empty2 == 1 && block2 == 1 && empty1 >= 1) || (empty2 >= 1 && block2 == 1 && empty1 == 1)) {
                out++;
            }
        }
    }
    return out;
}

void upload_check_board(Evaluate *eval){//����ǰ������״̬�ϴ������������
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            CheckBoard[i][j] = eval->board[i][j];
        }
    }
}

void upload_check_simple_board(Evaluate *eval){//����ǰ������״̬�ϴ������������
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            CheckSimpleBoard[i][j] = eval->board[i][j];
        }
    }
}

int check_simple_ban(Evaluate *eval,int i, int j, int role){//ֻ�к���ż���??
    int out = 0;
    if(role==1){
        upload_check_simple_board(eval);
        // printf("XXXXX  CHECKING  SIMPLE BAN :(%d,%d) XXXXX\n",i,j);
        int out = CheckSimpleBan(i,j);
        // printf("XXXXX  CHECKING SIMPLE BAN FINISHED:(%d,%d) XXXXX\n",i,j);
        return out;
    }
    else{
        return 0;
    }
    // return 0;
}

int check_ban(Evaluate *eval,int i, int j, int role){//ֻ�к���ż���??
    int out = 0;
    if(role==1 && check_simple_ban(eval, i,j,role)==1){
        upload_check_board(eval);
        //printf("XXXXX  CHECKING BAN :(%d,%d) XXXXX\n",i,j);
        int out = CheckBan(CHECKBAN_DEPTH,i,j);
        //printf("XXXXX  CHECKING BAN FINISHED:(%d,%d) XXXXX\n",i,j);
        return out;
    }
    else{
        return 0;
    }
    // return 0;
}