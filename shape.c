/*
作者：薛翼舟
以下为对一个点检查棋型的函数
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
        count = 1; // 包含当前??
        int dx = direction[i][0];
        int dy = direction[i][1];
        // 正向检??
        x = position->x + dx;
        y = position->y + dy;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && eval->board[x][y] == role) {
            // printf("nihao123\n");
            count++;
            x += dx;
            y += dy;
        }
        // 反向检??
        x = position->x - dx;
        y = position->y - dy;
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && eval->board[x][y] == role) {
            count++;
            x -= dx;
            y -= dy;
        }
        if (count >= 5) {
            return 1; // 存在五连??
        }
    }
    return 0; // 不存在五连珠
}


//检查活四的函数
int check_A4(Evaluate *eval, point *position, int role) {
    int i, count, block;
    int out = 0; // 用于记录活四的数??
    int x, y;

    for (i = 0; i < 4; i++) {
        count = 1; // 包含当前??
        block = 0; // 记录两端是否被阻??

        int dx = direction[i][0];
        int dy = direction[i][1];

        // 正向检??
        x = position->x + dx;
        y = position->y + dy;

        int empty = 0; // 用于标记是否遇到空位

        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (eval->board[x][y] == role) {
                count++;
            } 
            else if (eval->board[x][y] == EMPTY) {
                empty++;
            } 
            else {
                // 遇到对方棋子，方向被阻挡
                block++;
                break;
            }
            x += dx;
            y += dy;
        }

        // 超出边界，方向被阻挡
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block++;
        }

        // 反向检查，逻辑同上
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

        // 判断是否形成活四
        if (count == 4 && block == 0 && empty == 2) {
            out++;
        }
    }

    return out;
}




//对于这种冲四, 考虑之前在checkban中写的检查四的函??
int check_B4(Evaluate *eval, point *position, int role){
    int out=0;
    int i = position->x, j = position->y;
    out = check_B4_row(eval,i,j,role)+check_B4_col(eval,i,j,role)+check_B4_AtoD(eval,i,j,role)+check_B4_BtoC(eval,i,j,role);
    return out;
}

int check_B4_row(Evaluate *eval,int i,int j, int role);
int check_B4_row(Evaluate *eval,int i,int j, int role){//检查横向的活四或者冲??
    int count=0;
    int out=0;
    int check_available;
    int check_con=0;

    int k,r,q;
    int start = j - 4 > 0 ? j - 4 : 0;//检查开始位置是否越??0
    int end = j + 4 < 14 ? j + 4 : 14;//检查结束位置是否越??14
    int opponent = opponent_select(role);
    
    if(check_B4_str_row(eval,i,j,role)){//如果检测到一个四连珠的冲??
        return check_B4_str_row(eval,i,j,role);
    }

    for (k = start; k <= j; k++) {//检测横向的是否??"中空"的四连珠
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
            if (k + r > end || eval->board[i][k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(eval->board[i][k+q]==0){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个里面有有效的空??
            out ++;
        }
    }
    return out;
}

int check_B4_str_row(Evaluate *eval,int i,int j, int role);
int check_B4_str_row(Evaluate *eval,int i,int j, int role){//检查四连珠的情??, 有没有包??(i,j)的横向四连珠冲四
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

        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是冲??
            if(k-1>=0 && eval->board[i][k-1]==0 && (k+4>=SIZE || eval->board[i][k+4]==opponent)){//检查是否有空位, 空位不能是禁??
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
int check_B4_col(Evaluate *eval,int i,int j, int role){//检查纵向的活四或者冲四
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);
    int check_con = 0;

    int k,r,q;
    int start = i - 4 > 0 ? i - 4 : 0;//检查开始位置是否越过0
    int end = i + 4 < 14 ? i + 4 : 14;//检查结束位置是否越过14

    if(check_B4_str_col(eval,i,j,role)){//如果检测到一个有效的四连珠, 直接返回1
        return check_B4_str_col(eval,i,j,role);
    }

    for (k = start; k <= i; k++) {//检测纵向的是否有"中空"的四连珠
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
            if (k + r > end || eval->board[k + r][j] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(eval->board[k+q][j]==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个里面有有效的空位
            out ++;
        }
    }
    return out;
}

int check_B4_str_col(Evaluate *eval,int i,int j,int role);
int check_B4_str_col(Evaluate *eval,int i,int j,int role){//检查四连珠的情??, 有没有包??(i,j)的纵向四连珠
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
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连??
            if(k-1>=0 && eval->board[k-1][j]==0 &&(k+4>=SIZE || eval->board[k+4][j]==opponent)){//检查是否有空位, 空位不能是禁??
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
int check_B4_AtoD(Evaluate *eval,int i,int j,int role){//检查斜向的活四或者冲??
    int count=0;
    int out=0;
    int check_available;
    int check_con = 0;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i - 4 > 0 ? i - 4 : 0;//检查开始位置是否越??0
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i + 4 < 14 ? i + 4 : 14;//检查结束位置是否越??14
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(check_B4_str_AtoD(eval,i,j,role)){//如果检测到一个有效的四连??, 直接返回1
        return check_B4_str_AtoD(eval,i,j,role);
    }

    for (k = -4; k <= 0; k++) {//检测斜向的是否??"中空"的四连珠
        if(i+k<0 || j+k<0)
            continue;//检验起始点是否小于0

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
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(eval->board[i+k+q][j+k+q]==0){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个空位是有效的空??
            out ++;
        }
    }
    return out;
}


int check_B4_str_AtoD(Evaluate *eval,int i,int j,int role);
int check_B4_str_AtoD(Evaluate *eval,int i,int j,int role){//检查四连珠的情??, 有没有包??(i,j)的斜向四连珠
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
            continue;//如果起始点小??0, 直接进行下一个循??

        for (r = 0; r < 4; r++) {
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] != opponent) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连??
            if(i+k-1>=0 && j+k-1>=0 && eval->board[i+k-1][j+k-1]==0 && (i+k+4>=SIZE || j+k+4>=SIZE || eval->board[i+k+4][j+k+4]==opponent)){//检查是否有空位, 空位不能是禁??
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
    int start_i = i + 4 < 14 ? i + 4 : 14;//检查开始位置是否越??14
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i - 4 > 0 ? i - 4 : 0;//检查结束位置是否越??0
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(check_B4_str_BtoC(eval,i,j,role)){//如果检测到一个有效的四连??, 直接返回1
        return check_B4_str_BtoC(eval,i,j,role);
    }

    for (k = -4; k <= 0; k++) {//检测斜向的是否??"中空"的四连珠
        if(i-k>=SIZE || j+k<0)
            continue;//检验起始点是否合法

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
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(eval->board[i-k-q][j+k+q]==0){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个空??
            out ++;
        }
    }
    return out;
}

int check_B4_str_BtoC(Evaluate *eval,int i,int j,int role);
int check_B4_str_BtoC(Evaluate *eval,int i,int j,int role){//检查四连珠的情??, 有没有包??(i,j)的斜向四连珠
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
            continue;//如果起始点不合法, 直接进行下一个循??

        for (r = 0; r < 4; r++) {
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的冲四
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
int check_A3_row(Evaluate *eval,int i,int j, int role){//检查横向的活三
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start = j - 3 > 0 ? j - 3 : 0;//检查开始位置是否越??0
    int end = j + 3 < 14 ? j + 3 : 14;//检查结束位置是否越??14

    if(check_A3_str_row(eval,i,j,role)){//如果检测到一个三连珠的活??
        return check_A3_str_row(eval,i,j,role);
    }

    for (k = start; k <= j; k++) {//检测横向的是否??"中空"的三连珠
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i][k+r] == role){
                count++;
            }
            if (k + r > end || eval->board[i][k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(eval->board[i][k+q]==0){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//如果这个是有效的空位

            // upload_check_board(eval);
            if((k-1>=0) && eval->board[i][k-1]==0 && (k+4<=14) && eval->board[i][k+4]==0 ){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }

        }
    }
    return out;
}

int check_A3_str_row(Evaluate *eval,int i,int j, int role);
int check_A3_str_row(Evaluate *eval,int i,int j, int role){//检查三连珠导致的活??
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
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            // upload_check_board(eval);
            if(k-1>=0 && eval->board[i][k-1]==0){//考虑下到三连珠的左边
                eval->board[i][k-1]=role;
                if(k-2>=0 && eval->board[i][k-2]==0){//下完之后四连珠的左边是否有效
                    if(k+3<=14 && eval->board[i][k+3]==0 ){
                        out = 1;
                        eval->board[i][k-1]=0;
                        break;
                    }
                }
                eval->board[i][k-1]=0;
            }
            // upload_check_board(eval);
            if(k+3<=14 && eval->board[i][k+3]==0){//考虑下到三连珠的右边
                eval->board[i][k+3]=role;
                if(k+4<=14 && eval->board[i][k+4]==0){//下完之后的四连珠的右侧是否有??
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
int check_A3_col(Evaluate *eval,int i,int j, int role){//检查纵向的活三
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start = i - 3 > 0 ? i - 3 : 0;//检查开始位置是否越??0
    int end = i + 3 < 14 ? i + 3 : 14;//检查结束位置是否越??14

    if(check_A3_str_col(eval,i,j,role)){//如果检测到一个有效的三连??, 直接返回1
        return check_A3_str_col(eval,i,j,role);
    }

    for (k = start; k <= i; k++) {//检测纵向的是否??"中空"的三连珠
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[k+r][j] == role){
                count++;
            }
            if (k + r > end || eval->board[k + r][j] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(eval->board[k+q][j]==0 ){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//如果这个是有效的空位, 在这个空位上填上1
            eval->board[k+q][j]=role;
            // upload_check_board(eval);
            if((k-1>=0) && eval->board[k-1][j]==0&& (k+4<=14) && eval->board[k+4][j]==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
            eval->board[k+q][j]=0;
        }
    }
    return out;
}

int check_A3_str_col(Evaluate *eval,int i,int j, int role);
int check_A3_str_col(Evaluate *eval,int i,int j, int role){//检查三连珠导致的活??
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
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            // upload_check_board(eval);
            if(k-1>=0 && eval->board[k-1][j]==0){//考虑下到三连珠的左边
                eval->board[k-1][j]=role;
                if(k-2>=0 && eval->board[k-2][j]==0){//下完之后四连珠的左边是否有效
                    if(k+3<=14 && eval->board[k+3][j]==0){
                        out = 1;
                        eval->board[k-1][j]=0;
                        break;
                    }
                }
                eval->board[k-1][j]=0;
            }
            if(k+3<=14 && eval->board[k+3][j]==0 ){//考虑下到三连珠的右边
                eval->board[k+3][j]=role;
                if(k+4<=14 && eval->board[k+4][j]==0){//下完之后的四连珠的右侧是否有??
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
int check_A3_AtoD(Evaluate *eval,int i,int j, int role){//检查斜向的活三
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i - 3 > 0 ? i - 3 : 0;//检查开始位置是否越??0
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i + 3 < 14 ? i + 3 : 14;//检查结束位置是否越??14
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(check_A3_str_AtoD(eval,i,j,role)){//如果检测到一个有效的三连??, 直接返回1
        return check_A3_str_AtoD(eval,i,j,role);
    }

    for (k = -3; k <= 0; k++) {//检测斜向的是否??"中空"的三连珠
        if(i+k<0 || j+k<0)
            continue;//检验起始点是否小于0

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i+k+r][j+k+r] == role){
                count++;
            }
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(eval->board[i+k+q][j+k+q]==0){//如果有空??, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//如果这个是有效的空位, 在这个空位上填上1
            eval->board[i+k+q][j+k+q]=role;
            // upload_check_board(eval);
            if((i+k-1>=0) && (j+k-1>=0) && eval->board[i+k-1][j+k-1]==0&& (i+k+4<=14) && (j+k+4<=14) && eval->board[i+k+4][j+k+4]==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
            eval->board[i+k+q][j+k+q]=0;
        }
    }
    return out;
}

int check_A3_str_AtoD(Evaluate *eval,int i,int j, int role);
int check_A3_str_AtoD(Evaluate *eval,int i,int j, int role){//检查三连珠导致的活??
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
            continue;//如果起始点小??0, 直接进行下一个循??

        for (r = 0; r < 3; r++) {
            if (i + k + r > end_i || j + k + r > end_j || eval->board[i + k + r][j + k + r] != role) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            // upload_check_board(eval);
            if(i+k-1>=0 && j+k-1>=0 && eval->board[i+k-1][j+k-1]==0){//考虑下到三连珠的左下??
                eval->board[i+k-1][j+k-1]=role;
                if(i+k-2>=0 && j+k-2>=0 && eval->board[i+k-2][j+k-2]==0){//下完之后四连珠的左下边是否有??
                    if(i+k+3<=14 && j+k+3<=14 && eval->board[i+k+3][j+k+3]==0){
                        out = 1;
                        eval->board[i+k-1][j+k-1]=0;
                        break;
                    }
                }
                eval->board[i+k-1][j+k-1]=0;
            }
            if(i+k+3<=14 && j+k+3<=14 && eval->board[i+k+3][j+k+3]==0){//考虑下到三连珠的右上??
                eval->board[i+k+3][j+k+3]=role;
                if(i+k+4<=14 && j+k+4<=14 && eval->board[i+k+4][j+k+4]==0){//下完之后的四连珠的右上边是否有效
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
int check_A3_BtoC(Evaluate *eval,int i,int j, int role){//检查斜向的活三
    int count=0;
    int out=0;
    int check_available;
    int opponent = opponent_select(role);

    int k,r,q;
    int start_i = i + 3 < 14 ? i + 3 : 14;//检查开始位置是否越??14
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i - 3 > 0 ? i - 3 : 0;//检查结束位置是否越??0
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(check_A3_str_BtoC(eval,i,j,role)){//如果检测到一个有效的三连??, 直接返回1
        return check_A3_str_BtoC(eval,i,j,role);
    }

    for (k = -3; k <= 0; k++) {//检测斜向的是否??"中空"的三连珠
        if(i-k>=SIZE || j+k<0)
            continue;//检验起始点是否合法

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(eval->board[i-k-r][j+k+r] == role){
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] == opponent) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
            for(q = 0; q < 4; q++){
                if(eval->board[i-k-q][j+k+q]==0){//如果有空??, 并且这个空位不是禁手
                    check_available = 1;
                    break;
                }
            }
        }
        if(check_available==1){//如果这个是有效的空位, 在这个空位上填上1
            eval->board[i-k-q][j+k+q]=role;
            // upload_check_board(eval);
            if((i-k+1<=14) && (j+k-1>=0) && eval->board[i-k+1][j+k-1]==0&& (i-k-4>=0) && (j+k+4<=14) && eval->board[i-k-4][j+k+4]==0 ){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
            eval->board[i-k-q][j+k+q]=0;
        }
    }
    return out;
}

int check_A3_str_BtoC(Evaluate *eval,int i,int j, int role);
int check_A3_str_BtoC(Evaluate *eval,int i,int j, int role){//检查三连珠导致的活??
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
            continue;//如果起始点不合法, 直接进行下一个循??

        for (r = 0; r < 3; r++) {
            if (eval->board[i - k - r][j + k + r] == role) {
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || eval->board[i - k - r][j + k + r] != role) {
                break;
            }
        }
        if (count==3) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            // upload_check_board(eval);
            if(i-k+1<=14 && j+k-1>=0 && eval->board[i-k+1][j+k-1]==0){//检查是否有空位, 空位不能是禁??
                eval->board[i-k+1][j+k-1]=role;
                if(i-k+2<=14 && j+k-2>=0 && eval->board[i-k+2][j+k-2]==0){//检查是否有空位, 空位不能是禁??
                    if(i-k-3>=0 && j+k+3<=14 && eval->board[i-k-3][j+k+3]==0){
                        out = 1;
                        eval->board[i-k+1][j+k-1]=0;
                        break;
                    }
                }
                eval->board[i-k+1][j+k-1]=0;
            }
            if(i-k-3>=0 && j+k+3<=14 && eval->board[i-k-3][j+k+3]==0){//检查是否有空位, 空位不能是禁??
                eval->board[i-k-3][j+k+3]=role;
                if(i-k-4>=0 && j+k+4<=14 && eval->board[i-k-4][j+k+4]==0){//检查是否有空位, 空位不能是禁??
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
    int out = 0; // 用于记录眠三的数量
    int x, y;
    int dx, dy;
    int i, j;

    // 四个方向：横向、纵向、主对角线、副对角线
    int direction[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (i = 0; i < 4; i++) {
        dx = direction[i][0];
        dy = direction[i][1];

        int count = 1; // 当前棋子的计数
        int block = 0; // 阻挡数
        int empty_count = 0; // 空位计数
        int max_empty = 1; // 允许的最大空位数

        // 正向检查
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

        // 反向检查
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

        // 判断是否为眠三（包含跳眠三）
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
        // 正向检??
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
        // 反向检??
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
        if (count1 == 1 && count2 == 0 && pivot1 == 0){//说明这一侧有二连珠
            if ((empty1 >= 1 && empty2 == 2) || (empty1 ==2 && empty2 >=1)){
                out++;
            }
        }
        if (count1 == 1 && count2 == 0 && pivot1 == 1){//说明这一侧有中空的
            if ((empty1 == 2 && empty2 >= 1)){
                out++;
            }
        }
        else if (count1 == 0 && count2 == 1 && pivot2 == 0){//说明这一侧有二连珠
            if ((empty2 >= 1 && empty1 == 2) || (empty2 == 2  && empty1 >= 1)){
                out++;
            }
        }
        if (count1 == 0 && count2 == 1 && pivot2 == 1){//说明这一侧有中空的
            if ((empty2 == 2 && empty1 >= 1)){
                out++;
            }
        }
    }
    return out;
}

int check_B2(Evaluate *eval, point *position, int role);
int check_B2(Evaluate *eval, point *position, int role) {
    int out = 0; // 用于记录眠二的数量
    int x, y;

    // 四个方向：横向、纵向、主对角线、副对角线
    int direction[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};

    for (int i = 0; i < 4; i++) {
        int dx = direction[i][0];
        int dy = direction[i][1];

        // 初始化计数器
        int count1 = 0, count2 = 0;
        int empty1 = 0, empty2 = 0;
        int block1 = 0, block2 = 0;
        int pivot1 = 0, pivot2 = 0;

        // 正向检查（右侧）
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

        // 检查边界情况
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block1++;
        }

        // 反向检查（左侧）
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

        // 检查边界情况
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            block2++;
        }

        // 判断是否为眠二
        if (count1 == 1 && count2 == 0 && pivot1 == 0) { // 连续二连珠
            if ((empty1 == 0 && block1 == 1 && empty2 == 2) || (empty1 == 2 && block1 == 1 && empty2 == 0)) {
                out++;
            }
        }
        if (count1 == 1 && count2 == 0 && pivot1 == 1) { // 跳二
            if ((empty1 == 1 && block1 == 1 && empty2 >= 1) || (empty1 >= 1 && block1 == 1 && empty2 == 1)) {
                out++;
            }
        }
        if (count2 == 1 && count1 == 0 && pivot2 == 0) { // 连续二连珠
            if ((empty2 == 0 && block2 == 1 && empty1 == 2) || (empty2 == 2 && block2 == 1 && empty1 == 0)) {
                out++;
            }
        }
        if (count2 == 1 && count1 == 0 && pivot2 == 1) { // 跳二
            if ((empty2 == 1 && block2 == 1 && empty1 >= 1) || (empty2 >= 1 && block2 == 1 && empty1 == 1)) {
                out++;
            }
        }
    }
    return out;
}

void upload_check_board(Evaluate *eval){//将当前的棋盘状态上传到检查棋盘中
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            CheckBoard[i][j] = eval->board[i][j];
        }
    }
}

void upload_check_simple_board(Evaluate *eval){//将当前的棋盘状态上传到检查棋盘中
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            CheckSimpleBoard[i][j] = eval->board[i][j];
        }
    }
}

int check_simple_ban(Evaluate *eval,int i, int j, int role){//只有黑棋才检查禁??
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

int check_ban(Evaluate *eval,int i, int j, int role){//只有黑棋才检查禁??
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