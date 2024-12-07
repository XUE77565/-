#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void initialDispay();


int wincheck();
int check_row(int i,int j);
int check_col(int i,int j);
int check_A_to_D(int i,int j);
int check_B_to_C(int i,int j);
int checkpoint(int i,int j);


int CheckBan(int i,int j);
void InnerBoardToCheckBoard();
int CheckBoard[SIZE][SIZE];
int player;
int input(int);

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组存储用于显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];



int main()

{

    initRecordBorard();    //初始化一个空棋盘
    innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
    initialDispay();
    displayBoard();          //显示棋盘
    

    player=1;
    int out=wincheck();
    int check=0;
    while(player!=0 && player!=3 && out==0){
        
        player=input(player);
        out=wincheck();
        
    }
    if(player==3){
        printf("出现禁手,白方胜");
        return 0;
    }
    if(out==1){
        printf("黑方获胜");
        return 0; 
    }
    else if (out==2){
        printf("白方获胜");
        return 0;
    }

    return 0;
}

//初始化一个空棋盘格局 
void initRecordBorard(void){
	//通过双重循环，将arrayForInnerBoardLayout清0
      int i=0, j=0;
      for(i=0; i<SIZE+1; i++){
        for(j=0; j<SIZE+1; j++){
            arrayForInnerBoardLayout[i][j]=0;
        }
      }
}

void initialDispay(){//第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    int i,j;
        for(i=0; i<SIZE; i++){
            for(j=0; j<SIZE*CHARSIZE+1; j++){
                arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
            }
        }

}

void innerLayoutToDisplayArray(void){//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
	
    
	//第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
    int c;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                if((c=arrayForInnerBoardLayout[i][j])!=0){
                    switch(c){
                        case 1:
                            arrayForDisplayBoard[SIZE-1-i][2*j]=play1Pic[0];
                            arrayForDisplayBoard[SIZE-1-i][2*j+1]=play1Pic[1];
                            break;
                        case 2:
                            arrayForDisplayBoard[SIZE-1-i][2*j]=play2Pic[0];
                            arrayForDisplayBoard[SIZE-1-i][2*j+1]=play2Pic[1];
                            break;
                    }
                }
            }
        }
	

 
}



//显示棋盘格局 
void displayBoard(void){
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将arrayForDisplayBoard输出到屏幕上
    int i,j;
        for(i=0; i<SIZE; i++){
            if(i<6){
                printf("%d %s\n",15-i,arrayForDisplayBoard[i]);
            }
            else{
                printf("%d  %s\n",15-i,arrayForDisplayBoard[i]);
            }
        }
	
    printf("\n");
	//第三步：输出最下面的一行字母A B .... 
    printf("    ");
         for(j=0; 2*j<SIZE*CHARSIZE-1; j++){
            printf("%c ",('A'+j));
         }
         printf("\n");
} 

void InnerBoardToCheckBoard(){//将心中的棋盘转化为用于检查禁手的棋盘
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            CheckBoard[i][j]=arrayForInnerBoardLayout[i][j];
        }
    }
}


int input(int player){
    printf("请输入下子位置如:12 h 如果要结束， 请输入88\n");
    int check;
    int r;
    char c;
    int *p=&player;
    scanf("%d",&r);
    if(r==88){return 0;}
    scanf("%c",&c);
    r=r-1;
    int n;
    n=c-'a';
    if(n<0||r<0 ||r>=SIZE || n>=SIZE || arrayForInnerBoardLayout[r][n]!=0){
        printf("输入的位置不合法，请重新输入\n");
        // printf("%d\n",arrayForDisplayBoard[r][n]);
        if(player==1){return 1;}
        else{return 2;}
    }
    else{
        innerLayoutToDisplayArray();
        arrayForInnerBoardLayout[r][n]=player;
        InnerBoardToCheckBoard();//将用于检查的棋盘和心中的棋盘同步
        if(player==1){
            arrayForDisplayBoard[SIZE-r-1][2*n]=play1CurrentPic[0];
            arrayForDisplayBoard[SIZE-r-1][2*n+1]=play1CurrentPic[1];
            displayBoard();//展示棋盘
            if(CheckBan(r,n)==1){
                return 3;
            }
            return 2;
        }

        else{
            arrayForDisplayBoard[SIZE-r-1][2*n]=play2CurrentPic[0];
            arrayForDisplayBoard[SIZE-r-1][2*n+1]=play2CurrentPic[1];
            displayBoard();
            return 1;
            }
    }
}

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

    // 妫�鏌ヤ綅缃? j 鐨勫乏鍙充袱渚ф渶澶? 4 涓綅缃?
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

    // 妫�鏌ヤ綅缃? j 鐨勫乏鍙充袱渚ф渶澶? 4 涓綅缃?
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

        if(start_i >= SIZE || start_j < 0)
            continue;

  
        if(start_i - 4 < 0 || start_j + 4 >= SIZE)
            continue;

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
