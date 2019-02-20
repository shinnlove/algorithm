//
// Created by shinnlove on 2019-02-20.
//

#include <stdio.h>
#include <mm_malloc.h>

#define LEN sizeof(struct Student)

typedef struct Student {
    long num;
    float score;
    struct Student *next;
} Student, *Stu;

// 链表全局节点数
int n;

/**
 * 创建链表。
 *
 * 头指针初始化为NULL，第一个节点创建后指向第一个节点。
 * p1指向新开辟的节点地址，如果是第一个节点则给头指针。
 * p2指针用来衔接链表，next指向p1，而后与p1同步。
 *
 * @return  返回链表头指针（注意可能为空）
 */
Stu create() {
    Student *head, *p1, *p2;

    head = NULL;
    n = 0;

    p1 = p2 = (Stu) malloc(LEN);

    scanf("%ld, %f", &p1->num, &p1->score);

    while (p1->num != 0) {
        n = n + 1;

        if (n == 1) {
            head = p1;
        } else {
            p2->next = p1; // 挂接
        }

        p2 = p1; // 同步

        p1 = (Stu) malloc(LEN);

        scanf("%ld, %f", &p1->num, &p1->score);
    }

    // 尾部变空
    p2->next = NULL;

    return head;
}

/**
 * 在指定链表上按照学号顺序插入链表新节点。
 *
 * 有三种插入情形：
 * 1) 在链表最后插入；
 * 2) 在链表中插入，此时又有两种情形：
 *  a) 在头节点插入；
 *  b) 在链表中间节点插入。
 *
 * @param head  链表的头指针
 * @param node  链表要插入的新节点指针
 * @return      返回新的链表头节点地址
 */
Stu add(Stu head, Stu node) {

    // 没有要新增的节点返回头节点
    if (node == NULL) {
        return head;
    }

    // 空链表返回新节点(注意尾指针!!)
    if (head == NULL) {
        node->next = NULL;
        return node;
    }

    // 然后开始遍历（注意定义两个变量给一个赋值是给后边的赋值!）
    Student *p1, *p2;
    p1 = p2 = head;

    // 数字比较不用等于是避免处理相同节点却落到尾节点上的情况（原链表只有一个节点判断p1!=null是错的!!）
    while (node->num > p1->num && p1->next != NULL) {
        p2 = p1;
        p1 = p1->next;
    }

    // 判断是找到位置了还是到链表末尾了
    if (node->num <= p1->num) {
        // 找到插入位置了
        if (p1 == head) {
            // 就插在头部
            node->next = head;
            head = node;
        } else {
            // 插在中间
            p2->next = node;
            node->next = p1;
        }
    } else {
        // 走到链表末尾了
        p1->next = node;
        node->next = NULL;
    }

    n = n + 1;

    return head;
}

/**
 * 在指定链表上删除给定学号的节点。
 *
 * 特别注意：这里的头节点带数据，如果删除了头节点，必须要返回新的头节点地址，因此这个函数有返回值。
 *
 * @param head  头指针指向的节点不是空节点，而是第一个节点
 * @param num   指定的学号
 * @return      返回新的链表头节点地址
 */
Stu del(Stu head, long num) {
    Student *p1, *p2;
    p1 = p2 = head;

    // 链表空则什么不做
    if (head == NULL) {
        return head;
    }

    // 先遍历到停
    while (num != p1->num && p1->next != NULL) {
        p2 = p1;
        p1 = p1->next;
    }

    // 再比较
    if (num == p1->num) {
        // 找到了
        if (p1 == head) {
            // 头指针所指节点就是，那么把头指针往后移
            head = p1->next;
        } else {
            // 进行链表挂接
            p2->next = p1->next;
        }

        printf("delete node: num=%ld", num);
        // 链表数减1
        n = n - 1;
        // 最终释放内存
        free(p1);

    } else {
        printf("%ld not been found!\n", num);
    }

    return head;
}

/**
 * 遍历链表节点。
 *
 * 传入链表头指针作为形参，一般不会去做改动，否则不知道链表起始地址了（如果是单链表的话）!!
 *
 * 因此用新指针去做遍历。
 *
 * @param head  链表头指针
 */
void print(Stu head) {
    printf("\nNow, these %d records are:\n", n);
    Student *p = head;

    // 一判断两用：p在头节点链表判空、p在尾节点判断尾指针
    while (p != NULL) {
        printf("%ld %5.1f\n", p->num, p->score);
        p = p->next;
    }
}

/**
 * 特别注意：
 * 1)本链表程序的头节点是带有数据的，无论是删除还是插入都有可能直接改变头指针，因此add和del都是带有返回值的。
 * 2)同时定义多个指针并且指向同一存储单元，就是p1=p2=xxx，不能边定义边赋值，这样只是最后一个赋值了!!!
 *
 * 3)malloc函数开辟一个void*的空指针后，经(Student *)强转后才能赋予该类型的指针，否则编译器报错（某些编译器能智能识别）。
 *
 * 程序输入与输出：
 *
 * 1001,67.5
 * 1003,87
 * 1005,99
 * 0,0
 *
 * Now, these 3 records are:
 * 1001  67.5
 * 1003  87.0
 * 1005  99.0
 *
 * @return
 */
int main() {

    // 新建链表
    Student *head = create();
    print(head);

    // 删除节点
    head = del(head, 1003);
    print(head);

    // 中间新节点
    Student *one = (Stu) malloc(LEN);
    one->num = 1002;
    one->score = 96.5;

    // 头节点
    Student *two = (Stu) malloc(LEN);
    two->num = 1000;
    two->score = 88.5;

    // 尾节点
    Student *three = (Stu) malloc(LEN);
    three->num = 1010;
    three->score = 97.0;

    // 依次添加
    head = add(head, one);
    head = add(head, two);
    head = add(head, three);
    print(head);

    return 0;
}

