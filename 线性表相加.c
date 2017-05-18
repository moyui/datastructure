#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
    int data;
    struct Node *next;
}LNode;

int createList (LNode *L) {    /*建立线性表*/
    LNode *q;
    int m, n, i;    /*节点个数为m，节点数据为n*/
    printf("请输入链表节点个数：");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        q = (LNode*)malloc(sizeof(LNode));
        printf("请输入节点数据：");
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*尾标识为NULL*/
    return 1;
}

int mergeListSL(LNode *L1, LNode *L2, LNode *L3) {    /*将L1，L2合并成L3，升序*/
    LNode *p1, *p2, *p3;
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    p2 = p2 -> next;
    while (p1 != NULL && p2 != NULL) {
        if (p1 -> data <= p2 -> data) {    /*如果p1的data小于p2的data，就将p1插入L3*/
            p3 -> next = p1;
            p3 = p1;
            p1 = p1 -> next;
        } else {    /*如果p2的data小于p1的data，就将p2插入L3*/
            p3 -> next = p2;
            p3 = p2;
            p2 = p2 -> next;
        }
    }
    p3 -> next = (p1 != NULL)? p1: p2;    /*如果p1还有节点，就将p1剩余节点全部插入L3，p2同理*/
    p3 = L3;    /*指针回到L3开头*/
    p3 = p3 -> next;
    printf("合并后的线性表输出的结果为：");
    while (p3 != NULL) {    /*将L3线性表显示出来*/
        printf("%d ", p3 -> data);
        p3 = p3 -> next;
    }
    return 1;
}

int mergeListLS(LNode *L1, LNode *L2, LNode *L3) {    /*将L1，L2合并成L3，降序*/
    LNode *p1, *p2, *p3;
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    p2 = p2 -> next;
    while (p1 != NULL && p2 != NULL) {
        if (p1 -> data >= p2 -> data) {    /*如果p1的data大于p2的data，就将p1插入L3*/
            p3 -> next = p1;
            p3 = p1;
            p1 = p1 -> next;
        } else {    /*如果p2的data大于p1的data，就将p2插入L3*/
            p3 -> next = p2;
            p3 = p2;
            p2 = p2 -> next;
        }
    }
    p3 -> next = (p1 != NULL)? p1: p2;    /*如果p1还有节点，就将p1剩余节点全部插入L3，p2同理*/
    p3 = L3;    /*指针回到L3开头*/
    p3 = p3 -> next;
    printf("合并后的线性表输出的结果为：");
    while (p3 != NULL) {    /*将L3线性表显示出来*/
        printf("%d ", p3 -> data);
        p3 = p3 -> next;
    }
    return 1;
}

int main() {
    LNode *L1, *L2, *L3;
    int ch;
    L1 = (LNode*)malloc(sizeof(LNode));
    L2 = (LNode*)malloc(sizeof(LNode));
    L3 = (LNode*)malloc(sizeof(LNode));
    printf("请选择排序顺序：");
    printf("1.升序");
    printf("2.降序\n");
    scanf("%d", &ch);
    createList(&L1);
    createList(&L2);
    switch(ch) {
        case 1:mergeListSL(&L1, &L2, &L3);break;
        case 2:mergeListLS(&L1, &L2, &L3);break;
        default: printf("输入错误");break;
    }
    return 1;
}

