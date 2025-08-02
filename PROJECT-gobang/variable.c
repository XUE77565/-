/*
作者：薛翼舟
以下是所有用到的变量
*/

#include "variable.h"
#include <time.h>
 int CheckBoard[SIZE][SIZE];
 void initRecordBorard(void);
 void innerLayoutToDisplayArray(void);
 void displayBoard(void);
 void initialDispay();
int player;
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

int arrayForInnerBoardLayout[SIZE][SIZE];

int direction[4][2]={
	{1,0},
	{0,1},
	{1,1},
	{1,-1}
};

int ai_type;
int human_type;


double time_checkban=0;
double time_simpleban=0;
double time_shape=0;
int pivot=0;
int times_board=0;
int minimax_mode = 0;