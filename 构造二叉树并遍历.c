#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100    /*定义最大节点数为100*/

typedef int SqBiTree[MAX_TREE_SIZE];

typedef struct {
    char data;    /*定义数据*/
    struct btnode *lChild, *rChild;    /*定义左右孩子指针*/
}BitNode, *BitTree;



int preOrder(BitNode *T) {    /*非递归先序遍历*/
    BitTree stack[100];    /*基于栈进行遍历*/
    int top = 0, bottom = 0;
    BitNode *p;
    if(T != NULL) {
        stack[top] = T;    /*将根节点入栈*/
        top = (top + 1) % 100;
    }
    while (bottom != top) {
        p = stack[bottom];
        printf("%d", p -> data);    /*输出节点*/
        bottom = (top + 1) % 100;
        if(p -> lChild != NULL) {    /*左子树不为空就输出左子树*/
            stack[top] = p -> lChild;    /*左子树入栈*/
            top = (top + 1) % 100;
        }
        if(p-> rChild != NULL) {    /*最后是右子树*/
            stack[top] = p -> rChild;    /*右子树入栈*/
            top = (top + 1) % 100;
        }
    }
    return 1;
}
