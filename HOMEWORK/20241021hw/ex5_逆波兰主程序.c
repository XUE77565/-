#include<stdio.h>
#include<stdlib.h>
#define MAXOP 100
#define NUMBER '0'
int getop(char[]);
void push(int);
double pop(void);

int main(){
	int type;
	int op2;
	char s[MAXOP];
	while((type=getop(s))!=EOF){
		switch(type){
			case NUMBER:
				push(atoi(s));	break;
			case '+':
				push(pop()+pop());	break;
			case'*':
				push(pop()*pop());	break;
			case'-':
				op2=pop();
				push(pop()-op2);	break;
			case'/':
				op2=pop();
				if(op2!=0.0){push(pop()/op2);}
				else{printf("ERROR");}
				break;
			case'\n':
				printf("%d\n",pop());	break;
			case'&':
				push(pop()&pop());	break;
			case'|':
				push(pop()|pop());	break;
			case'<': 
				if(getop(s)=='<'){
					op2=pop();
					push(pop()<<op2);
					break;
					}
				else{printf("ERROR");break;}
			case'>': 
				if(getop(s)=='>'){
					op2=pop();
					push(pop()>>op2);
					break;
					}
				else{printf("ERROR");break;}
			default:
				printf("ERROR");break;
		}
	}
	return 0;
}

#include<ctype.h>
#define NUMBER '0'
int getch(void);
void ungetch(int);

int getop(char s[]){
	int i,c;
	while((s[0]=c=getch())==' ' || c=='\t');
	s[1]='\0';
	if(!isdigit(c))
		return c;
	i=0;
	if(isdigit(c))
		while(isdigit(s[++i]=c=getch()));
	s[i]='\0';
	if(c!=EOF)
		ungetch(c);
	return NUMBER;
}



#define MAXVAL 100
int sp=0;
double val[MAXVAL];

void push(double f){
	if(sp < MAXVAL)
		val[sp++]=f;
	else
		printf("ERROR\n");
}

double pop(void){
	if(sp>0)
		return val[--sp];
	else{
		printf("ERROR\n");
		return 0.0; 
	}
}



#define BUFSIZE 100
char buf[BUFSIZE] ;
int bufp=0;

int getch(void){
	return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch: too many charachters\n");
	else
		buf[bufp++]=c;
}
