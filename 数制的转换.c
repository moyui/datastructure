#include <stdio.h>
#include <malloc.h>
#include <math.h>

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

int Push (SqStack *S, int e) {    /*插入元素e为新的栈顶元素*/
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

int Pop (SqStack *S, int *e) {    /*退栈*/
    if (S -> top == S -> base) {    /*栈空*/
            return 0;
    } else {
        S -> top --;    /*先将指针减1在出栈*/
        *e = *(S -> top);
    }
    return 1;
}

int Convert (SqStack *S, int data) {    /*转换函数*/
    int i, j, e;    /*分别定义商,余数和转换后的数字*/
    i = data / 2;
    j = data % 2;
    Push(S, j);    /*若原数据为0就直接入栈*/
    while (i != 0) {    /*除原数据为0以外商为1的继续做除法和求模运算*/
        j = i % 2;
        i = i / 2;
        Push(S, j);
    }
    printf("对应的二进制数为：");
    while(S -> top != S -> base)    /*将处理完的数据出栈*/
    {
        Pop(S, &e);
        printf("%d ", e);
    }
    return 1;
}

int main() {
    SqStack *S;
    int number;
    InitStack(&S);
    printf("请输入要转换的十进制数：");
    scanf("%d", &number);
    Convert(&S, number);
}


