#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
    int num;
    struct Node *next;
}Node;

int create(Node *L) {    /*创建约瑟夫环*/
    int i;    /*计数器*/
    int num;    /*每个节点中的数字及约瑟夫环的节点总数*/
    Node *q;    /*定义新节点*/
    printf("请输入约瑟夫环的节点总数：");
    scanf("%d", &num);
    for (i = 1; i <= num; i++) {    /*建立数据节点*/
        q = (Node*)malloc(sizeof(Node));
        q -> num = i;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*尾标识为NULL*/
    return 1;
}

int process(Node *L) {    /*实现约瑟夫环*/
    int m, n, i;    /*定义从第m个人开始，数n次*/
    Node *head, *point;    /*定义头结点，point节点(用以删除节点)*/
    head = L;
    head = head -> next;    /*将头结点和L移到有数值的第一个节点*/
    L = head;
    while (head -> next != NULL) {    /*遍历到最后一个节点*/
        head = head -> next;
    }
    head -> next = L;    /*闭环*/
    printf("请输入从第几个人开始：");
    scanf("%d", &m);
    printf("请输入要数几次：");
    scanf("%d", &n);
    for (i = 1; i < m; i++) {    /*将指针移到第m个人处*/
        L = L -> next;
    }
    if (n == 1) {    /*如果第m个人数1次，就依次出列*/
        while(L -> next != L) {    /*如果最后只有L指向的节点自己形成环，就跳出*/
            head = L;    /*L自身就是要输出的节点*/
            while(head -> next != L) {    /*将head指向L的前节点*/
                head = head -> next;
            }
            printf("%d ", L -> num);
            point = L;   /*将point指针指向已经输出的节点*/
            L = L -> next;
            head -> next = L;    /*将断环闭合*/
            free(point);
        }
        printf("%d", L -> num);
        free(L);
        return 1;
    } else {    /*如果第m个人数n次*/
        while(L -> next != L) {
            for (i = 1; i < n; i++) {    /*将L指向要输出的节点*/
                L = L -> next;
            }
            while(head -> next != L) {
                head = head -> next;
            }
            printf("%d ", L -> num);
            point = L;
            L = L -> next;
            head -> next = L;
            free(point);
        }
        printf("%d", L -> num);
        free(L);
        return 1;
    }
}


int main() {
    Node *Circle;
    Circle = (Node*)malloc(sizeof(Node));
    create(&Circle);
    process(&Circle);
}


