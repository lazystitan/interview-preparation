# 面试准备（算法）

## 基础数据结构

1. 数组
2. 单向链表
3. 栈

## 基础数据结构拓展

1. 双向链表0
   - 异或链表
2. O(1)极值栈
3. 异形链表
   - Y形链表寻找分叉点
   - 环

## 树

1. 二叉树
2. B+树

## 图
1. 邻接表

## 基础排序算法

1. 选择排序
2. 插入排序
3. 希尔排序
4. 冒泡排序
5. 归并排序
6. 快速排序
7. 堆排序（优先队列）

[//]: # (8. 基数排序)

[//]: # (9. 桶排序)

## 基础字符串算法

1. 暴力字符串查找
2. KMP算法
3. BM算法
4. RK算法

## 记录

### 对数组排序速度的疑问

在开启O2优化的情况下，希尔排序速度显著慢于选择排序和插入排序。
按照《算法》所描述，希尔排序应该更快，怀疑是采用vector导致的。
下为输出记录：
```
**** select sort ****
----ordered vector----
exchange count: 100000
compare count: 5000050000
cost time: 1201.44ms
----10 random vector----
average exchange count: 100000
average compare count: 5.00005e+09
cost time: 11527.6ms
----reversed vector----
exchange count: 100000
compare count: 5000050000
cost time: 1267.61ms
*******************
**** insert sort ****
----ordered vector----
exchange count: 0
compare count: 4999950000
cost time: 2279.58ms
----10 random vector----
average exchange count: 2.50075e+09
average compare count: 4.99995e+09
cost time: 23098.7ms
----reversed vector----
exchange count: 4999950000
compare count: 4999950000
cost time: 2298.28ms
*******************
**** shell sort ****
----ordered vector----
exchange count: 0
compare count: 6820966545
cost time: 3090.63ms
----10 random vector----
average exchange count: 2.95771e+06
average compare count: 6.82097e+09
cost time: 31931.9ms
----reversed vector----
exchange count: 619654
compare count: 6820966545
cost time: 3112.49ms
*******************
```

更换为数组后希尔还是没有选择和插入快。
输出如下：
```
**** select sort ****
----ordered vector----
exchange count: 100000
compare count: 5000050000
cost time: 1201.25ms
----10 random vector----
average exchange count: 100000
average compare count: 5.00005e+09
cost time: 11338.1ms
----reversed vector----
exchange count: 100000
compare count: 5000050000
cost time: 1704.92ms
*******************
**** insert sort ****
----ordered vector----
exchange count: 0
compare count: 4999950000
cost time: 3372.06ms
----10 random vector----
average exchange count: 2.49751e+09
average compare count: 4.99995e+09
cost time: 29850.3ms
----reversed vector----
exchange count: 4999950000
compare count: 4999950000
cost time: 2441.19ms
*******************
**** shell sort ****
----ordered vector----
exchange count: 0
compare count: 6820966545
cost time: 4837.93ms
----10 random vector----
average exchange count: 2.92275e+06
average compare count: 6.82097e+09
cost time: 47529.9ms
----reversed vector----
exchange count: 619654
compare count: 6820966545
cost time: 4607.58ms
*******************
```
尝试将比较操作放入for条件内后，插入和希尔排序比较次数大幅下降，速度变快：

- 插入排序

```c++
void insert_sort(double *v) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = i; j > 0 && less(v[j], v[j - 1]); j--) {
            exchange(v, j, j - 1);
        }

// slow way
//        for (int j = i; j > 0; j--) {
//            if (less(v[j], v[j - 1])) {
//                exchange(v, j, j - 1);
//            }
//        }
    }
}
```

- 希尔排序

```c++
void shell_sort(double *v) {
    int h = 1;
    while (h < (ARRAY_SIZE / 3))
        h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < ARRAY_SIZE; i++) {
            for (int j = i; j >= h && less(v[j], v[j - h]); j -= h) {
                exchange(v, j, j - h);
            }
// slow way
//            for (int j = i; j >= h; j -= h) {
//                if (less(v[j], v[j - h]))
//                    exchange(v, j, j - h);
//            }
        }

        h = h / 3;
    }
}
```
输出如下：
```
**** select sort ****
----ordered vector----
exchange count: 100000
compare count: 5000050000
cost time: 2.26638s
----10 random vector----
average exchange count: 100000
average compare count: 5.00005e+09
cost time: 22.97s
----reversed vector----
exchange count: 100000
compare count: 5000050000
cost time: 2.27603s
*******************
**** insert sort ****
----ordered vector----
exchange count: 0
compare count: 99999
cost time: 7.3441e-05s
----10 random vector----
average exchange count: 2.49981e+09
average compare count: 2.49991e+09
cost time: 11.666s
----reversed vector----
exchange count: 4999950000
compare count: 4999950000
cost time: 2.38609s
*******************
**** shell sort ****
----ordered vector----
exchange count: 0
compare count: 967146
cost time: 0.000878631s
----10 random vector----
average exchange count: 2.97707e+06
average compare count: 3.90292e+06
cost time: 0.150304s
----reversed vector----
exchange count: 619654
compare count: 1533494
cost time: 0.00116666s
*******************
```
最后发现原因在于，for的条件隐含着break的意义，例如，两种插入排序展开后如下：
```c++
    //fast
    for (int i = 0; i < size; ++i) {
        int j = i;
        while(true) {
            if (!(j > 0)) { break; } //middle condition
            if (!less(v1[j], v1[j - 1])) { break; } //middle condition
            exchange(v1, j, j - 1);
            j--;
        }
    }

    //slower
    for (int i = 0; i < size; ++i) {
       int j = i;
       while(true) {
          if (!(j > 0)) { break; } //middle condition
          if (!less(v2[j], v2[j - 1])) {
              //not break
          } else {
              exchange(v2, j, j - 1);
          }
          j--;
       }
    }

```