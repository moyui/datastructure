#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define len 100

typedef struct {    /*顺序表节点*/
    int array[len];
    int length;
}List;

typedef struct {    /*链表节点*/
    int data;
    struct Node *next;
}Node;

int createList (List *L) {    /*建立顺序表*/
    if (L -> length != NULL) {
        printf("已建立顺序表!");
        return 0;
    }
    int i, num;
    printf("请输入顺序表长度：");
    scanf("%d", &num);
    L -> length = num;    /*length指明线性表长度*/
    printf("请输入线性表节点数据");
    for (i = 1; i <= num; i++) {
        scanf("%d", &L -> array[i]);
    }
    return 1;
}

int createNode (Node *L) {    /*建立链表*/
    if (L -> data != NULL) {
        printf("已建立链表！");
        return 0;
    }
    Node *q;
    int m, n, i;    /*节点个数为m，节点数据为n*/
    printf("请输入链表节点个数：");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        q = (Node*)malloc(sizeof(Node));
        printf("请输入节点数据：");
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*尾标识为NULL*/
    return 1;
}

int sortList(List *L) {
    int choose, M = 1, N = L -> length, i;
    int r[N+1], r2[N+1];    /*建立归并排序所需数组*/
    for (i = 1; i <= N; i++) {
        r[i] = L -> array[i];
    }
    system("CLS");
    printf("1.直接插入排序\n");
    printf("2.冒泡排序\n");
    printf("3.直接选择排序\n");
    printf("4.快速排序\n");
    printf("5.归并排序\n");
    printf("请键入你的选择:");
    scanf("%d", &choose);
    switch(choose) {
        case 1:insertSort(L);break;
        case 2:bubbleSort(L);break;
        case 3:selectionSort(L);break;
        case 4:quickSort(L, M, N);break;
        case 5:mergeSort(r, r2, M, N);
               for (i = 1; i < N; i++) {
                    L -> array[i] = r [i];
               }break;
    }
    return 1;
}

int insertSort(List *L) {    /*直接插入排序*/
    int i, j;
    for (i = 2; i <= L -> length; i++) {
        if (L -> array[i] < L -> array[i-1]) {    /*将L->array[i]插入到有序子表*/
            L -> array[0] = L -> array[i];    /*复制为哨兵*/
            L -> array[i] = L -> array[i-1];
            for (j = i - 1; L -> array[0] < L -> array[j]; j--) {
                L -> array[j+1] = L -> array[j];    /*记录后移*/
            }
            L -> array[j+1] = L-> array[0];    /*插入到正确位置*/
        }
    }
    return 1;
}

int bubbleSort(List* L) {    /*冒泡排序*/
    int i, j, temp;
    for (i = 1; i < L -> length; i++) {
        for (j = i; j < L-> length; j++) {
            if (L -> array[j] > L -> array[j+1]) {
                temp = L -> array[j+1];
                L -> array[j+1] = L -> array[j];
                L -> array[j] = temp;
            }
        }
    }
    return 1;
}

int selectionSort(List *L) {    /*直接选择排序*/
    int i, j, temp, m;
    for (i = 1; i < L -> length; i++) {
        m = i;
        for (j = i; j < L -> length; j++) {    /*找到最小的数字*/
            if(L -> array[j] < L -> array[m]) {
                m=j;
            }
        if (i != m) {
            temp = L -> array[i];
            L -> array[i] = L -> array[m];
            L -> array[m] = temp;
            }
        }
    }
}

