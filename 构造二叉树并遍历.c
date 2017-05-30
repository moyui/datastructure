#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct BitTree {
    int data;    /*定义数据*/
    struct BitTree *lChild, *rChild;    /*定义左右孩子指针*/
}BitNode, *BitTree;

void buildTree(int inOrder[], int postOrder[], int il, int ir, int pl, int pr, BitTree T) {   /*根据中序和后序构造二叉树*/
    T = (BitTree)malloc(sizeof(BitNode));
    T -> data = postOrder[pr];    /*后序序列中最后一个元素为二叉树的根节点*/
    int m = il;
    while(inOrder[m] != postOrder[pr]) {    /*查找根节点在中序序列的位置*/
        m++;
    }
    if (m == il) {    /*左子树的中序序列为空*/
        T -> lChild = NULL;
    } else {
        buildTree(inOrder, postOrder, il, m - 1, pl, pl + m -1 - il, T -> lChild);    /*确定左子树*/
    }
    if (m == ir) {    /*右子树的中序序列为空*/
        T -> rChild = NULL;
    } else {
        buildTree(inOrder, postOrder, m + 1, ir, pr - ir + m, pr - 1, T -> rChild);    /*确定右子树*/
    }
}

int preOrder(BitTree T) {    /*非递归先序遍历*/
    BitTree stack[100];    /*基于栈进行遍历*/
    int front = 0, rear = 0;
    BitNode *p;
    if(T != NULL) {
        stack[rear] = T;    /*将根节点入栈*/
        rear = (rear + 1) % 100;
    }
    while (front != rear) {
        p = stack[front];
        front = (front + 1) % 100;
        printf("%5d", p -> data);    /*输出节点*/
        if(p -> lChild != NULL) {    /*左子树不为空就输出左子树*/
            stack[rear] = p -> lChild;    /*左子树入栈*/
            rear = (rear + 1) % 100;
        }
        if(p -> rChild != NULL) {    /*最后是右子树*/
            stack[rear] = p -> rChild;    /*右子树入栈*/
            rear = (rear + 1) % 100;
        }
    }
    return;
}

int main()  {
    int i, il, ir, pl, pr;    /*il和ir为中序序列的左右端点, pl和pr为后序序列的左右端点*/
    int len;
    BitNode *T;    /*树的根节点*/
    printf("请输入数组的长度:\n");
    scanf("%d", &len);
    int inOrder[len];    /*中序的数组*/
    printf("请依次输入中序数组:\n");
    for(i = 0; i < len; i++) {
        scanf("%d", &(inOrder[i]));
    }
    int postOrder[len];    /*后序的数组*/
    printf("请依次输入后序数组:\n");
    for(i = 0; i < len; i++) {
        scanf("%d", &(postOrder[i]));
    }
    il = 0;
    ir = len - 1;
    pl = 0;
    pr = len - 1;
    buildTree(inOrder, postOrder, il, ir, pl, pr, &T);
    preOrder(&T);
    return 1;
}


