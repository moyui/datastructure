#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*存储空间初始分配量*/
#define STACKINCREMENT 20    /*存储空间分配增量*/

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

int isEmpty (SqStack *S) {    /*判断栈是否为空*/
    if (S -> top == S -> base) {
        return 0;
    } else {
        return 1;
    }
}

int match (SqStack *S, int counter) {    /*判断括号是否匹配*/
    int i, flag1 = 0, flag2 = 0, flag3 = 0;    /*标志位flag1,2,3, 记录三种括号()[]{}的次数*/
    char e;
    if (isEmpty(S) == 0) {    /*判断栈是否为空*/
        printf("输入的字符为空！");
    } else {    /*不为空就弹栈*/
        for (i = 0; i < counter; i++) {
            Pop(S, &e);
            switch (e) {    /*判断括号是否匹配*/
                case '(': flag1--;break;
                case ')': flag1++;break;
                case '[': flag2--;break;
                case ']': flag2++;break;
                case '{': flag3--;break;
                case '}': flag3++;break;
                default: break;
            }
        }
        if (flag1 == 0 && flag2 == 0 && flag3 == 0 && (counter != 0)) {
            printf("括号匹配！");
        } else {
            printf("括号不匹配！");
        }
    }
    return 1;
}

int main() {
    int counter;   /*定义计数器，记录入栈次数*/
    char c = 0;
    SqStack *S;
    InitStack(&S);
    printf("请依次输入字符(回车键表示结束)：\n");
    while (c != '\n') {    /*当输入的字符是回车时,停止输入*/
        c = getchar();
        if (c != '\n') {    /*当输入的字符不是回车时,将其放入栈*/
            Push(&S, c);
            counter++;
        }
    }
    match(&S, counter);
    return 1;
}
