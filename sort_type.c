//
// Created by shinnlove on 2019-02-27.
//

#include <stdio.h>
#include <mm_malloc.h>
#include <stdlib.h>
#include <time.h>
#include "sort_type.h"

void random_init(SqListPoint list) {
    printf("初始化待排序数组：");

    for (int i = 1; i <= 20; i++) {
        list->r[i].key = rand() % 100;
        printf("%d ", list->r[i].key);
    }

    printf("\n");
}

void print_sort_result(SqListPoint list) {
    printf("排序后的数组结果：");

    // 再次输出
    for (int j = 1; j <= 20; j++) {
        printf("%d ", list->r[j].key);
    }

    printf("\n");
}

void insert_sort(SqListPoint list) {
    // 默认第一个数已经有序，从第二个数开始直接插入排序
    for (int i = 2; i <= list->length; i++) {
        if (list->r[i].key < list->r[i - 1].key) {
            // 总是把需要换位置的数据复制到哨兵位置
            list->r[0] = list->r[i];

            // 默认插入位置：比当前key大的相邻位置前面的一个数
            list->r[i] = list->r[i - 1];

            // 再看看这个数前面还有没有比当前key大的数、一并后移
            int j = i - 2;

            // C语言循环到0自动退出
            for (j; list->r[0].key < list->r[j].key; j--) {
                // 逐个后移
                list->r[j + 1] = list->r[j];
            }

            // 再把哨兵插入到可覆写的正确位置
            // 此时j已经是0
            list->r[j + 1] = list->r[0];
        }
    }
}

void counting_sort(SqListPoint list) {

    int len = list->length;

    // 最小值与最大值
    int min, max;
    min = max = list->r[1].key;
    for (int i = 1; i <= list->length; i++) {
        if (list->r[i].key < min) {
            min = list->r[i].key;
        }
        if (list->r[i].key > max) {
            max = list->r[i].key;
        }
    }

    printf("数组中最小min=%d, 最大max=%d\n", min, max);

    // 组别数
    int g_len = max - min + 1, offset = min;
    // 组数组
    int group[g_len];

    // 要初始化
    for (int i = 0; i < g_len; i++) {
        group[i] = 0;
    }

    // 统计原数组
    for (int i = 1; i <= len; i++) {
        group[list->r[i].key - offset] += 1;
    }

    printf("排序后的数组结果：");

    // 遍历组别
    for (int j = 0; j < g_len; j++) {
        // 组内次数
        for (int k = 0; k < group[j]; k++) {
            // 输出的时候加上偏移量
            printf("%d ", j + offset);
        }
    }

    printf("\n");
}

int main() {
    // 使用时间作为随机数种子
    srand(time(NULL));

    // 初始化
    SqList list;
    SqListPoint sp = &list;
    list.length = 20;

    random_init(sp);
    // 直接插入排序
    insert_sort(sp);
    print_sort_result(sp);

    random_init(sp);
    // 计数排序(不改变原数组)
    counting_sort(sp);

    return 0;
}
