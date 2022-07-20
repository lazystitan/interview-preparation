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