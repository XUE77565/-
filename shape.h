#ifndef SHAPE_C
#define SHAPE_C

void upload_check_board(Evaluate *eval);
int check_ban(Evaluate *eval,int i, int j, int role);
int check_ban_for3(int i,int j,int role);
int opponent_select(int role);
shape check_shape(Evaluate *eval, point *position, int role);
int check_A5(Evaluate *eval, point *position, int role);
int check_A4(Evaluate *eval, point *position, int role);
int check_B4_row(Evaluate *eval,int i,int j, int role);
int check_B4_str_row(Evaluate *eval,int i,int j, int role);
int check_B4_col(Evaluate *eval,int i,int j, int role);
int check_B4_str_col(Evaluate *eval,int i,int j, int role);
int check_B4_AtoD(Evaluate *eval,int i,int j, int role);
int check_B4_str_AtoD(Evaluate *eval,int i,int j, int role);
int check_B4_BtoC(Evaluate *eval,int i,int j, int role);
int check_B4_str_BtoC(Evaluate *eval,int i,int j, int role);
int check_A3(Evaluate *eval, point *position, int role);
int check_A3_row(Evaluate *eval,int i,int j, int role);
int check_A3_str_row(Evaluate *eval,int i,int j, int role);
int check_A3_col(Evaluate *eval,int i,int j, int role);
int check_A3_str_col(Evaluate *eval,int i,int j, int role);
int check_A3_AtoD(Evaluate *eval,int i,int j, int role);
int check_A3_str_AtoD(Evaluate *eval,int i,int j, int role);
int check_A3_BtoC(Evaluate *eval,int i,int j, int role);
int check_A3_str_BtoC(Evaluate *eval,int i,int j, int role);
int check_B3(Evaluate *eval, point *position, int role);
int check_A2(Evaluate *eval, point *position, int role);
int check_B2(Evaluate *eval, point *position, int role);
#endif