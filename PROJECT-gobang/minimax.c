/*
作者：薛翼舟
以下为minimax-alphabeta的函数
*/

#include "variable.h"
#include "shape.h"
#include "score.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

int minimax_alphaBeta(Evaluate *eval, int depth, int alpha, int beta, int role, Path *path) {
    static int abc = 0;

    int check = 0;
    int temp;
    point p;
    pscore **score_array = (pscore **)malloc(MAXLINE * sizeof(pscore *));
    for (int i = 0; i < MAXLINE; i++) {
        score_array[i] = (pscore *)malloc(sizeof(pscore));
    }
    int k = 0;

    if (depth == 0) {
        times_board++;
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return evaluate_board(eval, role);
    }

    if (role == ai_type) {
        int bestScore = -INFTY;

        for (int i = 0; i < SIZE; i++) {
            if (check == 1) {
                break;
            }
            for (int j = 0; j < SIZE; j++) {
                p.x = i, p.y = j;
                if (eval->board[i][j] == EMPTY && check_around(eval, &p)) {
                    eval->board[i][j] = ai_type;
                    score_array[k]->score = calculate_score(eval, &p, ai_type); // 对有效的点进行排序，来进一步优化ab剪枝
                    score_array[k]->position = p;
                    eval->board[i][j] = EMPTY;
                    k++;
                }
            }
        }

        sort(score_array, 0, k - 1); // 对有效的点排序

        for (int l = 0; l < k; l++) {
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = ai_type;
            if (bestScore < (temp = minimax_alphaBeta(eval, depth - 1, alpha, beta, human_type, path))) { // 迭代更新
                path->moves[DEPTH - depth][0] = score_array[l]->position.x; // 将ai的落子存到path中
                path->moves[DEPTH - depth][1] = score_array[l]->position.y;
                path->moves[DEPTH - depth][2] = ai_type;
                bestScore = temp;
            }
            alpha = max(alpha, bestScore);
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = EMPTY;
            if (beta <= alpha) {
                check = 1;
                break; // Beta剪枝
            }
        }
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return bestScore;
    } else {
        int bestScore = +INFTY;
        for (int i = 0; i < SIZE; i++) {
            if (check == 1) {
                break;
            }
            for (int j = 0; j < SIZE; j++) {
                p.x = i, p.y = j;
                if (eval->board[i][j] == EMPTY && check_around(eval, &p)) {
                    eval->board[i][j] = human_type;
                    score_array[k]->score = calculate_score(eval, &p, human_type); // 对有效的点进行排序，来进一步优化ab剪枝
                    score_array[k]->position = p;
                    eval->board[i][j] = EMPTY;
                    k++;
                }
            }
        }

        sort(score_array, 0, k - 1); // 对有效的点排序

        for (int l = 0; l < k; l++) {
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = human_type;
            if (bestScore > (temp = minimax_alphaBeta(eval, depth - 1, alpha, beta, ai_type, path))) { // 迭代更新
                path->moves[DEPTH - depth][0] = score_array[l]->position.x; // 将ai的落子存到path中
                path->moves[DEPTH - depth][1] = score_array[l]->position.y;
                path->moves[DEPTH - depth][2] = human_type;
                bestScore = temp;
            }
            beta = min(beta, bestScore);
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = EMPTY;
            if (beta <= alpha) {
                check = 1;
                break; // Beta剪枝
            }
        }
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return bestScore;
    }
}

int minimax_alphaBeta_2(Evaluate *eval, int depth, int alpha, int beta, int role, Path *path) {
    static int abc = 0;

    int check = 0;
    int temp;
    point p;
    pscore **score_array = (pscore **)malloc(MAXLINE * sizeof(pscore *));
    for (int i = 0; i < MAXLINE; i++) {
        score_array[i] = (pscore *)malloc(sizeof(pscore));
    }
    int k = 0;

    if (depth == 0) {
        times_board++;
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return evaluate_board(eval, role);
    }

    if (role == ai_type) {
        int bestScore = -INFTY;

        for (int i = 0; i < SIZE; i++) {
            if (check == 1) {
                break;
            }
            for (int j = 0; j < SIZE; j++) {
                p.x = i, p.y = j;
                if (eval->board[i][j] == EMPTY && check_around(eval, &p)) {
                    eval->board[i][j] = ai_type;
                    score_array[k]->score = calculate_score(eval, &p, ai_type); // 对有效的点进行排序，来进一步优化ab剪枝
                    score_array[k]->position = p;
                    eval->board[i][j] = EMPTY;
                    k++;
                }
            }
        }

        sort(score_array, 0, k - 1); // 对有效的点排序

        for (int l = 0; l < k; l++) {
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = ai_type;
            if (bestScore < (temp = minimax_alphaBeta_2(eval, depth - 1, alpha, beta, human_type, path))) { // 迭代更新
                path->moves[DEPTH2 - depth][0] = score_array[l]->position.x; // 将ai的落子存到path中
                path->moves[DEPTH2 - depth][1] = score_array[l]->position.y;
                path->moves[DEPTH2 - depth][2] = ai_type;
                bestScore = temp;
            }
            alpha = max(alpha, bestScore);
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = EMPTY;
            if (beta <= alpha) {
                check = 1;
                break; // Beta剪枝
            }
        }
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return bestScore;
    } else {
        int bestScore = +INFTY;
        for (int i = 0; i < SIZE; i++) {
            if (check == 1) {
                break;
            }
            for (int j = 0; j < SIZE; j++) {
                p.x = i, p.y = j;
                if (eval->board[i][j] == EMPTY && check_around(eval, &p)) {
                    eval->board[i][j] = human_type;
                    score_array[k]->score = calculate_score(eval, &p, human_type); // 对有效的点进行排序，来进一步优化ab剪枝
                    score_array[k]->position = p;
                    eval->board[i][j] = EMPTY;
                    k++;
                }
            }
        }

        sort(score_array, 0, k - 1); // 对有效的点排序

        for (int l = 0; l < k; l++) {
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = human_type;
            if (bestScore > (temp = minimax_alphaBeta_2(eval, depth - 1, alpha, beta, ai_type, path))) { // 迭代更新
                path->moves[DEPTH2 - depth][0] = score_array[l]->position.x; // 将ai的落子存到path中
                path->moves[DEPTH2 - depth][1] = score_array[l]->position.y;
                path->moves[DEPTH2 - depth][2] = human_type;
                bestScore = temp;
            }
            beta = min(beta, bestScore);
            eval->board[score_array[l]->position.x][score_array[l]->position.y] = EMPTY;
            if (beta <= alpha) {
                check = 1;
                break; // Beta剪枝
            }
        }
        for (int i = 0; i < MAXLINE; i++) {
            free(score_array[i]);
        }
        free(score_array);
        return bestScore;
    }
}

void sort(pscore *p[], int left, int right) {
    int i, last;
    if (left >= right) {
        return;
    }
    swap(p, left, (right + left) / 2); // 快速排序，将中间元素排到前面
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (p[i]->score > p[left]->score) {
            swap(p, ++last, i);
        }
    }
    swap(p, left, last); // 左边是比中间大的，右边是比中间小的
    sort(p, left, last - 1);
    sort(p, last + 1, right);
}

void swap(pscore *p[], int i, int j) {
    pscore *temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}