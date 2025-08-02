#ifndef MINIMAX_H
#define MINIMAX_H

#include "variable.h"
int minimax_alphaBeta(Evaluate *eval,int depth, int alpha, int beta, int role,  Path *path);
void sort(pscore*[],int left,int right);
void swap(pscore*[],int,int);
int minimax_alphaBeta_2(Evaluate *eval,int depth, int alpha, int beta, int role,  Path *path);

#endif