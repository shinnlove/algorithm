//
// Created by shinnlove on 2019-02-20.
//

#include <stdio.h>
#include "data_structure_func.h"

/**
 * 访问一个元素，输出其值。
 *
 * @param e
 * @return
 */
Status visit(TElemType e) {
    printf("current visited: e=%d\n", e);
    return OK;
}


int main() {

    // 一颗二叉树(树的根指针)
    BiTree tree;

    // 访问函数
    Status (*v)(TElemType e);
    v = visit;

    // 建树就是修改树指针指向新地址(一开始是空的根)、因此传入指针引用
    if (createBiTree(&tree) != 1) {
        printf("为二叉树分配内存失败!\n");
    }

    // 先序
    printf("先序遍历二叉树开始：\n");
    preOrderTraverse(tree, v);

    // 中序
    printf("中序遍历二叉树开始：\n");
    inOrderTraverse(tree, v);

    return 0;
}