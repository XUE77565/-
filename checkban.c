#include<stdio.h>
#define SIZE 15

int arrayForInnerBoardLayout[SIZE][SIZE];
int ArrayForCheckBan[SIZE][SIZE];
int CheckBan(int i,int j);
int CheckMulti3(int i,int j);
int CheckMulti4(int i,int j);
int CheckLong(int i, int j);

int CheckLongRow(int,int);
int CheckLongCol(int,int);
int CheckLongAtoD(int,int);
int CheckLongBtoC(int,int);


int CheckBan(int i,int j){
    if(CheckMulti3(i,j)==1 || CheckMulti4(i,j)==1 || CheckLong(i,j)==1){
        return 1;
    }
    else
    return 0;
}

int CheckLong(int i,int j){
    if((CheckLongRow(i,j)!=0) ||(CheckLongCol(i,j)!=0) ||(CheckLongAtoD(i,j)!=0) ||(CheckLongBtoC(i,j)!=0)){
        return 1;
    }
    else
    return 0;
}

int CheckLongRow(int i,int j){
    int out=0;
    int ban;
    int k,r;
    int start = j-5>0? j-5: 0;//检查开始位置是否超出0
    int end = j+5<14? j+5: 14;//检查结束位置是否超出14
    for(k=start; k<=j; k++){
        ban=1;
        for(r=0;r<6;r++){
            if(k+r>end || (arrayForInnerBoardLayout[i][k+r]!=1)){
                ban=0;//检查是否有个数为6的长连，长度比6大的同样也可以判断，因为有6的长连是充要的，如果没有长连，跳出内不循环，改变开始位置继续判断。
                break;
            }
        }
        if(ban==1){
                out = ban;
                break;
        }
    }
    return out;
}

int CheckLongCol(int i,int j){
    int out=0;
    int ban;
    int k,r;
    int start = i-5>0? i-5: 0;//检查开始位置是否超出0
    int end = i+5<14? i+5: 14;//检查结束位置是否超出14
    for(k=start; k<=i; k++){
        ban=1;
        for(r=0;r<6;r++){
            if(k+r>end || (arrayForInnerBoardLayout[k+r][j]!=1)){
                ban=0;//检查是否有个数为6的长连，长度比6大的同样也可以判断，因为有6的长连是充要的，如果没有长连，跳出内不循环，改变开始位置继续判断。
                break;
            }
        }
        if(ban==1){
                out = ban;
                break;
        }
    }
    return out;
}

int CheckLongAtoD(int i,int j){//判断斜方向上的长连禁手，基本思路类似
    int ban;
    int out = 0;
    int k;

    for(k = -5; k <= 0; k++){
        ban=1;
        int r;
        int start_i = i + k;
        int start_j = j + k;

        
        if(start_i < 0 || start_j < 0)
            continue;

       
        if(start_i + 5 >= SIZE|| start_j + 5 >= SIZE)
            continue;

    
        for(r = 0; r < 6; r++){
            if(arrayForInnerBoardLayout[start_i + r][start_j + r] != 1){
                ban=0;
                break;
            }
        }
        if(ban == 1){
            out = 1;
            break;
        }
    }
    return out;
}

int CheckLongBtoC(int i,int j){//判断斜方向上的长连禁手，基本思路类似
    int ban;
    int out = 0;
    int k;

    for(k = -5; k <= 0; k++){
        ban=1;
        int r;
        int start_i = i - k;
        int start_j = j + k;

        
        if(start_i >= SIZE || start_j < 0)
            continue;

       
        if(start_i - 5 < 0|| start_j + 5 >= SIZE)
            continue;

    
        for(r = 0; r < 6; r++){
            if(arrayForInnerBoardLayout[start_i - r][start_j + r] != 1){
                ban=0;
                break;
            }
        }
        if(ban == 1){
            out = 1;
            break;
        }
    }
    return out;
}


int Check4Row(int i,int j);
int Check4StrRow(int i,int j);
int Check4Col(int i,int j);
int Check4StrCol(int i,int j);
int Check4AtoD(int i,int j);
int Check4StrAtoD(int i,int j);
int Check4BtoC(int i,int j);
int Check4StrBtoC(int i,int j);


int CheckMulti4(int i, int j){
    int count;
    count = Check4Row(i,j)+Check4Col(i,j)+Check4AtoD(i,j)+Check4BtoC(i,j);
    if(count>=2){
        return 1;
    }
    else
        return 0;
}

