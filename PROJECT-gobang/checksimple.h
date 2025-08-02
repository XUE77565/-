#ifndef CHECKSIMPLE_H
#define CHECKSIMPLE_H
#define SIZE 15

extern int CheckSimpleBoard[SIZE][SIZE];
int CheckSimpleBan(int i,int j);
int CheckSimpleMulti3(int i,int j);
int CheckSimpleMulti4(int i,int j);
int CheckSimpleLong(int i, int j);

int CheckSimpleLongRow(int,int);
int CheckSimpleLongCol(int,int);
int CheckSimpleLongAtoD(int,int);
int CheckSimpleLongBtoC(int,int);

int CheckSimple4Row(int i,int j);
int CheckSimple4StrRow(int i,int j);
int CheckSimple4Col(int i,int j);
int CheckSimple4StrCol(int i,int j);
int CheckSimple4AtoD(int i,int j);
int CheckSimple4StrAtoD(int i,int j);
int CheckSimple4BtoC(int i,int j);
int CheckSimple4StrBtoC(int i,int j);

int CheckSimple3Row(int i,int j);
int CheckSimple3StrRow(int i,int j);
int CheckSimple3Col(int i,int j);
int CheckSimple3StrCol(int i,int j);
int CheckSimple3AtoD(int i,int j);
int CheckSimple3StrAtoD(int i,int j);
int CheckSimple3BtoC(int i,int j);
int CheckSimple3StrBtoC(int i,int j);
#endif
