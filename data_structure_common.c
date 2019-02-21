//
// Created by shinnlove on 2019-02-20.
//

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

#define TElemType int
#define BiTNodeLEN sizeof(BiTNode)
#define BiThrNodeLEN sizeof(BiThrNode)

typedef int Status;

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

// 定义线索二叉树左右指针类型（Link->0、Thread->1）
typedef enum PointTag {
    Link, Thread
};

// 线索二叉树
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild; // 左右孩子指针
    enum PointTag LTag, RTag; // 左右指针标记
} BiThrNode, *BiThrTree;

