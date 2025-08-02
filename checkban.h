
#ifndef CHECKBAN_H
#define CHECKBAN_H
#define SIZE 15

extern int CheckBoard[SIZE][SIZE];
int CheckBan(int depth,int i,int j);
int CheckMulti3(int depth,int i,int j);
int CheckMulti4(int depth,int i,int j);
int CheckLong(int depth,int i, int j);

int CheckLongRow(int depth,int,int);
int CheckLongCol(int depth,int,int);
int CheckLongAtoD(int depth,int,int);
int CheckLongBtoC(int depth,int,int);

int Check4Row(int depth,int i,int j);
int Check4StrRow(int depth,int i,int j);
int Check4Col(int depth,int i,int j);
int Check4StrCol(int depth,int i,int j);
int Check4AtoD(int depth,int i,int j);
int Check4StrAtoD(int depth,int i,int j);
int Check4BtoC(int depth,int i,int j);
int Check4StrBtoC(int depth,int i,int j);

int Check3Row(int depth,int i,int j);
int Check3StrRow(int depth,int i,int j);
int Check3Col(int depth,int i,int j);
int Check3StrCol(int depth,int i,int j);
int Check3AtoD(int depth,int i,int j);
int Check3StrAtoD(int depth,int i,int j);
int Check3BtoC(int depth,int i,int j);
int Check3StrBtoC(int depth,int i,int j);
#endif
