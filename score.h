#ifndef SCORE_H
#define SCORE_H
#define SIZE 15

int tempBoard[SIZE][SIZE];
int evaluate_board(Evaluate *eval, int role);
int check_in_board_range(point *position);
point evaluate_position(Evaluate *eval, point *position);
int calculate_score(Evaluate *eval, point *position, int role);
void store_board(Evaluate *eval);
void read_board(Evaluate *eval);
int check_must_block_attack(Evaluate *eval, int role);
#endif

