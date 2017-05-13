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
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
    }
    switch(b) {
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
    }
    return pre[i][j];
}

int InN(char c， char op[]) {    /*判断输入的某个字符是否是运算符*/
    char *p;
    p = op;
    while(*p != '\0'){
        if(c == *p)
            return 1;
        p++;
    }
    return 0;
}

int Operate(int a, char y, int b) {
    int i, j, result;
    i = a;
    j = b;
    switch(y) {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    return result;
}

int getNext(int *n) {
    char c;
    *n = 0;
    while((c = getchar()) == ' ');  /*跳过一个或多个空格*/
    if(!InN(c)) {            /*通过函数判断如果字符不是数字，那么只能是运算符*/
        *n = c;
        return 1;
    }
    do {                         /*能执行到该条语句，说明字符是数字，此处用循环获得连续的数字*/
        *n = *n * 10 + (c-'0');       /*把连续的数字字符转换成相对应的整数*/
        c = getchar();
    } while(InN(c));         /*如果下一个字符是数字，进入下一轮循环*/
    ungetc(c,stdin);            /*新读入的字符不是数字，可能是运算符,为了不影响下次读入，把该字符放回到输入缓冲区*/
    return 0;
}

int evaluateExpression(){
    int n;
    int flag;
    int c;
    char x, y;
    int a,b;
    char OP[] = "+-*/()#";
    SqStack* OPTR;
    SqStack* OPND;
    InitStack(&OPTR);
    Push(&OPTR,'#');
    InitStack(&OPND);
    flag = getNext(&c);
    Pop(OPTR, &x);
    while(c !='#' || x != '#') {
        if(flag == 0) {
                  Push(&OPND,c);
                  flag = getNext(&c);
             } else {
            Pop(OPTR, &x);
            switch(Precede(x, c)) {
                case '<':    /*栈顶元素优先级低*/
                    Push(&OPTR, c);
                    flag = getNext(&c);
                    break;
                case '=':    /*脱括号并接受下一字符*/
                    Pop(&OPTR,&x);
                    flag = getNext(&c);
                    break;
                case '>':    /*退栈并将运算结果入栈*/
                    Pop(&OPTR, &y);
                    Pop(&OPND, &b);
                    Pop(&OPND, &a);
                    Push(&OPND, Operate(a, y, b));
                    break;
            }
        }
        Pop(OPTR, &x);
    }
    Pop(OPND, &c);
    return c;
}

void main(){
    int c;
    printf("请输入一个字符:\n");
    c = evaluateExpression();
    printf("结果是 = %d\n",c);
    getch();
}