int Check4Row(int i,int j){//检查横向的活四或者冲四
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start = j - 4 > 0 ? j - 4 : 0;//检查开始位置是否越过0
    int end = j + 4 < 14 ? j + 4 : 14;//检查结束位置是否越过14

    if(Check4StrRow(i,j)==1){//如果检测到一个有效的四连珠, 直接返回1
        return 1;
    }

    for (k = start; k <= j; k++) {//检测横向的是否有"中空"的四连珠
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 5; r++){
            if(arrayForInnerBoardLayout[i][k+r] == 1){
                count++;
            }
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(arrayForInnerBoardLayout[i][k+q]==0 && CheckBan(i,k+q)==0){//如果有空位, 并且这个空位不是禁手
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


int Check4StrRow(int i,int j){//检查四连珠的情况, 有没有包含(i,j)的横向四连珠
    int out = 0;
    int k, r;

    int start = j - 3 > 0 ? j - 3 : 0;
    int end = j + 3 < 14 ? j + 3 : 14;

    for (k = start; k <= j; k++) {
        int check = 1;
        for (r = 0; r < 4; r++) {
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连珠
            if(k-1>=0 && arrayForInnerBoardLayout[i][k-1]==0 && CheckBan(i,k-1)==0){//检查是否有空位, 空位不能是禁手
                out = 1;
                break;
            }
            if(k+4<=14 && arrayForInnerBoardLayout[i][k+4]==0 && CheckBan(i,k+4)==0){
                out = 1;
                break;
            }
        }
    }
    return out;
}

int Check4Col(int i,int j){//检查纵向的活四或者冲四
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start = i - 4 > 0 ? i - 4 : 0;//检查开始位置是否越过0
    int end = i + 4 < 14 ? i + 4 : 14;//检查结束位置是否越过14

    if(Check4StrCol(i,j)==1){//如果检测到一个有效的四连珠, 直接返回1
        return 1;
    }

    for (k = start; k <= i; k++) {//检测纵向的是否有"中空"的四连珠
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 5; r++){
            if(arrayForInnerBoardLayout[k+r][j] == 1){
                count++;
            }
            if (k + r > end || arrayForInnerBoardLayout[k + r][j] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(arrayForInnerBoardLayout[k+q][j]==0 && CheckBan(k+q,j)==0){//如果有空位, 并且这个空位不是禁手
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

int Check4StrCol(int i,int j){//检查四连珠的情况, 有没有包含(i,j)的纵向四连珠
    int out = 0;
    int k, r;

    int start = i - 3 > 0 ? i - 3 : 0;
    int end = i + 3 < 14 ? i + 3 : 14;

    for (k = start; k <= i; k++) {
        int check = 1;
        for (r = 0; r < 4; r++) {
            if (k + r > end || arrayForInnerBoardLayout[k + r][j] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连珠
            if(k-1>=0 && arrayForInnerBoardLayout[k-1][j]==0 && CheckBan(k-1,j)==0){//检查是否有空位, 空位不能是禁手
                out = 1;
                break;
            }
            if(k+4<=14 && arrayForInnerBoardLayout[k+4][j]==0 && CheckBan(k+4,j)==0){
                out = 1;
                break;
            }
        }
    }
    return out;
}

int Check4AtoD(int i,int j){//检查斜向的活四或者冲四
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start_i = i - 4 > 0 ? i - 4 : 0;//检查开始位置是否越过0
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i + 4 < 14 ? i + 4 : 14;//检查结束位置是否越过14
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(Check4StrAtoD(i,j)==1){//如果检测到一个有效的四连珠, 直接返回1
        return 1;
    }

    for (k = -4; k <= 0; k++) {//检测斜向的是否有"中空"的四连珠
        if(i+k<0 || j+k<0)
            continue;//检验起始点是否小于0

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 5; r++){
            if(arrayForInnerBoardLayout[i+k+r][j+k+r] == 1){
                count++;
            }
            if (i + k + r > end_i || j + k + r > end_j || arrayForInnerBoardLayout[i + k + r][j + k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(arrayForInnerBoardLayout[i+k+q][j+k+q]==0 && CheckBan(i+k+q,j+k+q)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个空位是有效的空位
            out ++;
        }
    }
    printf("out=%d\n",out);
    return out;
}

int Check4StrAtoD(int i,int j){//检查四连珠的情况, 有没有包含(i,j)的斜向四连珠
    int out = 0;
    int k, r;

    int start_i = i - 3 > 0 ? i - 3 : 0;
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i + 3 < 14 ? i + 3 : 14;
    int end_j = j + 3 < 14 ? j + 3 : 14;

    for (k = -3; k <= 0; k++) {
        int check = 1;
        if(i+k<0 || j+k<0)
            continue;//如果起始点小于0, 直接进行下一个循环

        for (r = 0; r < 4; r++) {
            if (i + k + r > end_i || j + k + r > end_j || arrayForInnerBoardLayout[i + k + r][j + k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连珠
            if(i+k-1>=0 && j+k-1>=0 && arrayForInnerBoardLayout[i+k-1][j+k-1]==0 && CheckBan(i+k-1,j+k-1)==0){//检查是否有空位, 空位不能是禁手
                out = 1;
                break;
            }
            if(i+k+4<=14 && j+k+4<=14 && arrayForInnerBoardLayout[i+k+4][j+k+4]==0 && CheckBan(i+k+4,j+k+4)==0){
                out = 1;
                break;
            }
        }
    }
    return out;
}

int Check4BtoC(int i,int j){
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start_i = i + 4 < 14 ? i + 4 : 14;//检查开始位置是否越过14
    int start_j = j - 4 > 0 ? j - 4 : 0;
    int end_i = i - 4 > 0 ? i - 4 : 0;//检查结束位置是否越过0
    int end_j = j + 4 < 14 ? j + 4 : 14;

    if(Check4StrBtoC(i,j)==1){//如果检测到一个有效的四连珠, 直接返回1
        return 1;
    }

    for (k = -4; k <= 0; k++) {//检测斜向的是否有"中空"的四连珠
        if(i-k>=SIZE || j+k<0)
            continue;//检验起始点是否合法

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 5; r++){
            if(arrayForInnerBoardLayout[i-k-r][j+k+r] == 1){
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || arrayForInnerBoardLayout[i - k - r][j + k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 4){//如果在这五个位置里面找到四个, 检查是否有空位
                for(q = 0; q < 5; q++){
                    if(arrayForInnerBoardLayout[i-k-q][j+k+q]==0 && CheckBan(i-k-q,j+k+q)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(count==4 && check_available==1){//如果这五个位置里面有四个子并且这个空位
            out ++;
        }
    }
    return out;
}

int Check4StrBtoC(int i,int j){//检查四连珠的情况, 有没有包含(i,j)的斜向四连珠
    int out = 0;
    int k, r;

    int start_i = i + 3 < 14 ? i + 3 : 14;
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i - 3 > 0 ? i - 3 : 0;
    int end_j = j + 3 < 14 ? j + 3 : 14;

    for (k = -3; k <= 0; k++) {
        int check = 1;
        if(i-k>=SIZE || j+k<0)
            continue;//如果起始点不合法, 直接进行下一个循环

        for (r = 0; r < 4; r++) {
            if (i - k - r < end_i || j + k + r > end_j || arrayForInnerBoardLayout[i - k - r][j + k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有四连珠, 继续去检验这个四连珠是否是有效的四连珠
            if(i-k+1<=14 && j+k-1>=0 && arrayForInnerBoardLayout[i-k+1][j+k-1]==0 && CheckBan(i-k+1,j+k-1)==0){//检查是否有空位, 空位不能是禁手
                out = 1;
                break;
            }
            if(i-k-4>=0 && j+k+4<=14 && arrayForInnerBoardLayout[i-k-4][j+k+4]==0 && CheckBan(i-k-4,j+k+4)==0){
                out = 1;
                break;
            }
        }
    }
    return out;
}


int Check3Row(int i,int j);
int Check3StrRow(int i,int j);
int Check3Col(int i,int j);
int Check3StrCol(int i,int j);
int Check3AtoD(int i,int j);
int Check3StrAtoD(int i,int j);
int Check3BtoC(int i,int j);
int Check3StrBtoC(int i,int j);

int CheckMulti3(int i,int j){
    int count;
    count = Check3Row(i,j)+Check3Col(i,j)+Check3AtoD(i,j)+Check3BtoC(i,j);
    if(count>=2){
        return 1;
    }
    else
        return 0;
}

int Check3Row(int i,int j){
    int count=0;
    int out=0;
    int check_available;
    int available4;

    int k,r,q;
    int start = j - 3 > 0 ? j - 3 : 0;//检查开始位置是否越过0
    int end = j + 3 < 14 ? j + 3 : 14;//检查结束位置是否越过14

    if(Check3StrRow(i,j)==1){//如果检测到一个有效的三连珠, 直接返回1
        return 1;
    }

    for (k = start; k <= j; k++) {//检测横向的是否有"中空"的三连珠, 如果出现有可能的活三, 那么四个里面一定有三个
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){//检查四个位置里面是否有三个
            if(arrayForInnerBoardLayout[i][k+r] == 1){
                count++;
            }
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查这个是否是真活三
                for(q = 0; q < 4; q++){
                    if(arrayForInnerBoardLayout[i][k+q]==0 && CheckBan(i,k+q)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }//经过这个判断, 所以这个活三能形成四连珠
                }
        }
        if(check_available==1){//如果这四个位置里面有三个子并且这个里面有有效的空位
            if(k-1>=0 && arrayForInnerBoardLayout[i][k-1]==0 && CheckBan(i,k-1)==0 && k+4<=14 && arrayForInnerBoardLayout[i][k+4]==0 && CheckBan(i,k+4)==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
        }
    }
    return available4;
}

int Check3StrRow(int i,int j){//检查是否有三连珠导致的活三
    int out = 0;
    int k, r;

    int start = j - 2 > 0 ? j - 2 : 0;
    int end = j + 2 < 14 ? j + 2 : 14;

    for (k = start; k <= j; k++) {
        int check = 1;
        for (r = 0; r < 3; r++) {
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            if(k-1>=0 && arrayForInnerBoardLayout[i][k-1]==0 && CheckBan(i,k-1)==0){//考虑下到三连珠的左边
                if(k-2>=0 && arrayForInnerBoardLayout[i][k-2]==0 && CheckBan(i,k-2)==0){//下完之后四连珠的左边是否有效
                    if(k+3<=14 && arrayForInnerBoardLayout[i][k+3]==0 && CheckBan(i,k+3)==0){
                        out = 1;
                        break;
                    }
                }
            }
            if(k+3<=14 && arrayForInnerBoardLayout[i][k+3]==0 && CheckBan(i,k+3)==0){//考虑下到三连珠的右边
                if(k+4<=14 && arrayForInnerBoardLayout[i][k+4]==0 && CheckBan(i,k+4)==0){//下完之后的四连珠的右侧是否有效
                    if(k-1>=0 && arrayForInnerBoardLayout[i][k-1]==0 && CheckBan(i,k-1)==0){
                        out = 1;
                        break;
                    }
                }
            }
        }
    }
    return out;
}

int Check3Col(int i,int j){
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start = i - 3 > 0 ? i - 3 : 0;//检查开始位置是否越过0
    int end = i + 3 < 14 ? i + 3 : 14;//检查结束位置是否越过14

    if(Check3StrCol(i,j)==1){//如果检测到一个有效的三连珠, 直接返回1
        return 1;
    }

    for (k = start; k <= i; k++) {//检测纵向的是否有"中空"的三连珠
        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(arrayForInnerBoardLayout[k+r][j] == 1){
                count++;
            }
            if (k + r > end || arrayForInnerBoardLayout[k + r][j] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(arrayForInnerBoardLayout[k+q][j]==0 && CheckBan(k+q,j)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//如果这四个位置里面有三个子并且这个里面有有效的空位
            if(k-1>=0 && arrayForInnerBoardLayout[k-1][j]==0 && CheckBan(k-1,j)==0 && k+4<=14 && arrayForInnerBoardLayout[k+4][j]==0 && CheckBan(k+4,j)==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
        }
    }
    return out;
}

int Check3StrCol(int i,int j){//检查是否有三连珠导致的活三
    int out = 0;
    int k, r;

    int start = i - 2 > 0 ? i - 2 : 0;
    int end = i + 2 < 14 ? i + 2 : 14;

    for (k = start; k <= i; k++) {
        int check = 1;
        for (r = 0; r < 3; r++) {
            if (k + r > end || arrayForInnerBoardLayout[k + r][j] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            if(k-1>=0 && arrayForInnerBoardLayout[k-1][j]==0 && CheckBan(k-1,j)==0){//考虑下到三连珠的左边
                if(k-2>=0 && arrayForInnerBoardLayout[k-2][j]==0 && CheckBan(k-2,j)==0){//下完之后四连珠的左边是否有效
                    if(k+3<=14 && arrayForInnerBoardLayout[k+3][j]==0 && CheckBan(k+3,j)==0){
                        out = 1;
                        break;
                    }
                }
            }
            if(k+3<=14 && arrayForInnerBoardLayout[k+3][j]==0 && CheckBan(k+3,j)==0){//考虑下到三连珠的右边
                if(k+4<=14 && arrayForInnerBoardLayout[k+4][j]==0 && CheckBan(k+4,j)==0){//下完之后的四连珠的右侧是否有效
                    if(k-1>=0 && arrayForInnerBoardLayout[k-1][j]==0 && CheckBan(k-1,j)==0){
                        out = 1;
                        break;
                    }
                }
            }
        }
    }
    return out;
}

int Check3AtoD(int i,int j){
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start_i = i - 3 > 0 ? i - 3 : 0;//检查开始位置是否越过0
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i + 3 < 14 ? i + 3 : 14;//检查结束位置是否越过14
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(Check3StrAtoD(i,j)==1){//如果检测到一个有效的三连珠, 直接返回1
        return 1;
    }

    for (k = -3; k <= 0; k++) {//检测斜向的是否有"中空"的三连珠
        if(i+k<0 || j+k<0)
            continue;//检验起始点是否合法

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(arrayForInnerBoardLayout[i+k+r][j+k+r] == 1){
                count++;
            }
            if (i + k + r > end_i || j + k + r > end_j || arrayForInnerBoardLayout[i + k + r][j + k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(arrayForInnerBoardLayout[i+k+q][j+k+q]==0 && CheckBan(i+k+q,j+k+q)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){//如果这四个位置里面有三个子并且这个里面有有效的
            if((i+k-1>=0 && j+k-1>=0) && arrayForInnerBoardLayout[i+k-1][j+k-1]==0 && CheckBan(i+k-1,j+k-1)==0 && (i+k+4<=14 && j+k+4<=14) && 
            arrayForInnerBoardLayout[i+k+4][j+k+4]==0 && CheckBan(i-k+4,j-k+4)==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
        }
    }   
    return out;
}

int Check3StrAtoD(int i,int j){//检查是否有三连珠导致的活三
    int out = 0;
    int k, r;

    int start_i = i - 2 > 0 ? i - 2 : 0;
    int start_j = j - 2 > 0 ? j - 2 : 0;
    int end_i = i + 2 < 14 ? i + 2 : 14;
    int end_j = j + 2 < 14 ? j + 2 : 14;

    for (k = -2; k <= 0; k++) {
        int check = 1;
        if(i+k<0 || j+k<0)
            continue;//如果起始点不合法, 直接进行下一个循环

        for (r = 0; r < 3; r++) {
            if (i + k + r > end_i || j + k + r > end_j || arrayForInnerBoardLayout[i + k + r][j + k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            if(i+k-1>=0 && j+k-1>=0 && arrayForInnerBoardLayout[i+k-1][j+k-1]==0 && CheckBan(i+k-1,j+k-1)==0){//检查是否有空位, 空位不能是禁手
                if(i+k-2>=0 && j+k-2>=0 && arrayForInnerBoardLayout[i+k-2][j+k-2]==0 && CheckBan(i+k-2,j+k-2)==0){//检查是否有空位, 空位不能是禁手
                    if(i+k+3<=14 && j+k+3<=14 && arrayForInnerBoardLayout[i+k+3][j+k+3]==0 && CheckBan(i+k+3,j+k+3)==0){
                        out = 1;
                        break;
                    }
                }
            }
            if(i+k+3<=14 && j+k+3<=14 && arrayForInnerBoardLayout[i+k+3][j+k+3]==0 && CheckBan(i+k+3,j+k+3)==0){//检查是否有空位, 空位不能是禁手
                if(i+k+4<=14 && j+k+4<=14 && arrayForInnerBoardLayout[i+k+4][j+k+4]==0 && CheckBan(i+k+4,j+k+4)==0){//检查是否有空位, 空位不能是禁手
                    if(i+k-1>=0 && j+k-1>=0 && arrayForInnerBoardLayout[i+k-1][j+k-1]==0 && CheckBan(i+k-1,j+k-1)==0){
                        out = 1;
                        break;
                    }
                }
            }
        }
    }
    return out;
}

int Check3BtoC(int i,int j){
    int count=0;
    int out=0;
    int check_available;

    int k,r,q;
    int start_i = i + 3 < 14 ? i + 3 : 14;//检查开始位置是否越过14
    int start_j = j - 3 > 0 ? j - 3 : 0;
    int end_i = i - 3 > 0 ? i - 3 : 0;//检查结束位置是否越过0
    int end_j = j + 3 < 14 ? j + 3 : 14;

    if(Check3StrBtoC(i,j)==1){//如果检测到一个有效的三连珠, 直接返回1
        return 1;
    }

    for (k = -3; k <= 0; k++) {//检测斜向的是否有"中空"的三连珠
        if(i-k>=SIZE || j+k<0)
            continue;//检验起始点是否合法

        count = 0;
        check_available = 0;
        for(r = 0 ; r < 4; r++){
            if(arrayForInnerBoardLayout[i-k-r][j+k+r] == 1){
                count++;
            }
            if (i - k - r < end_i || j + k + r > end_j || arrayForInnerBoardLayout[i - k - r][j + k + r] == 2) {//如果检测到了边界或者对方的棋子, 直接跳出循环
                count = 0;
                break;
            }
        }
        if(count == 3){//如果在这四个位置里面找到三个, 检查是否有空位
                for(q = 0; q < 4; q++){
                    if(arrayForInnerBoardLayout[i-k-q][j+k+q]==0 && CheckBan(i-k-q,j+k+q)==0){//如果有空位, 并且这个空位不是禁手
                        check_available = 1;
                        break;
                    }
                }
        }
        if(check_available==1){
            if((i-k+1<=14 && j+k-1>=0) && arrayForInnerBoardLayout[i-k+1][j+k-1]==0 && CheckBan(i-k+1,j+k-1)==0 && (i-k-4>=0 && j+k+4<=14) && 
            arrayForInnerBoardLayout[i-k-4][j+k+4]==0 && CheckBan(i-k-4,j+k+4)==0){//检查这个活三之后形成的四连珠是否是活四
                out++;
            }
        }
    }
    return out;
}

int Check3StrBtoC(int i,int j){//检查是否有三连珠导致的活三
    int out = 0;
    int k, r;

    int start_i = i + 2 < 14 ? i + 2 : 14;
    int start_j = j - 2 > 0 ? j - 2 : 0;
    int end_i = i - 2 > 0 ? i - 2 : 0;
    int end_j = j + 2 < 14 ? j + 2 : 14;

    for (k = -2; k <= 0; k++) {
        int check = 1;
        if(i-k>=SIZE || j+k<0)
            continue;//如果起始点不合法, 直接进行下一个循环

        for (r = 0; r < 3; r++) {
            if (i - k - r < end_i || j + k + r > end_j || arrayForInnerBoardLayout[i - k - r][j + k + r] != 1) {
                check = 0;
                break;
            }
        }
        if (check) {//如果发现有三连珠, 继续去检验这个三连珠是否是一个真活三
            if(i-k+1<=14 && j+k-1>=0 && arrayForInnerBoardLayout[i-k+1][j+k-1]==0 && CheckBan(i-k+1,j+k-1)==0){//检查是否有空位, 空位不能是禁手
                if(i-k+2<=14 && j+k-2>=0 && arrayForInnerBoardLayout[i-k+2][j+k-2]==0 && CheckBan(i-k+2,j+k-2)==0){//检查是否有空位, 空位不能是禁手
                    if(i-k-3>=0 && j+k+3<=14 && arrayForInnerBoardLayout[i-k-3][j+k+3]==0 && CheckBan(i-k-3,j+k+3)==0){
                        out = 1;
                        break;
                    }
                }
            }
            if(i-k-3>=0 && j+k+3<=14 && arrayForInnerBoardLayout[i-k-3][j+k+3]==0 && CheckBan(i-k-3,j+k+3)==0){//检查是否有空位, 空位不能是禁手
                if(i-k-4>=0 && j+k+4<=14 && arrayForInnerBoardLayout[i-k-4][j+k+4]==0 && CheckBan(i-k-4,j+k+4)==0){//检查是否有空位, 空位不能是禁手
                    if(i-k+1<=14 && j+k-1>=0 && arrayForInnerBoardLayout[i-k+1][j+k-1]==0 && CheckBan(i-k+1,j+k-1)==0){
                        out = 1;
                        break;
                    }
                }
            }
        }
    }
    return out;
}