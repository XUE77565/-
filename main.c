#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void initialDispay();


int wincheck();
int check_row(int i,int j);
int check_col(int i,int j);
int check_A_to_D(int i,int j);
int check_B_to_C(int i,int j);
int checkpoint(int i,int j);


int CheckBan(int i,int j);
void InnerBoardToCheckBoard();
int CheckBoard[SIZE][SIZE];
int player;
int input(int);

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//������ģ�� 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������洢������ʾ������ 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼��ǰ�����̵ĸ�� 
int arrayForInnerBoardLayout[SIZE][SIZE];



int main()

{

    initRecordBorard();    //��ʼ��һ��������
    innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
    initialDispay();
    displayBoard();          //��ʾ����
    

    player=1;
    int out=wincheck();
    int check=0;
    while(player!=0 && player!=3 && out==0){
        
        player=input(player);
        out=wincheck();
        
    }
    if(player==3){
        printf("���ֽ���,�׷�ʤ");
        return 0;
    }
    if(out==1){
        printf("�ڷ���ʤ");
        return 0; 
    }
    else if (out==2){
        printf("�׷���ʤ");
        return 0;
    }

    return 0;
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
	system("clear");   //����  
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


int input(int player){
    printf("����������λ����:12 h ���Ҫ������ ������88\n");
    int check;
    int r;
    char c;
    int *p=&player;
    scanf("%d",&r);
    if(r==88){return 0;}
    scanf("%c",&c);
    r=r-1;
    int n;
    n=c-'a';
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
        if(player==1){
            arrayForDisplayBoard[SIZE-r-1][2*n]=play1CurrentPic[0];
            arrayForDisplayBoard[SIZE-r-1][2*n+1]=play1CurrentPic[1];
            displayBoard();//չʾ����
            if(CheckBan(r,n)==1){
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

int wincheck(){
    int i, j;
    int out = 0;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(checkpoint(i, j) != 0){
                return checkpoint(i,j);
            }
        }
    }
    return 0;
}



int checkpoint(int i,int j){
    if((check_row(i,j)!=0) ||(check_col(i,j)!=0) || (check_A_to_D(i,j)!=0) || (check_B_to_C(i,j)!=0))
        return arrayForInnerBoardLayout[i][j];
}

int check_row(int i, int j) {
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // 检查位�? j 的左右两侧最�? 4 个位�?
    int start = j - 4 > 0 ? j - 4 : 0;
    int end = j + 4 < 14 ? j + 4 : 14;

    for (k = start; k <= j; k++) {
        int win = 1;
        for (r = 0; r < 5; r++) {
            if (k + r > end || arrayForInnerBoardLayout[i][k + r] != c) {
                win = 0;
                break;
            }
        }
        if (win) {
            out = c;
            break;
        }
    }
    return out;
}

int check_col(int i, int j) {
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k, r;

    // 检查位�? j 的左右两侧最�? 4 个位�?
    int start = i - 4 > 0 ? i - 4 : 0;
    int end = i + 4 < 14 ? i + 4 : 14;

    for (k = start; k <= i; k++) {
        int win = 1;
        for (r = 0; r < 5; r++) {
            if (k + r > end || arrayForInnerBoardLayout[k+r][j] != c) {
                win = 0;
                break;
            }
        }
        if (win) {
            out = c;
            break;
        }
    }
    return out;
}

int check_A_to_D(int i, int j){
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k;

    for(k = -4; k <= 0; k++){
        int count = 0;
        int r;
        int start_i = i + k;
        int start_j = j + k;


        if(start_i < 0 || start_j < 0)
            continue;


        if(start_i + 4 >= SIZE|| start_j + 4 >= SIZE)
            continue;


        for(r = 0; r < 5; r++){
            if(arrayForInnerBoardLayout[start_i + r][start_j + r] != c)
                break;
            else
                count++;
        }
        if(count == 5){
            out = c;
            break;
        }
    }
    return out;
}

int check_B_to_C(int i, int j){
    int out = 0;
    int c = arrayForInnerBoardLayout[i][j];
    int k;

    for(k = -4; k <= 0; k++){
        int count = 0;
        int r;
        int start_i = i - k;
        int start_j = j + k;

        if(start_i >= SIZE || start_j < 0)
            continue;

  
        if(start_i - 4 < 0 || start_j + 4 >= SIZE)
            continue;

        for(r = 0; r < 5; r++){
            if(arrayForInnerBoardLayout[start_i - r][start_j + r] != c)
                break;
            else
                count++;
        }
        if(count == 5){
            out = c;
            break;
        }
    }
    return out;

}
