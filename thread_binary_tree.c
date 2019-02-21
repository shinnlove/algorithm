//
// Created by shinnlove on 2019-02-21.
//

#include <stdio.h>
#include "data_structure_func.h"

int main() {

    // 线索二叉树
    BiThrTree tree;

    // 访问函数
    Status (*v)(TElemType e);
    v = visit;

    // 建立可线索化的二叉树
    if (createBiThrTree(&tree) != 1) {
        printf("为二叉树分配内存失败!\n");
        return ERROR;
    }

    printf("二叉树建立完毕，准备线索化\n");

    // 线索化二叉树
    if (inOrderThreading(&tree, tree) != 1) {
        printf("线索化二叉树失败!\n");
        return ERROR;
    }

    printf("二叉树线索化完毕，准备线索化中序遍历\n");

    // 中序遍历线索二叉树
    if (inOrderTraverse_Thr(tree, v) != 1) {
        printf("线索化二叉树失败!\n");
        return ERROR;
    }

    printf("中序遍历线索化二叉树成功!");

    return 0;
}