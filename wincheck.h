#ifndef WINCHECK_H
#define WINCHECK_H
#define SIZE 15
#include "variable.h"
int wincheck();
int check_row(int i,int j);
int check_col(int i,int j);
int check_A_to_D(int i,int j);
int check_B_to_C(int i,int j);
int check_absolute_win(Evaluate *eval, int role);

#endif