int quickSort(List *L ,int M ,int N) {    /*快速排序*/
    int i, j, x;
    i = M, j = N;
    x = L -> array[i];
    do {
        while ((L -> array[j] >= x) && (j > i)) {
            j--;
        }
            if (i < j) {
                L -> array[i] = L -> array [j];
                i++;
                while (L -> array[j] <= x && (i < j)) {
                    i++;
                }
                if (i < j) {
                    L -> array[j] = L -> array [i];
                    j--;
                }
            }
    }while (i != j);
    L -> array[i] = x;
    i++;
    j--;
    if (M < j) {
        quickSort(L ,M ,j);
    }
    if (i < N) {
        quickSort(L, i, N);
    }
}
int merge(int r[], int r2[], int S, int M, int N) {
    int i,k,j;
    i = S, k = S, j = M + 1;    /*从S开始*/
    while ((i <= M) && (j <= N)) {    /*当两个表都有内容未排完时*/
        if (r[i] <= r[j]) {
            r2[k] = r[i];
            i++;
        } else {
            r2[k] = r [j];
            j++;
        }
        k++;
    }
    while (i <= M + 1) {    /*将剩下的全部放入*/
        r2[k++] = r[i++];
    }
    while (j <= N + 1) {
        r2[k++] = r[j++];
    }
    for (i = S; i <= N; i++) {
        r[i] = r2[i];
    }
}
int mergeSort(int r[], int r2[], int S, int N) {    /*归并排序*/
    int M;
    if (S < N) {
        M = (S + N)/2;
        mergeSort(r, r2, S, M);
        mergeSort(r, r2, M + 1, N);
        merge(r, r2, S, M, N);
    }
}

int printList(List *L) {    /*打印顺序表*/
    int i;
    for (i = 1; i < L -> length; i++) {   /*打印排序结果*/
    printf("%d ", L -> array[i]);
    }
    return 1;
}

int sortNode(Node *L) {    /*对链表节点进行排序，仅交换数据*/
    int i, j, tempData;
    Node *head, *point;    /*辅助指针point帮助指向head的下一个节点*/
    head = L;
    head = head -> next;
    int length = 0;
    while (head -> next != NULL) {    /*计算链表长度*/
        head = head -> next;
        length++;
    }
    for (i = 0; i < length; i++) {    /*冒泡排序*/
        head = L;    /*将head复位*/
        head = head -> next;
        for(j = i; j < length; j++) {
            point = head -> next;
            if(head -> data >= point -> data) {
                tempData = head -> data;
                head -> data = point -> data;
                point -> data = tempData;
            }
            head = head -> next;
        }
    }
    head = L;    /*指针回到开头*/
    head = head -> next;
    while (head != NULL) {    /*将排序后的线性表显示出来*/
        printf("%d ", head -> data);
        head = head -> next;
    }
    return 1;
}

int combine(List *L1, Node *L2) {    /*结合两张表*/
    int r[10000], i = 1, point = 0;
    Node *head;
    head = L2;
    head = head -> next;
    while((head != NULL) && (i <= L1 -> length)) {
        if (head -> data <= L1 -> array[i]) {
            r[point] = head -> data;
            point++;
            head = head -> next;
        } else {
            r[point] = L1 -> array[i];
            point++;
            i++;
        }
    }
    while (head != NULL) {    /*将剩下元素全部放入数组*/
        r[point] = head -> data;
        point++;
        head = head -> next;
    }
    while (i <= L1 -> length) {
        r[point] = L1 -> array[i];
        point++;
        i++;
    }
    for (i = 0; i < point; i++) {    /*输出元素*/
        printf("%d ", r[i]);
    }
    return 1;
}

int main() {
    int choose;
    List *L1;
    Node *L2;
    while(1) {
        system("CLS");
        printf("1.建立顺序表\n");
        printf("2.排序\n");
        printf("3.建立链表\n");
        printf("4.逆置链表\n");
        printf("5.合并顺序表与链表\n");
        printf("0.退出\n");
        printf("请键入你的选择:");
        scanf("%d", &choose);
        switch(choose) {
            case 1:createList(&L1);printList(&L1);break;
            case 2:sortList(&L1);printList(&L1);break;
            case 3:createNode(&L2);break;
            case 4:sortNode(&L2);break;
            case 5:combine(&L1, &L2);break;
            case 0:exit(0);
        }
    }
}
