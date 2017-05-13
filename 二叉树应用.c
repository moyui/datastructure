#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100    /*定义最大节点数为100*/

typedef int SqBiTree[MAX_TREE_SIZE];    /*定义根节点*/

typedef struct {
    int data;    /*定义数据*/
    struct btnode *lChild, *rChild;    /*定义左右孩子指针*/
}BitNode, *BitTree;

int createTree(BitNode *T) {    /*创建二叉树*/
    int ch;
    printf("请输入节点数据,0表示空树:");
    scanf("%d", &ch);
    if (ch == 0) {    /*0表示空树*/
        T = NULL;
    } else {
        T = (BitNode*)malloc(sizeof(BitNode));
        if (!T) {
            exit(-1);
        }
        T -> data = ch;    /*生成根节点*/
        createTree(T -> lChild);    /*构造左子树*/
        createTree(T -> rChild);    /*构造右子树*/
    }
    return 1;
}

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

int inOrder(BitNode* T) {    /*非递归中序遍历*/
    BitTree stack[100];    /*基于栈进行遍历*/
    int top = 0;
    BitNode *p;
    p = T;
    while(p != NULL || top > 0) {
        while(p != NULL) {    /*遍历到最左端的节点*/
            stack[top++] = p;
            p = p -> lChild;
        }
        if(top > 0) {    /*出栈，选择当前节点的右子树*/
            p = stack[--top];
            printf("%d", p -> data);
            p = p -> rChild;
        }
    }
    return 1;
}

int levelPrint(BitNode *T){    /*非递归层次遍历*/
    BitTree queue[100];
    BitNode *p;
    int front = -1, rear = 0;
    queue[rear] = T;
    while(front != rear) {
        p = queue[front];
        front = (front + 1) % 10000;
        printf("%d", p -> data);
        if(p -> lChild != NULL) {
            queue[rear] = p -> lChild;
            rear = (rear + 1) % 10000;
        }
        if(p -> rChild != NULL) {
            queue[rear] = p -> rChild;
            rear = (rear + 1) % 10000;
        }
    }
    return 1;
}

int judgePrint(BitNode *T) {    /*判断是否为二叉排序树*/
    if(!T) {    /*返回1代表是二叉排序树*/
        return 1;
    }
    else if(!(T -> lChild)&&!(T -> rChild)) {     /*左右子树都没有*/
        return 1;    /*返回1代表是二叉排序树*/
    }
    else if((T->lChild)&&!(T->rChild)) {   /*只有左子树*/
        if(((T -> lChild) -> data)>(T -> data)) {
            return 0;    /*返回0代表无二叉树*/
        } else {
            return (judgePrint(T -> lChild));   /*继续寻找子节点*/
        }

    }
    else if (!(T -> lChild)&&(T -> rChild)) {   /*只有右子树*/
        if(((T -> rChild) -> data) < (T -> data)) {
            return 0;
        } else {
            return (judgePrint(T -> rChild));
        }
    }
    else {    /*如果左右子树都存在*/
        if((T -> lChild -> data) > (T -> data) || (T -> rChild -> data) < (T -> data)) {
            return 0;
        }
        else {
        return (judgePrint(T -> lChild) && judgePrint(T -> rChild));
        }
    }
}

int insertBst(BitNode *T, int key) { /*二叉排序树插入*/
    BitTree P, N;
    if(searchBst(T, NULL, key, &p)) {    /*查找适合位置插入*/
        return 0;
    } else {
        N = (BitNode*)malloc(sizeof(BitNode));    /*创建新节点*/
        N -> data = key;
        N -> lChild = NULL;
        N -> rChild = NULL;
        if(!P) {    /*判断插入*/
            T = N;
        } else if(key < P -> data) {
            P -> lChild = N;
        }
        else {
            P -> rChild = N;
        }
    }
    return 1;
}

int searchBst(BitNode *T, BitNode *U int key, BitNode *P) {    /*查找节点*/

    if(!T) {    /*判断原树是否存在*/
        P = NULL;
        return 0;
    } else if(key == T -> data) {
        P = T;
        return 1;
    }
    else if(key < T -> data) {
        return searchBst(T -> lchild, T, key, P);
    }
    else {
        return searchBst(T->rChild, T, key, P);
    }
    return 1;
}

int deleteBst(BitNode *T, int key) {    /*二叉排序树删除*/
    if(!T) {
        return 0;
    }
    else {
        if(key == T -> data) {    /*找到指定节点，删除*/
            delete(T);
        }
        else if(key < T -> data) {
            return deleteBst(&T -> lChild, key);
        } else {
            return deleteBst(&T -> rChild, key);
        }
    }
    return 1;
}

int delete(BitNode *P) {    /*删除节点*/

    BitNode *N, *Q;
    if(!(P -> lChild) && !(P -> rChild)) {
         P = NULL;
    }

    else if(!(p->lchild)) {
        Q = P;
        free(Q);
    }
    else if(!(p -> rChild)) {
        Q = p;
        free(Q);
    }
    else {
        Q = P;
        N = P -> lChild;
        while(N -> rChild) {
            Q = N;
            N = N -> rChild;
        }
        P -> data = N -> data;
        if(Q != P) {
            Q -> rChild = N -> rChild;
        }
        else {
            Q -> lChild = N -> lChild;
        }
        free(N);
    }
    return 1;
}

int main() {
    int ch = 0,flag = 0, key;
    BitNode *T;
    while(1)
    {
        printf("1.创建二叉树\n");
        printf("2.先序非递归遍历\n");
        printf("3.中序非递归遍历\n");
        printf("4.层次非递归遍历\n");
        printf("5.判断二叉树是否为二叉排序树\n");
        printf("6.二叉排序树插入数据\n");
        printf("7.二叉排序树删除数据\n");
        printf("0.退出\n");
        printf("请键入你的选择：");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:createTree(&T);break;
            case 2:printf("非递归先序遍历为：\n");
                   preOrder(&T);
                   printf("\n");break;
            case 3:printf("非递归中序遍历为：\n");
                   inOrder(&T);
                   printf("\n");break;
            case 4:printf("非递归层次遍历为：\n");
                   levelPrint(&T);
                   printf("\n");break;
            case 5:flag = judgePrint(&T);
                   if(flag) {
                       printf("该树是二叉排序树\n");
                   }
                   else {
                       printf("该树不是二叉排序树\n");
                   }
                   printf("\n");break;
            case 6:printf("请输入数据：");
                   scanf("%d", &key);
                   insertBst(&T, key);break;
            case 7:printf("请输入数据：");
                   scanf("%d", &key);
                   deleteBst(&T, key);break;
            case 0:exit(0);
        }
        printf("\n");
    }
}
