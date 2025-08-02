/*
中国科学院大学wcg五子棋期末大作业
作者：薛翼舟
以下为主函数
*/
#include "wincheck.h"
#include "checkban.h"
#include "variable.h"
#include "shape.h"
#include "score.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 2


int human_input(int);
int main()

{
    system("clear");
    initRecordBorard();    //初始化一个空棋盘
    innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
    initialDispay();
    // displayBoard();          //显示棋盘
    printf("欢迎来到五子棋游戏, 制作者： 2306薛翼舟\n");
    printf("\n");
    printf("请选择游戏模式：\n");
    printf("\n");
    printf("人人对战模式请输入1\n");
    printf("人机对战请输入2\n");
    printf("\n");
    printf("请输入：");

    int out=0;
    int player;

    int mode;
    scanf("%d",&mode);
    displayBoard();
    if(mode==1){
        player=1;
        while(player!=0 && player!=3 && out==0){
            player=human_input(player);
            out=wincheck();
        }
        if(out==1){
            printf("黑方获胜");
            return 0; 
        }
        else if (out==2){
            printf("白方获胜");
            return 0;
        }
        if(player==3){
            printf("出现禁手,白方胜");
            return 0;
        }
    }
    
    if(mode==2){
        printf("请选择先后手,先手输入1,后手输入2\n");
        printf("\n");
        printf("请输入：");
        int mode2;
        scanf("%d",&mode2);//表示选择了模式
        if(mode2 == 1){
            human_type=1;
            ai_type=2;
            while(1){
                player = human_input(1);
                while (player == 1){
                    player = human_input(1);
                }
                if(player==3){
                    break;
                }
                out = wincheck();
                if(out){
                    break;
                }
                if(player==0){
                    return 0;
                }
                printf("正在计算，请稍候...\n");
                ai_place(2);
                out = wincheck();
                if(out){
                    break;
                }
            }
            if(out == 1){
                printf("黑方获胜");
                return 0;
            }
            else if(out == 2){
                printf("白方获胜");
                return 0;
            }
            else if(player == 3){
                printf("出现禁手,白方胜");
                return 0;
            }
        }
        else{
            human_type=2;
            ai_type=1;
            arrayForInnerBoardLayout[7][7] = 1;//如果是ai先手, 则直接下在天元
            innerLayoutToDisplayArray();
            displayBoard();
            human_input(2);
            while(1){
                printf("AI is calculating\n");
                player = ai_place(1);
                if(player==3){
                    break;
                }
                out = wincheck();
                if(out){
                    break;
                }
                player = human_input(2);
                while (player == 2){
                    player = human_input(2);
                }
                out = wincheck();
                if(out){
                    break;
                }
                if(player==0){
                    return 0;
                }
            }
            if(out == 1){
                printf("黑方获胜");
                return 0;
            }
            else if(out == 2){
                printf("白方获胜");
                return 0;
            }
            else if(player == 3){
                printf("出现禁手,白方胜");
                return 0;
            }
        }
    }
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
	// system("clear");   //清屏  
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


int human_input(int player){
    printf("请输入下子位置如:12 h 如果要结束， 请输入88\n");
    int check;
    int r;
    char c;
    scanf("%d",&r);
    if(r==88){return 0;}
    scanf("%c",&c);
    r=r-1;
    int n;
    n=c-'a';
    printf("%d\n",arrayForDisplayBoard[r][n]);
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
        // Evaluate eval;
        // memcpy(eval.board, arrayForInnerBoardLayout, sizeof(arrayForInnerBoardLayout));
        // // int score = evaluate_board(&eval, player);
        // // printf("current score:%d\n",score);
        // point p = {r,n};
        // shape shpe;
        // shpe = check_shape(&eval,&p,player);
        if(player==1){
            arrayForDisplayBoard[SIZE-r-1][2*n]=play1CurrentPic[0];
            arrayForDisplayBoard[SIZE-r-1][2*n+1]=play1CurrentPic[1];
            displayBoard();//展示棋盘
            if(CheckBan(CHECKBAN_DEPTH,r,n)==1){
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

int ai_place(int role) {
    printf("CURRENTMODE DEPTH=%d\n",(minimax_mode==0)?4:2);
    clock_t time1 = clock();
    innerLayoutToDisplayArray();
    Evaluate eval;
    memcpy(eval.board, arrayForInnerBoardLayout, sizeof(arrayForInnerBoardLayout));//将当前棋盘格局上传到eval中
    int score;
    Path path;
    if(check_absolute_win(&eval,role)){
        printf("ABSOLUTE WI N DETECTED\n");
        displayBoard();
    }
    else if(check_must_block_attack(&eval,role)){
        printf("HAVE TO BLOCK DETECTED\n");
        displayBoard();
    }
    else if(minimax_mode==0){
        score = minimax_alphaBeta(&eval, DEPTH, -INFTY, INFTY, role, &path);
        clock_t time2 = clock();
        arrayForInnerBoardLayout[path.moves[0][0]][path.moves[0][1]] = role;//将ai的落子放到棋盘中
        if(role == 1){
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]]=play1CurrentPic[0];
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]+1]=play1CurrentPic[1];
        }
        else{
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]]=play2CurrentPic[0];
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]+1]=play2CurrentPic[1];
        }
        displayBoard();
        printf("AI score: %d\n", score);
        printf("AI places at (%d,%c)\n",path.moves[0][0]+1,'A'+path.moves[0][1]);
        double time = ((double) (time2 - time1) / CLOCKS_PER_SEC);
        if(time >= 15.0){minimax_mode = 1;printf("CHANGING_MODE:%d\n",minimax_mode);}
        printf("USED_TIME :%f s\n",time);
        printf("CHECKBAN_TIME :%f s\n",time_checkban);
        printf("SIMPLEBAN_TIME :%f s\n",time_simpleban);
        printf("SHAPE_TIME :%f s\n",time_shape);
        // printf("check shape number:%d\n",pivot);
        // printf("check board times:%d\n",times_board);
        time_checkban=0,time_simpleban=0,time_shape=0,pivot=0,time = 0;
    }
    else{
        score = minimax_alphaBeta_2(&eval, DEPTH2, -INFTY, INFTY, role, &path);
        clock_t time2 = clock();
        arrayForInnerBoardLayout[path.moves[0][0]][path.moves[0][1]] = role;//将ai的落子放到棋盘中
        if(role == 1){
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]]=play1CurrentPic[0];
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]+1]=play1CurrentPic[1];
        }
        else{
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]]=play2CurrentPic[0];
            arrayForDisplayBoard[SIZE-path.moves[0][0]-1][2*path.moves[0][1]+1]=play2CurrentPic[1];
        }
        displayBoard();
        printf("AI score: %d\n", score);
        printf("AI places at (%d,%c)\n",path.moves[0][0]+1,'A'+path.moves[0][1]);
        double time = ((double) (time2 - time1) / CLOCKS_PER_SEC);
        printf("USED_TIME :%f s\n",time);
        printf("CHECKBAN_TIME :%f s\n",time_checkban);
        printf("SIMPLEBAN_TIME :%f s\n",time_simpleban);
        printf("SHAPE_TIME :%f s\n",time_shape);
        // printf("check shape number:%d\n",pivot);
        // printf("check board times:%d\n",times_board);
        time_checkban=0,time_simpleban=0,time_shape=0,pivot=0,time=0;
    }

    if(role==1){
        InnerBoardToCheckBoard();
        if(CheckBan(CHECKBAN_DEPTH,path.moves[0][0],path.moves[0][1])==1){
            return 3;
        }
        else
            return 0;
    }
    else{
        return 0;
    }
}

