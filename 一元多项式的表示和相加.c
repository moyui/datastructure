#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct {
    int cof;    //系数
    int exp;    //指数
    struct Node *next;    /*指向下一项的指针*/
}Poly;

int createPoly(Poly *L) {    /*创建多项式链表*/
    int x, y;    /*x表示系数，y表示指数*/
    Poly *q;    /*定义新节点*/
    do {
        printf("请输入多项式的系数(多项式系数输入0时结束)：");
        scanf("%d", &x);
        if (x == 0) {    /*如果系数为0就将指数填入0*/
            y = 0;
        } else {
            printf("请输入多项式的指数：");
            scanf("%d", &y);
        }
        q = (Poly*)malloc(sizeof(Poly));
        q -> cof = x;
        q -> exp = y;
        L -> next = q;
        L = q;
    }while(L -> cof != 0);    /*系数为0就跳出*/
    L -> next = NULL;    /*尾标识为NULL*/
    return 1;
}

int printPolynoimal(Poly *L) {
    Poly *head;
    head = L;
    head = head -> next;
    if (head -> cof == 0) {
        printf("F(x)=0\n");
        return;
    } else {
        printf("F(x)=%dX^%d", head -> cof, head -> exp);
        head = head -> next;
    }
    while (head -> cof != 0) {
        if (head -> cof > 0) {
            printf("+%dX^%d", head -> cof, head -> exp);
            head = head -> next;
        } else {
            printf("%dX^%d", head -> cof, head -> exp);
            head = head -> next;
        }
    }
    printf("\n");
    return 1;
}


int sortPolynoimal(Poly *L) {    /*对节点进行排序，仅交换数据*/
    int i, j, tempCof, tempExp, length = 0;
    Poly *head, *point;    /*辅助指针point帮助指向head的下一个节点*/
    head = L;
    head = head -> next;
    while (head -> next != NULL) {    /*计算链表长度*/
        length++;
        head = head -> next;
    }
    for (i = 0; i < length - 1; i++) {    /*冒泡排序*/
        head = L;   /*将head复位*/
        head = head -> next;
        for(j = i; j < length - 1; j++) {
            point = head -> next;
            if(head -> exp > point -> exp) {
                tempCof = head -> cof;
                tempExp = head -> exp;
                head -> cof = point -> cof;
                head -> exp = point -> exp;
                point -> cof = tempCof;
                point -> exp = tempExp;
            }
            head = head -> next;
        }
    }
    return 1;
}

int addPolynoimal(Poly *L1, Poly *L2, Poly *L3) {
    int x = 0;    /*x为和多项式每一项的系数*/
    Poly *headL1, *headL2, *headL3;    /*定义和多项式的指针和节点*/
    headL1 = L1;
    headL2 = L2;
    headL1 = headL1 -> next;
    headL2 = headL2 -> next;
    while (headL1 -> cof && headL2 -> cof) {
        if (headL1 -> exp == headL2 -> exp) {    /*两指数相同时，系数相加*/
            x = headL1 -> cof + headL2 -> cof;
            if (x) {    /*系数和不为零就插入到和多项式*/
                headL3 = (Poly*)malloc(sizeof(Poly));
                headL3 -> cof = x;
                headL3 -> exp = headL1 -> exp;
                L3 -> next = headL3;
                L3 = headL3;
                headL1 = headL1 -> next;
                headL2 = headL2 -> next;
            } else {    /*系数和为零就向后移一个节点*/
                headL1 = headL1 -> next;
                headL2 = headL2 -> next;
            }
        } else if (headL1 -> exp < headL2 -> exp){    /*两指数不相同时，将小的节点插入L3*/
            headL3 = (Poly*)malloc(sizeof(Poly));
            headL3 -> cof = headL1 -> cof;
            headL3 -> exp = headL1 -> exp;
            L3 -> next = headL3;
            L3 = headL3;
            headL1 = headL1 -> next;
        } else {
            headL3 = (Poly*)malloc(sizeof(Poly));
            headL3 -> cof = headL2 -> cof;
            headL3 -> exp = headL2 -> exp;
            L3 -> next = headL3;
            L3 = headL3;
            headL2 = headL2 -> next;
        }
    }
    while (headL1 -> cof != 0) {   /*如果L1有剩余即当前节点系数不为0，则将剩下的全部插入L3*/
        headL3 = (Poly*)malloc(sizeof(Poly));
        headL3 -> cof = headL1 -> cof;
        headL3 -> exp = headL1 -> exp;
        L3 -> next = headL3;
        L3 = headL3;
        headL1 = headL1 -> next;
    }
    while (headL2 -> cof != 0) {    /*如果L2有剩余即当前节点系数不为0，则将剩下的全部插入L3*/
        headL3 = (Poly*)malloc(sizeof(Poly));
        headL3 -> cof = headL2 -> cof;
        headL3 -> exp = headL2 -> exp;
        L3 -> next = headL3;
        L3 = headL3;
        headL2 = headL2 -> next;
    }
    headL3 = (Poly*)malloc(sizeof(Poly));    /*制造出cof值为0的节点，插入到链表末尾作为标志节点*/
    headL3 -> cof = 0;
    L3 -> next = headL3;
   return;
}

int main() {
    Poly *L1, *L2, *L3;
    L1 = (Poly*)malloc(sizeof(Poly));
    L2 = (Poly*)malloc(sizeof(Poly));
    L3 = (Poly*)malloc(sizeof(Poly));
    printf("请输入第一个多项式\n");
    createPoly(&L1);
    printf("请输入第二个多项式\n");
    createPoly(&L2);
    sortPolynoimal(&L1);
    sortPolynoimal(&L2);
    printf("第一个多项式如下：\n");
    printPolynoimal(&L1);
    printf("第二个多项式如下：\n");
    printPolynoimal(&L2);
    printf("相加后和多项式如下：\n");
    addPolynoimal(&L1, &L2, &L3);
    printPolynoimal(&L3);
    return 1;
}

