#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct customer {    /*乘客结构体*/
	char name[20];
	int id;
	int seat;
	char sex[10];
	char goal[10];
	char type[1];
}Customer;

typedef struct list {    /*将乘客规划为数组*/
    Customer *array[25];     /*最大存放25人*/
    int length;
}sqList;

typedef struct node {    /*将飞机规划为链表*/
    int number;
	int input;
    struct node *next;
}Node;

int temp1 = 0;    /*航班计数器*/
int temp2 = 0;    /*人数计数器*/

int createPlane(Node *L) {    /*创建飞机链表*/
    int x, y;
    do {
        printf("请输入飞机序号(序号为0时输入完毕)：");
        scanf("%d", &x);
        if (x != 0) {
            printf("请输入登机口：");
            scanf("%d", &y);
            Node *q;    /*定义新节点*/
            q = (Node*)malloc(sizeof(Node));
            temp1++;
            q -> number = x;
            q -> input = y;
            L -> next = q;
            L = q;
        }
    }while(x != 0);    /*飞机序号为0时结束*/
    L -> next = NULL;
    return 1;
}

int deleteNode(Node *L) {    /*删除飞机节点*/
    int num;
    Node *q;
    q = L;
    Node *r = q;
    q = q -> next;
    printf("请输入要删除的飞机序号（警告该飞机下的乘客全部删除！）：");
    scanf("%d", &num);
    while(q != NULL) {
        if (q -> number == num) {
            r -> next = q -> next;
            free(q);
            temp1--;
            return 1;
        } else {
            q = q -> next;
            r = r -> next;
        }
    }
    printf("未找到该飞机！");
    return 0;
}

int initSqList (sqList *S) {    /*容器初始化*/
    S -> length = 0;
    return 1;
}

int createSqList (Node *L, sqList *S) {   /*构造乘客容器*/
    int x, y, i;
    Node *q;
    q = L;
    q = q -> next;
    printf("请输入乘客所在飞机号：");
    scanf("%d", &x);
    while (q != NULL) {
        if (q -> number == x) {
            printf("该飞机共有几名乘客:");
            scanf("%d", &y);
            for (i = temp2 + 1; i <= y; i++) {
            S -> array[i] = createCustomer(i);
            S -> length ++;
            temp2++;
            }
            return S;
        } else {
            q = q -> next;
        }
    }
    printf("未找到该飞机序号！");
    return 0;
}

int createCustomer(int i) {    /*创建新乘客*/
    Customer *q;
    q = (Customer*)malloc(sizeof(Customer));
    printf("请输入乘客身份识别号：");
    scanf("%d", &(q -> id));
    printf("请输入乘客姓名：");
    scanf("%s", &(q -> name));
    printf("请输入座位号：");
    scanf("%d", &(q -> seat));
    printf("请输入乘客性别：");
    scanf("%s", &(q-> sex));
    printf("请输入目的地：");
    scanf("%s", &(q -> goal));
    printf("请输入舱位种类: ");
    scanf("%s", &(q -> type));
    return q;
}

int searchPlane(Node *L) {    /*搜寻航班*/
    int x, y;
    Node *q;
    q = L;
    printf("请输入航班序号：");
    scanf("%d", &x);
    while (q != NULL) {
        if (x == q -> number) {
            printf("找到该航班！\n");
            printf("航班序号：%d, 登机口:%d\n", q -> number, q -> input);
            return 1;
        } else {
            q = q -> next;
        }
    }
    printf("未找到该航班\n");
    return 0;
}

int searchCustomer(Node *L, sqList *S) {    /*搜寻乘客*/
    int x, y, i;
    char s;
    Node *q;
    q = L;
    q = q -> next;
    printf("请输入乘客所在飞机号：");    /*检测飞机是否存在*/
    scanf("%d", &x);
    while(q != NULL) {
        if (q -> number == x) {
            break;
        } else {
            q = q -> next;
        }
    }
    if (q == NULL) {
        printf("未找到该飞机\n");
        return 0;
    }
    printf("请输入乘客身份识别号：");
    scanf("%d", &y);
    for (i = 1; i <= temp2; i++) {
        if (y == S -> array[i] -> id) {
            printf("找到乘客，打印出数据：\n");
            printf("乘客姓名：%s\n", S -> array[i] -> name);
            printf("乘客身份识别号：%d\n", S -> array[i] -> id);
            printf("乘客座位号：%d\n", S -> array[i] -> seat);
            printf("乘客目的地: %s\n", S -> array[i] -> goal);
            printf("舱位种类：%s\n", S -> array[i] -> type);
            return 1;
            }
    }
    printf("未找到该乘客\n");
    return 0;
}

int reserve(Node *L, sqList *S) {
     int i;
    L = L -> next;
    FILE *fp = NULL;
    if ((fp = fopen("Customer.txt", "w")) == NULL) {
        printf("不能打开文件！");
        return 0;
    }
    fprintf(fp, "%d\n", temp1);
    fprintf(fp, "%d\n", temp2);
    while (L != NULL) {    /*保存飞机节点*/
        fprintf(fp,"%d %d\n", L -> number, L -> input);
        L = L -> next;
    }
    for (i = 1; i <= temp2; i++) {    /*保存乘客节点*/
        fprintf(fp, "%s %d %d %s %s %s\n", S -> array[i] -> name, S -> array[i] -> id, S -> array[i] -> seat,
                 S -> array[i] -> sex, S -> array[i] -> goal, S -> array[i] -> type);
    }
    fprintf(fp, "%d\n", S -> length);
    fclose(fp);
    printf("成功完成");
    return 1;
}

int read(Node *L, sqList*S) {
    FILE *fp = NULL;
    int i = 0;
    Node *q;
    if ((fp = fopen("Customer.txt", "r")) == NULL) {
        printf("不能打开文件！");
        return 0;
    }
    fscanf(fp, "%d\n", &temp1);
    fscanf(fp, "%d\n", &temp2);
    for (i = 0; i < temp1; i++) {    /*读取飞机数据*/
        q = (Node*)malloc(sizeof(Node));
        fscanf(fp, "%d %d\n", &q -> number, &q -> input);
        L -> next = q;
        L = q;
    }
    for (i = 1; i <= temp2; i++); {
        Customer *temp;
        temp = (Customer*)malloc(sizeof(Customer));
        fscanf(fp,"%s %d %d %s %s %s\n", &temp -> name, &temp -> id, &temp -> seat, &temp -> sex, &temp -> goal,
            &temp -> type);
        S -> array[i] = temp;
        }
    fscanf(fp ,"%d\n", &S -> length);
    fclose(fp);
    printf("成功完成");
    return 1;
}

int main() {
    Node *L;
    sqList *S;
    L = (Node*)malloc(sizeof(Node));
    S = (sqList*)malloc(sizeof(sqList));
    initSqList(&S);
    int ch;
    while (1) {
        printf("                       --------飞机票预订系统--------\n");
        printf("                               1.创建航班\n");
        printf("                               2.创建乘客\n");
        printf("                               3.查询航班信息\n");
        printf("                               4.查询乘客信息\n");
        printf("                               5.保存信息\n");
        printf("                               6.读取信息\n");
        printf("                               7.删除飞机信息\n");
        printf("                               0.退出系统\n");
        printf("请输入您的选择:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:createPlane(&L);break;
            case 2:S = createSqList(&L, &S);break;
            case 3:searchPlane(&L);break;
            case 4:searchCustomer(&L, S);break;
            case 5:reserve(&L, S);break;
            case 6:read(&L, &S);break;
            case 7:deleteNode(&L);break;
            case 0:exit(0);
        }
    }
}
