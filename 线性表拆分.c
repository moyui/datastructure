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
    printf("请输入链表节点个数: ");
    scanf("%d", &m);
    printf("请输入链表节点数据（从大到小）:\n");
    for (i = 0; i < m; i++) {
        q = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*尾标识为NULL*/
    return 1;
}

int print(LNode *L) {    /*打印数据*/
    LNode *q;
    q = L;    /*指针回到开头*/
    q = q -> next;
    if (q == NULL) {    /*如果链表不存在数据就显示无数据*/
        printf("无数据！");
    } else {
        while (q != NULL) {    /*将排序后的线性表显示出来*/
            printf("%d ", q -> data);
            q = q -> next;
        }
    }
    return 1;
}

int sortList(LNode *L) {    /*对节点进行排序，仅交换数据*/
    int i, j, tempData;
    LNode *head, *point;    /*辅助指针point帮助指向head的下一个节点*/
    head = L;
    head = head -> next;
    int length = 0;
    if (head != NULL) {    /*如果链表不存在数据就跳过排序*/
        while (head -> next != NULL) {    /*计算链表长度*/
            head = head -> next;
            length++;
        }
        for (i = 0; i < length; i++) {    /*冒泡排序*/
            head = L;    /*将head复位*/
            head = head -> next;
        for(j = i; j < length; j++) {
            point = head -> next;
            if (head -> data >= point -> data) {
                tempData = head -> data;
                head -> data = point -> data;
                point -> data = tempData;
                }
            head = head -> next;
            }
        }
    }
    return 1;
}

int splitList(LNode *L1, LNode *L2, LNode *L3) {    /*将原线性表分开成两个线性表*/
    LNode *p1, *p2, *p3;
    int m;    /*m为余数*/
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    while (p1 != NULL) {
        m = (p1 -> data) % 2;
        if (m == 1) {    /*当前指针指向的数据为奇数时*/
            p2 -> next = p1;
            p2 = p2 -> next;
            p1 = p1 -> next;
        } else if (m == 0) {    /*当前指针指向的数据为偶数时*/
            p3 -> next = p1;
            p3 = p3 -> next;
            p1 = p1 -> next;
        } else {
            break;
        }
    }
    p2 -> next = NULL;
    p3 -> next = NULL;
    return 1;
}

int main() {
    LNode *L1, *L2, *L3, *p;
    L1 = (LNode*)malloc(sizeof(LNode));
    L2 = (LNode*)malloc(sizeof(LNode));
    L3 = (LNode*)malloc(sizeof(LNode));
    createList(&L1);
    printf("原线性表输出的结果为：");
    print(&L1);
    splitList(&L1, &L2, &L3);
    sortList(&L2);
    sortList(&L3);
    printf("\n奇数线性表输出的结果为：");
    print(&L2);
    printf("\n偶数线性表输出的结果为：");
    print(&L3);
}
