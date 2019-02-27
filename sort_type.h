//
// Created by shinnlove on 2019-02-27.
//

#ifndef ALGORITHM_SORT_TYPE_H
#define ALGORITHM_SORT_TYPE_H

#endif //ALGORITHM_SORT_TYPE_H


#define MAXSIZE 20

// 定义排序主键为整型
typedef int KeyType;

// 定义与排序主键关联的结构体信息
typedef struct {
    char name[20];
    float score;
    int age;
} InfoType;

// 需要排序的结构体对象
typedef struct {
    KeyType key;
    InfoType otherInfo;
} RedType;

// 待排序顺序表
typedef struct {
    RedType r[MAXSIZE + 1];    // r[0]闲置或用作哨兵单元
    int length;                // 顺序表长度
} SqList, *SqListPoint;

/**
 * 初始化数组随机数。
 *
 * @param list
 */
void random_init(SqListPoint list);

/**
 * 打印数组排序结果。
 *
 * @param list
 */
void print_sort_result(SqListPoint list);

/**
 * 直接插入排序。
 *
 * @param list
 */
void insert_sort(SqListPoint list);

/**
 * 选择交换排序
 *
 * @param list
 */
void select_sort(SqListPoint list);

/**
 * 计数排序。
 *
 * @param list
 */
void counting_sort(SqListPoint list);