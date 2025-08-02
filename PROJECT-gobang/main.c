/*
�й���ѧԺ��ѧwcg��������ĩ����ҵ
���ߣ�Ѧ����
����Ϊ������
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
    initRecordBorard();    //��ʼ��һ��������
    innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
    initialDispay();
    // displayBoard();          //��ʾ����
    printf("��ӭ������������Ϸ, �����ߣ� 2306Ѧ����\n");
    printf("\n");
    printf("��ѡ����Ϸģʽ��\n");
    printf("\n");
    printf("���˶�սģʽ������1\n");
    printf("�˻���ս������2\n");
    printf("\n");
    printf("�����룺");

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
            printf("�ڷ���ʤ");
            return 0; 
        }
        else if (out==2){
            printf("�׷���ʤ");
            return 0;
        }
        if(player==3){
            printf("���ֽ���,�׷�ʤ");
            return 0;
        }
    }
    
    if(mode==2){
        printf("��ѡ���Ⱥ���,��������1,��������2\n");
        printf("\n");
        printf("�����룺");
        int mode2;
        scanf("%d",&mode2);//��ʾѡ����ģʽ
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
                printf("���ڼ��㣬���Ժ�...\n");
                ai_place(2);
                out = wincheck();
                if(out){
                    break;
                }
            }
            if(out == 1){
                printf("�ڷ���ʤ");
                return 0;
            }
            else if(out == 2){
                printf("�׷���ʤ");
                return 0;
            }
            else if(player == 3){
                printf("���ֽ���,�׷�ʤ");
                return 0;
            }
        }
        else{
            human_type=2;
            ai_type=1;
            arrayForInnerBoardLayout[7][7] = 1;//�����ai����, ��ֱ��������Ԫ
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
                printf("�ڷ���ʤ");
                return 0;
            }
            else if(out == 2){
                printf("�׷���ʤ");
                return 0;
            }
            else if(player == 3){
                printf("���ֽ���,�׷�ʤ");
                return 0;
            }
        }
    }
}

    

//��ʼ��һ�������̸�� 
void initRecordBorard(void){
	//ͨ��˫��ѭ������arrayForInnerBoardLayout��0
      int i=0, j=0;
      for(i=0; i<SIZE+1; i++){
        for(j=0; j<SIZE+1; j++){
            arrayForInnerBoardLayout[i][j]=0;
        }
      }
}

void initialDispay(){//��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
    int i,j;
        for(i=0; i<SIZE; i++){
            for(j=0; j<SIZE*CHARSIZE+1; j++){
                arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
            }
        }

}

void innerLayoutToDisplayArray(void){//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
	
    
	//�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
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



//��ʾ���̸�� 
void displayBoard(void){
	//��һ��������
	// system("clear");   //����  
	//�ڶ�������arrayForDisplayBoard�������Ļ��
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
	//������������������һ����ĸA B .... 
    printf("    ");
         for(j=0; 2*j<SIZE*CHARSIZE-1; j++){
            printf("%c ",('A'+j));
         }
         printf("\n");
} 

void InnerBoardToCheckBoard(){//�����е�����ת��Ϊ���ڼ����ֵ�����
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            CheckBoard[i][j]=arrayForInnerBoardLayout[i][j];
        }
    }
}


int human_input(int player){
    printf("����������λ����:12 h ���Ҫ������ ������88\n");
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
        printf("�����λ�ò��Ϸ�������������\n");
        // printf("%d\n",arrayForDisplayBoard[r][n]);
        if(player==1){return 1;}
        else{return 2;}
    }
    else{
        innerLayoutToDisplayArray();
        arrayForInnerBoardLayout[r][n]=player;
        InnerBoardToCheckBoard();//�����ڼ������̺����е�����ͬ��
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
            displayBoard();//չʾ����
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
    memcpy(eval.board, arrayForInnerBoardLayout, sizeof(arrayForInnerBoardLayout));//����ǰ���̸���ϴ���eval��
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
        arrayForInnerBoardLayout[path.moves[0][0]][path.moves[0][1]] = role;//��ai�����ӷŵ�������
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
        arrayForInnerBoardLayout[path.moves[0][0]][path.moves[0][1]] = role;//��ai�����ӷŵ�������
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

