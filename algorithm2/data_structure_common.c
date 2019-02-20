//
// Created by shinnlove on 2019-02-20.
//

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#define TElemType int
#define LEN sizeof(BiTNode)

// 二叉树
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 栈元素存放二叉树结点地址
typedef BiTree SElemType;

// 定义栈
typedef struct {
    // 栈底指针(都是指向数组的指针，因此可以+-)
    SElemType *base;
    // 栈顶指针
    SElemType *top;
    int stack_size;
} SqStack, *SqStackPoint;