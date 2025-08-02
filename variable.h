#ifndef VARIABLE_H
#define VARIABLE_H
#define SIZE 15
#define CHARSIZE 2
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define SCORE_BAN -10000000
#define SCORE_A5 10000000
#define SCORE_A4 1000
#define SCORE_B4 250
#define SCORE_A3 340
#define SCORE_B3 15
#define SCORE_A2 1
#define SCORE_B2 0
#define DEPTH 4
#define DEPTH2 2
#define CHECKBAN_DEPTH 4
#define INFTY 1000000000
#define DEFENSE_RATE_BLACK 0.95
#define DEFENSE_RATE_WHITE 0.95
#define MAXLINE 1000
extern int CheckBoard[SIZE][SIZE];

extern void initRecordBorard(void);
extern void innerLayoutToDisplayArray(void);
extern void displayBoard(void);
extern void initialDispay();
extern int player;
extern char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1];

//此数组存储用于显示的棋盘 
extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
extern char play1Pic[];//黑棋子;
extern char play1CurrentPic[]; 

extern char play2Pic[];//白棋子;
extern char play2CurrentPic[];

//此数组用于记录当前的棋盘的格局 
extern int arrayForInnerBoardLayout[SIZE][SIZE];

typedef struct{
    int size;
    int board[SIZE][SIZE];
}Evaluate;
typedef struct{
    int x;
    int y;
}point;
//表示所记录的点

typedef struct{
    int A5;//五连
    int A4;//活四
    int B4;//冲四
    int A3;//活三
    int B3;//眠三
    int C3;//跳三
    int A2;//活二
    int B2;//眠二
}shape;

//表示记录这个点的形状
extern int ai_type;
extern int human_type;
typedef struct {
    int moves[DEPTH][3];
}Path;

typedef struct{
    int score;
    point position;
}pscore;

extern int direction[4][2];

extern double time_checkban;
extern double time_simpleban;
extern double time_shape;

extern int pivot;
extern int times_board;

extern int minimax_mode;

#endif