//
// Created by shinnlove on 2019-04-02.
//

#include <stdio.h>

/**
 * 贝壳找房面试题：
 *
 * 有两个整型有序数组，num1数组中有m个有序数，整个数组长度为m+n；num2数组中有n个有序数，
 * 现将num2数组元素合并到num1数组中，保持有序。
 *
 * 时间复杂度是：O(n2)。
 *
 * 优化：num1数组有序，还可以采用折半查找方式找到插入位置。
 *
 * 如果允许额外的空间复杂度，遍历O(m+n)就可以合并到新数组中。
 *
 * @return
 */
int main() {

    // 初始化
    int m = 6, n = 5;
    int num1[11] = {2, 6, 8, 10, 12, 16};
    int num2[5] = {1, 3, 5, 7, 11};


    int sorted_count = 0;

    // 将num2每个数插入num1
    for (int i = n - 1; i >= 0; i--) {

        // 寻找插入位置
        int j = m - 1 + sorted_count;
        for (j; j >= 0; j--) {
            if (num2[i] > num1[j]) {
                break;
            }
        }

        // 移动num1数组
        for (int k = m - 1 + sorted_count; k > j; k--) {
            num1[k + 1] = num1[k];
        }

        // 将num2这个数放入
        num1[j + 1] = num2[i];

        sorted_count += 1;
    }

    printf("排序后的数组是：\n");
    for (int k = 0; k < m + n; k++) {
        printf("%d ", num1[k]);
    }
    printf("\n");

    return 0;
}