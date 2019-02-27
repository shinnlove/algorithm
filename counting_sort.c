//
// Created by shinnlove on 2019-02-27.
//

#include <stdio.h>
#include <mm_malloc.h>

/**
 * 计数排序。
 *
 * 并没有改变原来数组的排序，只是对辅助数组输出了一个正确的值顺序。
 *
 * 特别注意：为了数组0存放最小值节省辅助数组空间，使用offset=min作为偏移量。
 * 当计算每个数字出现次数的时候，存储的下标要根据值减去offset；而当输出组别数组内的数字时，下标要加上对应的偏移量。
 *
 * @param a     原排序数组
 * @param len   数组长度，可以在传入统计前用sizeof(a)/sizeof(int)得到
 * @param min   遍历原来数组一遍可以得到最小值
 * @param max   遍历原来数组一遍可以得到最大值
 */
void counting_sort(int a[], int len, int min, int max) {

    printf("数组长度是len=%d, 最小min=%d, 最大max=%d\n", len, min, max);

    // 组别数
    int g_len = max - min + 1, offset = min;
    // 组数组
    int group[g_len];

    // 要初始化
    for (int i = 0; i < g_len; i++) {
        group[i] = 0;
    }

    // 统计原数组
    for (int i = 0; i < len; i++) {
        group[a[i] - offset] += 1;
    }

    // 遍历组别
    for (int j = 0; j < g_len; j++) {
        // 组内次数
        for (int k = 0; k < group[j]; k++) {
            // 输出的时候加上偏移量
            printf("%d ", j + offset);
        }
    }

}

int main() {

    // 一共25个数
    int a[] = {12, 31, 25, 18, 9, 2, 31, 8, 5, 2, 29, 7, 2, 7, 24, 37, 1, 15, 75, 7, 2, 7, 46, 2, 6};

    // 数组长度
    int len = sizeof(a) / sizeof(int);

    // 最小值与最大值
    int min, max;
    min = max = a[0];
    for (int i = 0; i < len; i++) {
        if (a[i] < min) {
            min = a[i];
        }
        if (a[i] > max) {
            max = a[i];
        }
    }

    // 计数排序
    counting_sort(a, len, min, max);

    return 0;
}

