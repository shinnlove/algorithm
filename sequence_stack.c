//
// Created by shinnlove on 2019-02-20.
//

#include <stdio.h>
#include "data_structure_func.h"

int main() {

    // 栈、它的指针
    SqStack stack;
    SqStackPoint sp = &stack;

    // 当前元素(特别注意，不要设置一个不确定的指针去改数据，至少也要让它指向自己类型的变量)
    int data;
    SElemType *dp;
    dp = &data;

    // 初始化
    initStack(sp);

    // 压栈与栈顶

    push(sp, 17);
    push(sp, 28);

    getTop(stack, dp);
    printf("当前栈顶元素是：%d\n", *dp);

    push(sp, 36);
    push(sp, 49);

    getTop(stack, dp);
    printf("当前栈顶元素是：%d\n", *dp);

    push(sp, 52);

    // 弹出栈
    getTop(stack, dp);
    printf("弹出前，当前栈顶元素是：%d\n", *dp);

    pop(sp, dp);
    printf("弹出了元素%d\n", *dp);

    pop(sp, dp);
    printf("弹出了元素%d\n", *dp);

    pop(sp, dp);
    printf("弹出了元素%d\n", *dp);

    pop(sp, dp);
    printf("弹出了元素%d\n", *dp);

    pop(sp, dp);
    printf("弹出了元素%d\n", *dp);

    return 0;
}