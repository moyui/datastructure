#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*存储空间初始分配量*/
#define STACKINCREMENT 10    /*存储空间分配增量*/

typedef struct {
  char *top;
  char *base;
  int stacksize;
}SqStack;

int InitStack (SqStack *S) {   /*构造一个空栈*/
    S -> base = (char*)malloc(STACK_INIT_SIZE*sizeof(char));
    S -> top = S -> base;
    S -> stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push (SqStack *S, char e) {    /*插入元素e为新的栈顶元素*/
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (char*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(char));
        if (!S -> base) {    /*栈溢出*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    *(S -> top) = e;    /*先赋值在将指针加1*/
    S -> top ++;
    return 1;
}

int Pop (SqStack *S, char *e) {    /*退栈*/
    if (S -> top == S -> base) {    /*栈空*/
            return 0;
    } else {
        S -> top --;    /*先将指针减1在出栈*/
        *e = *(S -> top);
    }
    return 1;
}

char getTop(SqStack S){    /*返回栈顶第一个元素*/
    char e;
    if(S.top == S.base)
        return 0;
    e = *(S.top - 1);
    return e;
}

char Precede(char a, char b) {    /*比较两个运算符的优先级,a，b中存放待比较的运算符,
                                   '>'表示a>b,'0'表示不可能出现的比较 */
    int i,j;
    char pre[][7]={    /*运算符之间的优先级制作成一张表格*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a) {
        case '+': i = 0; break;
        case '-': i = 1; break;
        case '*': i = 2; break;
        case '/': i = 3; break;
        case '(': i = 4; break;
        case ')': i = 5; break;
        case '#': i = 6; break;
    }
    switch(b) {
        case '+': j = 0; break;
        case '-': j = 1; break;
        case '*': j = 2; break;
        case '/': j = 3; break;
        case '(': j = 4; break;
        case ')': j = 5; break;
        case '#': j = 6; break;
    }
    return pre[i][j];
}

int in(char c, char OP[8]) {    /*判断输入的某个字符是否是运算符*/
    int i;
    for(i = 0; OP[i] != '\0'; i++) {
        if(OP[i] == c) {
            return 1;
        }
    }
    return 0;
}

char Operate(char a, char n, char b) {      /*四则运算计算*/
    int i, j, result;
    char back;
    i = a - '0';    /*将char转换为int*/
    j = b - '0';
    switch(n) {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    back = result + '0';
    return back;
}

char evaluateExpression(SqStack OPTR, SqStack OPND) {
    char a, b, c, x, n, temp;
    temp = '#';
    Push(&OPTR, temp);
    char OP[8] = {'+','-','*','/','(',')','#','\0'};
    c = getchar();    /*输入字符*/
    while(c != '#' || getTop(OPTR) != '#') {    /*判断是不是运算符*/
        if(!in(c, OP)) {    /*不是运算符则进栈*/
            Push(&OPND, c);
            c = getchar();
             } else {    /*是运算符就和前面的比较*/
            x = getTop(OPTR);
            switch(Precede(x, c)) {
                case '<':    /*栈顶元素优先级低*/
                    Push(&OPTR, c);
                    c = getchar();
                    break;
                case '=':    /*脱括号并接受下一字符*/
                    Pop(&OPTR, &x);
                    c = getchar();
                    break;
                case '>':    /*退栈并将运算结果入栈*/
                    Pop(&OPTR, &n);
                    Pop(&OPND, &b);
                    Pop(&OPND, &a);
                    Push(&OPND, Operate(a, n, b));
                    break;
            }
        }
    }
    return getTop(OPND);
}

int main(){
    char c;
    SqStack OPTR;    /*OPTR为运算符栈，OPND为数字栈*/
    SqStack OPND;
    InitStack(&OPTR);
    InitStack(&OPND);
    printf("请输入表达式:\n");
    c = evaluateExpression(OPTR, OPND);
    printf("结果是 = %c\n",c);
    return 1;
}
