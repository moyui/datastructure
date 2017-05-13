#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*存储空间初始分配量*/
#define STACKINCREMENT 10    /*存储空间分配增量*/

typedef struct {    /*乘客结构体*/
	char name[100];
	int id;
	int seat;
	char sex[50];
	char goal[20];
	char type;
}Customer;

typedef struct {    /*将乘客规划为栈*/
	Customer *top;
	Customer *base;
	int stacksize;
}Stack;

typedef struct {    /*飞机结构体*/
	int number;
	int input;
    Stack data;
}Plane;

typedef struct {    /*将飞机规划为链表*/
    Plane data;
    struct Node *next;
}Node;

int temp1 = 0;    /*节点计数器*/

int createPlane(Node *L) {    /*创建飞机链表*/
    int x, y;
    do {
        printf("请输入飞机序号(0时结束)：\n");
        scanf("%d", &x);
        printf("请输入登机口：\n");
        scanf("%d", &y);
        if (x != 0) {
            Node *q;    /*定义新节点*/
            q = (Node*)malloc(sizeof(Node));
            temp1++;
            q -> data.number = x;
            q -> data.input = y;
            L -> next = q;
            L = q;
        }
    }while(x != 0);    /*飞机序号为0时结束*/
    return 1;
}

int deleteNode(Node *L) {    /*删除飞机节点*/
    int num;
    Node *q;
    q = L;
    q = q -> next;
    printf("请输入要删除的飞机序号（警告该飞机下的乘客全部删除！）：\n");
    scanf("%d", &num);
    while(q != NULL) {
        Node *r = q;
        if (r.data.number == num) {
            q -> next = r -> next;
            return 1;
        } else {
            q = q -> next;
        }
    }
    printf("未找到该飞机！");
    return 0;
}

int initStack (Stack *S) {   /*构造一个乘客空栈*/
    S -> base = (Customer*)malloc(STACK_INIT_SIZE*sizeof(Customer));
    S -> top = S -> base;
    S -> stacksize = STACK_INIT_SIZE;
    return 1;
}

int createCustomer(Stack *S) {    /*插入结构体e的新顾客为新的栈顶元素*/
    Customer e;
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (Customer*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(Customer));
        if (!S -> base) {    /*栈溢出*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    printf("请输入乘客身份识别号：\n");
    scanf("%d", &e.id);
    printf("请输入乘客姓名：\n");
    scanf("%s", &e.name);
    printf("请输入座位号：\n");
    scanf("%d", &e.seat);
    printf("请输入乘客性别：\n");
    scanf("%s", &e.sex);
    printf("请输入目的地：\n");
    scanf("%s", &e.goal);
    printf("请输入舱位种类: \n");
    scanf("%s", &e.type);
    *(S -> top) = e;    /*先赋值在将指针加1*/
    S -> top ++;
    return 1;
}

int Push (Stack *S, Customer e) {    /*插入结构体e为新的栈顶元素*/
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (char*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(char));
        if (!S -> base) {    /*栈溢出*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    *(S -> top) = e;    /*先赋值在将指针加1*/
    S -> top ++;
    return 1;
}

int Pop (Stack *S, Customer *e) {    /*退栈*/
    if (S -> top == S -> base) {    /*栈空*/
            return 0;
    } else {
        S -> top --;    /*先将指针减1在出栈*/
        *e = *(S -> top);
    }
    return 1;
}

int searchCustomer(Node *L) {    /*搜寻乘客*/
    int x, y;
    char s;
    Node *q;
    q = L;
    q = q -> next;
    printf("请输入乘客所在飞机号：\n");
    scanf("%d", &x);
    printf("请输入乘客身份识别号：\n");
    scanf("%d", &y);
    while(q != NULL) {
        Node *r = q;
        if (r.data.number == x) {
            q = r;
            break;
        } else {
            q = q -> next;
        }
    }
    if (q == NULL) {
        printf("未找到该飞机\n");
        return 0;
    }
    while (q.data.data.top != --q.data.data.base) {
        Customer temp = q.data.data.top;
        if (temp.top.id == y) {
            system("cls");
            printf("找到乘客，打印出数据：\n");
            printf("乘客姓名：%s\n", temp.name);
            printf("乘客身份识别号：%d\n", temp.id);
            printf("乘客座位号：%d\n", temp.seat);
            printf("乘客目的地: %s\n", temp.goal);
            printf("舱位种类：%s\n", temp.type);
            break;
       }
       else {
       temp--;
       }
       if (temp < q.data.data.base) {
        printf("未找到该乘客，跳出")
        return 0;
       }
    }
    printf("是否回到首页？y/n：");
    scanf("%s", &s);
    if (s == 'y') {
        return 1;
    }
}

int reserve(Node *L) {
    Node *q = L;
    q = q -> next;
    FILE *fp = NULL;
    int i;
    if ((fp = fopen("Customer.txt", "w")) == NULL) {
        printf("不能打开文件！");
        return 0;
    }
    fprintf(fp, "%d\n", temp1);
    while (i = 0; i < temp1; i++) {
        Customer m = q.data.data.top;
        while (m >= q.data.data.base) {
            fprintf(fp,"%s %d %d %s %s %s\n", m.name, m.id, m.seat, m.sex, m.goal,
                 m.type);
            m--;
        }
        fprintf(fp,"%d %d\n", q.data.number, q.data.number);
        q = q-> next;
    }
    fclose(fp);
    return 1;
}

int read(Node *L) {
    FILE *fp = NULL;
    int i = 0;
    Node *q;
    if ((fp = fopen("Customer.txt", "r")) == NULL) {
        printf("不能打开文件！");
        return 0;
    }
    fscanf(fp, "%d\n", &temp1);
    while(i = 0; i < temp1; i++) {
        q = (Node*)malloc(sizeof(Node));
        Customer m = q.data.data.top;
        while (m != NULL) {
            fscanf(fp,"%s %d %d %s %s %s\n", &m.name, &m.id, &m.seat, &m.sex, &m.goal,
                 &m.type);
            printf("%s %d %d %s %s %s\n", m.name, m.id, m.seat, m.sex, m.goal,
                 m.type);
            m++;
            }
        }
        fscanf(fp,"%d %d\n", &q.data.number, &q.data.number);
        fprintf(fp,"%d %d\n", q.data.number, q.data.number);
        L -> next = q;
        L = q;
    }
    fclose(fp);
    return 1;
}

int main() {
    Node *L;
    int ch:
    while (1) {
        system("cls");
        printf("--------飞机票预订系统--------\n");
        printf("        1.创建航班\n");
        printf("        2.创建乘客\n");
        printf("        3.查询航班信息\n");
        printf("        4.查询乘客信息\n");
        printf("        5.保存信息\n");
        printf("        6.读取信息\n");
        printf("        0.退出系统\n");
        printf("请输入您的选择:\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:createPlane(&L);break;
            case 2:createCustomer();break;
            case 3:searchCustomer();break;
            case 4:searchCustomer();break;
            case 5:reserve(&L);break;
            case 6:read();break;
            case 0:exit(0);
        }
    }
}
