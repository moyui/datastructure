#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {    /*链表节点*/
    int data;
    struct Node *next;
}Node;

int array[100];    /*线性表用数组存储*/
int count;    /*顺序表计数器*/

int createList (int arr[]) {    /*建立顺序表*/
    int i;
    arr[0] = 0;
    printf("请输入顺序表长度：");
    scanf("%d", &count);
    printf("请输入顺序表节点数据:\n");
    for (i = 1; i <= count; i++) {
        scanf("%d", &arr[i]);
    }
    return 1;
}

int printList(int arr[]) {    /*打印顺序表*/
    int i;
    for (i = 1; i <= count; i++) {   /*打印排序结果*/
    printf("%d ", arr[i]);
    }
    printf("\n");
    return 1;
}

int sort(int arr[]) {    /*排序列表*/
    int M = 1, N = count, i, ch;/*建立快速，归并排序所需数组*/
    int r1[N + 1], r2[N + 1];
    for (i = 1; i <= N; i++) {
        r1[i - 1] = arr[i];
    }
    system("CLS");
    printf("1.直接插入排序\n");
    printf("2.冒泡排序\n");
    printf("3.直接选择排序\n");
    printf("4.快速排序\n");
    printf("5.归并排序\n");
    printf("请输入你的选择：");
    scanf("%d", &ch);
    switch(ch) {
        case 1:insertSort(arr);break;
        case 2:bubbleSort(arr);break;
        case 3:selectionSort(arr);break;
        case 4:quickSort(arr, M, N);break;
        case 5:mergeSort(r1, r2, 0, N - 1);
            for (i = 1; i <= N; i++) {
                arr[i] = r1[i - 1];
        }break;
    }
}

int insertSort(int arr[]) {    /*直接插入排序*/
    int i, j;
    for (i = 2; i <= count; i++) {
        arr[0] = arr[i];    /*array[0]作为监督哨*/
        j = i - 1;
        while (arr[0] < arr[j]) {    /*从后向前找到第一个关键字不小于arr[0]的记录*/
            arr[j + 1] = arr[j];
            j--;
        }
    arr[j + 1] = arr[0];
    }
    return 1;
}

int bubbleSort(int arr[]) {    /*冒泡排序*/
    int i, j, temp;
    for (i = 1; i <= count; i++) {
        for (j = 1; j <= count - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 1;
}

int selectionSort(int arr[]) {    /*直接选择排序*/
    int i, j, temp, m;
    for (i = 1; i <= count; i++) {
        m = i;
        for (j = i + 1; j <= count; j++) {    /*找到最小的数字*/
            if(arr[j] < arr[m]) {
                m = j;
            }
        if (i != m) {
            temp = arr[i];
            arr[i] = arr[m];
            arr[m] = temp;
            }
        }
    }
}

int quickSort(int arr[], int M, int N) {    /*快速排序*/
    int i, j, x;
    i = M, j = N;
    x = arr[i];
    do {
        while ((arr[j] >= x) && (j > i)) {
            j--;
        }
            if (i < j) {
                arr[i] = arr[j];
                i++;
                while (arr[j] <= x && (i < j)) {
                    i++;
                }
                if (i < j) {
                    arr[j] = arr[i];
                    j--;
                }
            }
    }while (i != j);
    arr[i] = x;
    i++;
    j--;
    if (M < j) {
        quickSort(arr, M ,j);
    }
    if (i < N) {
        quickSort(arr, i, N);
    }
}

int merge(int r[], int r2[], int S, int M, int N) {
    int i,k,j;
    i = S, k = S, j = M + 1;    /*从S开始*/
    while ((i != M + 1) && (j != N + 1)) {    /*当两个表都有内容未排完时*/
        if (r[i] > r[j]) {
            r2[k] = r[j];
            j++;
        } else {
            r2[k] = r [i];
            i++;
        }
        k++;
    }
    while (i != M + 1) {    /*将剩下的全部放入*/
        r2[k++] = r[i++];
    }
    while (j != N + 1) {
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

int createNode(Node *L) {    /*建立链表*/
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
    printf("\n");
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
    printf("\n");
    return 1;
}

int combine(int arr[], Node *L2) {    /*结合两张表*/
    int a[100];
    int i, j, temp;
    for (i = 1; i <= count; i++) {
        a[i - 1] = arr[i];
    }
    for (i = 1; i <= count; i++) {
        ;
    }
    while (L2 != NULL) {
        a[count + 1] = L2 -> data;
        count++;
    }
    for (i = 0; i <= count; i++) {
        for (j = 0; j <= count - i; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
    for (i = 0; i <= count; i++) {
        printf("%d ", a[i]);
    }
}

int main() {
    int choose;
    Node *L2;
    L2 = (Node*)malloc(sizeof(Node));
    while(1) {
        printf("1.建立顺序表\n");
        printf("2.顺序表排序\n");
        printf("3.建立链表\n");
        printf("4.逆置链表\n");
        printf("5.合并顺序表与链表\n");
        printf("0.退出\n");
        printf("请键入你的选择:");
        scanf("%d", &choose);
        switch(choose) {
            case 1:createList(array);printList(array);break;
            case 2:sort(array);printList(array);break;
            case 3:createNode(L2);break;
            case 4:sortNode(L2);break;
            case 5:combine(array, &L2);break;
            case 0:exit(0);
        }
        printf("\n");
    }
}
