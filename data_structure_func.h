//
// Created by shinnlove on 2019-02-20.
//

#ifndef FIRSTCPP_STACK_HANDLE_H
#define FIRSTCPP_STACK_HANDLE_H

#endif //FIRSTCPP_STACK_HANDLE_H

#include "data_structure_common.c"

// 访问一个元素，输出其值。
Status visit(TElemType e);

// 栈的基本操作函数声明

// 构造一个空栈sp
Status initStack(SqStackPoint sp);

// 销毁栈sp，sp的空间被释放
Status destroyStack(SqStackPoint sp);

// 把栈sp置为空
Status clearStack(SqStackPoint sp);

// 若栈s为空，则返回true
Status stackEmpty(SqStack s);

// 求栈元素个数
int stackLength(SqStack s);

// 若栈sp不空则用e返回栈顶元素，OK返回1
Status getTop(SqStack s, SElemType *e);

// 插入元素e为新的栈顶元素
Status push(SqStackPoint sp, SElemType e);

// 若栈sp不空则用e返回栈顶元素，OK返回1
Status pop(SqStackPoint sp, SElemType *e);

// 从栈底到栈顶依次调用遍历函数访问
Status stackTraverse(SqStack s, Status (*visit)());

// 二叉树的基本操作函数声明

// 创建一颗二叉树
Status createBiTree(BiTree *root);

// 先根遍历二叉树
Status preOrderTraverse(BiTree root, Status *(Visit)(TElemType e));

// 中根遍历二叉树(递归型)
Status inOrderTraverseRecursive(BiTree root, Status *(Visit)(TElemType e));

// 中根遍历二叉树(非递归)
Status inOrderTraverse(BiTree root, Status *(Visit)(TElemType e));

// 后根遍历二叉树(递归)
Status postOrderTraverseRecursive(BiTree root, Status *(Visit)(TElemType e));

Status createBiThrTree(BiThrTree *root);

// 对线索二叉树进行线索化
Status inOrderThreading(BiThrTree* tree, BiThrTree root);

// 中序递归线索化二叉树
void inThreading(BiThrTree* current, BiThrTree* pre);

// 中序遍历线索二叉树
Status inOrderTraverse_Thr(BiThrTree root, Status *(Visit)(TElemType e));

