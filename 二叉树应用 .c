#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

typedef int Elemtype;

typedef struct {
    Elemtype e;
}Elem;

typedef struct BitTree {
    Elem data;    /*定义数据*/
    struct BitTree *lChild, *rChild;    /*定义左右孩子指针*/
}BitNode, *BitTree;

BitNode *T = NULL;

int createTree(BitTree *T) {    /*创建二叉树*/
    Elemtype ch;
    scanf("%d", &ch);
    if(ch == 0) {    /*0表示空树*/
        *T = NULL;
    } else {
        *T = (BitTree)malloc(sizeof(BitNode));
        if (!T) {
            exit(1);
        }
        (*T) -> data.e = ch;    /*生成根节点*/
        createTree(&(*T) -> lChild);    /*构造左子树*/
        createTree(&(*T) -> rChild);    /*构造右子树*/
    }
    return 1;
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

int inOrder(BitTree T) {    /*非递归中序遍历*/
    BitNode *stack[100];
    int top;
    BitNode *p;
    top = 0;
    p = T;
    while(p != NULL || top > 0) {
        while(p != NULL) {    /*遍历到最左端的节点*/
            stack[top++] = p;
            p = p -> lChild;
        }
        if(top > 0) {    /*出栈，选择当前节点的右子树*/
            p = stack[--top];
            printf("%5d", p -> data);
            p = p -> rChild;
        }
    }
}

int levelPrint(BitTree T) {    /*非递归层次遍历*/
    BitTree queue[100];
    BitNode *p;
    int front = -1, rear = -1;
    rear++;
    queue[rear] = T;
    while(front != rear) {
        front = (front + 1) % 100;
        p = queue[front];
        printf("%5d", p -> data);
        if(p -> lChild != NULL) {
            rear = (rear + 1) % 100;
            queue[rear] = p -> lChild;
        }
        if(p -> rChild != NULL) {
            rear = (rear + 1) % 100;
            queue[rear] = p -> rChild;
        }
    }
}

int judge(BitTree T) {    /*判断是否为二叉树*/
    if(!T) {    /*返回1代表是二叉排序树*/
        return 1;
    } else if(!(T -> lChild)&&!(T -> rChild)) {     /*左右子树都没有*/
        return 1;
    } else if((T -> lChild)&&!(T -> rChild)) {   /*只有左子树*/
        if((T->lChild->data.e)>(T->data.e)) {
            return 0;    /*返回0代表无二叉树*/
        } else {
            return(judge(T -> lChild));   /*继续寻找子节点*/
        }
    }
    else if(!(T -> lChild)&&(T -> rChild)) {   /*只有右子树*/
        if((T->rChild -> data.e) < (T -> data.e)) {
            return 0;
        } else {
            return(judge(T -> rChild));
        }

    } else {    /*如果左右子树都存在*/
        if((T -> lChild -> data.e) > (T -> data.e)||(T -> rChild -> data.e) < (T -> data.e)) {
            return 0;
        } else {
            return (judge(T -> lChild) && judge(T -> rChild));
        }
    }
}

int searchBst(BitTree T, BitTree G, Elemtype key, BitTree *p) {    /*查找节点*/
    if(!T) {    /*判断原树是否存在*/
        *p = G;
        return 0;
    } else if(key == T -> data.e) {
        *p = T;
        return 1;
    }
    else if(key < T -> data.e) {
        return searchBst(T -> lChild, T, key, p);
    }
    else {
        return searchBst(T -> rChild, T, key, p);
    }
    return 1;
}

int insertBst(BitTree T, Elemtype key) {    /*二叉排序树插入*/
    BitTree p, N;
    if(searchBst(T, NULL, key, &p)) {
        return 0;
    } else {
        N = (BitTree)malloc(sizeof(BitNode));
        N -> data.e = key;
        N -> lChild = NULL;
        N -> rChild = NULL;
        if(!p) {
            T = N;
        } else if(key < p -> data.e) {
            p -> lChild = N;
        } else {
            p -> rChild = N;
        }
    }
    return 1;
}

int deleteBst(BitTree *T, int key) {    /*删除二叉排序树*/
    if(!(*T)) {
        return 0;
    } else {
        if(key == (*T) -> data.e) {
            Delete(T);    /*找到指定节点，删除*/
        } else if(key < (*T) -> data.e) {
            return deleteBst(&(*T)->lChild, key);
        } else {
            return deleteBst(&(*T)->rChild, key);
        }
    }
}

int Delete(BitTree *p) { /*删除节点*/
    BitTree q, N;
    if(!(*p) -> lChild && !(*p) -> rChild) {
        *p = NULL;
    } else if(!(*p) -> lChild) {
        q = *p;
        free(q);
    } else if(!(*p) -> rChild) {
        q = *p;
        free(q);
    } else {
        q = *p;
        N = (*p) -> lChild;
        while(N -> rChild) {
            q = N;
            N = N -> rChild;
        }
        (*p) -> data.e = N -> data.e;
        if(q!=*p) {
            q -> rChild = N -> lChild;
        } else {
            q -> lChild = N -> lChild;
        }
        free(N);
    }
    return 1;
}

int main() {
    int ch = 0, flag = 0, key, m;
    flag = judge(T);
    while(1) {
        printf("1.创建二叉树\n");
        printf("2.先序非递归遍历\n");
        printf("3.中序非递归遍历\n");
        printf("4.层次非递归遍历\n");
        printf("5.判断二叉树是否为二叉排序树\n");
        printf("6.二叉排序树插入数据\n");
        printf("7.二叉排序树删除数据\n");
        printf("0.退出\n");
        printf("请输入你的选择：");
        scanf("%d", &ch);
        switch(ch) {
            case 1:printf("请输入数据，0为空节点:\n");
                   createTree(&T);printf("\n");break;
            case 2:printf("非递归先序遍历为：\n");
                   preOrder(T);printf("\n");break;
            case 3:printf("非递归中序遍历为：\n");
                   inOrder(T);printf("\n");break;
            case 4:printf("非递归层次遍历为：\n");
                   levelPrint(T);printf("\n");break;
            case 5:flag = judge(T);
                   if(flag)
                   printf("该树是二叉排序树\n");
                   else
                   printf("该树不是二叉排序树\n");
                   printf("\n");break;
            case 6:printf("请输入数据：");
                   scanf("%d",&key);
                   insertBst(T, key);break;
            case 7:printf("请输入数据：");
                   scanf("%d",&m);
                   deleteBst(&T, m);break;
            case 0:exit(0);
        }
        printf("\n");
    }
    return 1;
}
