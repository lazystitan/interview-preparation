//
// Created by Riton on 2022/7/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <chrono>
#include "origin_array_sort.h"


std::vector<double> convert_array_to_vector(double *arr) {
    auto v = std::vector<double>();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        v.push_back(arr[i]);
    }

    return v;
}

void check_sorted(double *arr) {
    auto v = convert_array_to_vector(arr);
    assert(std::is_sorted(v.begin(), v.end()));
}

void show_reset_count() {
    show_count();
    reset_count();
}

void check_show_reset_count(double *p) {
    check_sorted(p);
    show_reset_count();
}

//选择排序
void select_sort(double *v) {
    auto index_to_put = 0;
    while (index_to_put < ARRAY_SIZE) {
        auto min_value_index = index_to_put;
        for (int i = index_to_put; i < ARRAY_SIZE; i++) {
            if (less(v[i], v[min_value_index])) {
                min_value_index = i;
            }
        }
        exchange(v, min_value_index, index_to_put);
        index_to_put++;
    }
}

//插入排序 slow
void insert_sort_slow(double *v) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = i; j > 0; j--) {
            if (less(v[j], v[j - 1])) {
                exchange(v, j, j - 1);
            }
        }
    }
}

//[low, high)
void insert_sort(double *v, int low, int high) {
    for (int i = low; i < high; ++i) {
        for (int j = i; j > low && less(v[j], v[j - 1]); j--) {
            exchange(v, j, j - 1);
        }
    }
}

//插入排序
void insert_sort(double *v) {
    insert_sort(v, 0, ARRAY_SIZE);
}

//  init                2,| 9, 7, 3, 8, 4, 5, 6, 0, 1
//  compare 9 and 2     2, 9,| 7, 3, 8, 4, 5, 6, 0, 1
//  compare 7 and 9     2, 7, 9,| 3, 8, 4, 5, 6, 0, 1
//  compare 7 and 2     2, 7, 9,| 3, 8, 4, 5, 6, 0, 1
//  compare 3 and 9     2, 7, 3, 9,| 8, 4, 5, 6, 0, 1
//  compare 3 and 7     2, 3, 7, 9,| 8, 4, 5, 6, 0, 1
//  compare 3 and 2     2, 3, 7, 9,| 8, 4, 5, 6, 0, 1
//  compare 8 and 9     2, 3, 7, 8, 9,| 4, 5, 6, 0, 1
//  compare 8 and 7     2, 3, 7, 8, 9,| 4, 5, 6, 0, 1
//* compare 4 and 9     2, 3, 7, 8, 9,| 4, 5, 6, 0, 1
void insert_sort_test() {
    const int size = 10;
    double v1[size] = {2, 9, 7, 3, 8, 4, 5, 6, 0, 1};

    for (int i = 0; i < size; ++i) {
        int j = i;
        while (true) {
            if (!(j > 0)) { break; } //middle condition
            if (!less(v1[j], v1[j - 1])) { break; } //middle condition
            exchange(v1, j, j - 1);
            j--;
        }
    }

    show_reset_count();

    double v2[size] = {2, 9, 7, 3, 8, 4, 5, 6, 0, 1};
    for (int i = 0; i < size; ++i) {
        int j = i;
        while (true) {
            if (!(j > 0)) { break; } //middle condition
            if (!less(v2[j], v2[j - 1])) {

            } else {
                exchange(v2, j, j - 1);
            }
            j--;
        }
    }
    show_reset_count();
}

//希尔排序
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

void merge(double *v, int low, int mid, int high, double *aux) {
    for (int i = low; i <= high; ++i) {
        aux[i] = v[i];
    }

    auto left_p = low, right_p = mid + 1;
    for (int i = low; i <= high; ++i) {
        if (left_p > mid) {
            v[i] = aux[right_p++];
        } else if (right_p > high) {
            v[i] = aux[left_p++];
        } else if (less(aux[left_p], aux[right_p])) {
            v[i] = aux[left_p++];
        } else {
            v[i] = aux[right_p++];
        }
    }
}

void merge_sort_recursive(double *v, int low, int high, double *aux) {
    if (high <= low) {
        return;
    }

    auto mid = low + (high - low) / 2;
    merge_sort_recursive(v, low, mid, aux);
    merge_sort_recursive(v, mid + 1, high, aux);
    merge(v, low, mid, high, aux);

}

//归并排序
void merge_sort_recursive(double *v) {
    auto aux = new double[ARRAY_SIZE];
    merge_sort_recursive(v, 0, ARRAY_SIZE - 1, aux);
}

//归并排序(改良)
//1. 对较小的数组采用插入排序
//2. 子数组已经有序时不再进行merge
//3. 辅助数组和原数组再递归中不断调换角色，减少复制次数
void merge_sort_recursive_opt(double *v, int low, int high, double *aux) {
    //TODO 用三种方法改良归并排序
}

void merge_sort_recursive_opt(double *v) {
    auto aux = new double[ARRAY_SIZE];
    merge_sort_recursive_opt(v, 0, ARRAY_SIZE - 1, aux);
}

//归并排序(非递归，自底向上)
void merge_sort(double *v) {
    auto aux = new double[ARRAY_SIZE];
    for (int sub_array_size = 1; sub_array_size < ARRAY_SIZE; sub_array_size *= 2) {
        for (int low = 0; low < ARRAY_SIZE - sub_array_size; low += sub_array_size * 2) {
            merge(v, low, low + sub_array_size - 1, std::min(low + 2 * sub_array_size - 1, ARRAY_SIZE - 1), aux);
        }
    }
}

int partition(double *v, int low, int high) {
    auto i = low, j = high + 1;
    auto p = v[low];
    while (true) {
        while (less(v[++i], p)) {
            if (i == high) {
                break;
            }
        }
        while (less(p, v[--j])) {
            if (j == low) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        exchange(v, i, j);
    }
    exchange(v, low, j);
    return j;

}

void quick_sort_recursive(double *v, int low, int high) {
    if (high <= low) return;

    auto j = partition(v, low, high);
    quick_sort_recursive(v, low, j - 1);
    quick_sort_recursive(v, j + 1, high);
}

//原生数组shuffle
void shuffle_origin_array(double *v) {
    std::default_random_engine engine;

    auto left_size = ARRAY_SIZE;
    for (int i = ARRAY_SIZE - 1; i >= 0; --i) {
        std::uniform_int_distribution<unsigned> u(0, left_size);
        auto rand_number = u(engine);
        auto p = rand_number % left_size;
        exchange(v, i, p);
        left_size--;
    }
}

//快速排序
void quick_sort_recursive(double *v) {
    shuffle_origin_array(v);
    quick_sort_recursive(v, 0, ARRAY_SIZE - 1);
}

void quick_sort_recursive_opt(double *v, int low, int high) {
    auto M = 10;
    if (high <= low + M) {
        insert_sort(v, low, high + 1);
        return;
    }

    auto equal_left = low, to_judge = low + 1, right_to_put_gt = high;

    //熵最优-三切分
    while (to_judge <= right_to_put_gt) {
        if (v[equal_left] > v[to_judge]) {
            exchange(v, equal_left++, to_judge++);
        } else if (v[equal_left] < v[to_judge]) {
            exchange(v, to_judge, right_to_put_gt--);
        } else {
            to_judge++;
        }
    }

    quick_sort_recursive_opt(v, low, equal_left - 1);
    quick_sort_recursive_opt(v, right_to_put_gt + 1, high);
}

//快速排序（优化）
//TODO 快速排序-三取样
void quick_sort_recursive_opt(double *v) {
    shuffle_origin_array(v);
    quick_sort_recursive_opt(v, 0, ARRAY_SIZE - 1);
}

void show_cost(std::chrono::duration<double> &cost) {
    std::cout << "cost time: " << cost.count() << "s" << std::endl;
    cost = cost - cost;
}

//优先队列（堆）
template<typename T>
class MaxPriorQueue {
private:
    T *_pq; //完全二叉树
    int _pq_max = 0, _size = 0;

    void swim(int k) {
        while (k > 1 && less(_pq[k / 2], _pq[k])) {
            exchange(_pq, k / 2, k);
            k /= 2;
        }
    }

    void sink(int k) {
        while (2 * k <= _size) {
            auto j = 2 * k;
            if (j < _size && less(_pq[j], _pq[j + 1]))
                j++;
            if (!less(_pq[k], _pq[j])) break;
            exchange(_pq, k, j);
            k = j;
        }
    }

public:
    explicit MaxPriorQueue(int max) {
        _pq_max = max;
        _pq = new T[max + 1];
    }

    bool is_empty() {
        return _size == 0;
    }

    int size() {
        return _size;
    }

    void insert(T v) {
        _pq[++_size] = v;
        swim(_size);
    }

    T delete_max() {
        auto max = _pq[1];
        exchange(_pq, 1, _size--);
        sink(1);
        return max;
    }
};

void test_queue() {
    auto v = build_random_vector();
    auto q = MaxPriorQueue<double>(ARRAY_SIZE);
    for (auto t: v) {
        q.insert(t);
        if (q.size() >= 10) {
            q.delete_max();
        }
    }

    while (!q.is_empty()) {
        std::cout << q.delete_max() << ", ";
    }
    std::cout << std::endl;

    show_reset_count();

}

void sink(double *heap, int i, int heap_size) {
    while (2 * i <= heap_size) {
        auto left_child_index = i * 2, right_child_index = i * 2 + 1, min_child_index = left_child_index;
        if (right_child_index <= heap_size && less(heap[left_child_index], heap[right_child_index])) {
            min_child_index = right_child_index;
        }

        if (less(heap[i], heap[min_child_index])) {
            exchange(heap, i, min_child_index);
        } else {
            break;
        }

        i = min_child_index;
    }
}

//堆排序
void heap_sort(double *v) {
    auto *heap = new double[ARRAY_SIZE + 1];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        heap[i + 1] = v[i];
    }

    auto length = ARRAY_SIZE;
    for (int i = ARRAY_SIZE / 2; i > 0; --i) {
        sink(heap, i, length);
    }

    while (length > 0) {
        exchange(heap, 1, length--);
        sink(heap, 1, length);
    }

    for (int i = 1; i <= ARRAY_SIZE; ++i) {
        v[i - 1] = heap[i];
    }

    delete[] heap;
}

void indexed_priority_queue_sort(double *v) {
    auto q = IndexedPriorityQueue<double>(ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        q.insert(i, v[i]);
    }

    for (int i = ARRAY_SIZE - 1; i >= 0; --i) {
        v[i] = q.min();
        q.delMin();
    }
}

void test_group(void (*f)(double *p), const std::string &name, bool only_random = false) {
    using namespace std::chrono;
    std::cout << "**** " << name << " sort ****" << std::endl;
    std::vector<double> v;
    double *arr;
    time_point<steady_clock> start, end;
    duration<double> cost{};
    if (!only_random) {
        std::cout << "----ordered vector----" << std::endl;
        v = build_sorted_vector();
        arr = convert_vector_to_array(v);

        start = steady_clock::now();
        f(arr);
        end = steady_clock::now();
        cost = duration_cast<duration<double>>(end - start);

        check_show_reset_count(arr);
        show_cost(cost);
    }

    std::cout << "----" << TEST_TIME << " random vector----" << std::endl;
    for (int i = 0; i < TEST_TIME; ++i) {
        v = build_random_vector();
        arr = convert_vector_to_array(v);

        start = steady_clock::now();
        f(arr);
        end = steady_clock::now();
        cost += duration_cast<duration<double>>(end - start);

        check_sorted(arr);
    }

    std::cout << "average exchange count: " << exchange_count / (double) TEST_TIME << std::endl;
    std::cout << "average compare count: " << compare_count / (double) TEST_TIME << std::endl;
    show_cost(cost);
    reset_count();


    if (!only_random) {
        std::cout << "----reversed vector----" << std::endl;
        v = build_sorted_vector();
        std::reverse(v.begin(), v.end());
        arr = convert_vector_to_array(v);

        start = steady_clock::now();
        f(arr);
        end = steady_clock::now();
        cost = duration_cast<duration<double>>(end - start);

        check_show_reset_count(arr);
        show_cost(cost);
    }
    std::cout << "*******************" << std::endl;
}

int main() {
//    test_group(select_sort, std::string("select"));
//    test_group(insert_sort, std::string("insert"));
    test_group(shell_sort, std::string("shell"));
    test_group(merge_sort_recursive, std::string("merge"));
    test_group(merge_sort, std::string("merge(bottom to up)"));
    test_group(quick_sort_recursive, std::string("quick"));
    test_group(quick_sort_recursive_opt, std::string("opt quick"));
    test_group(heap_sort, std::string("heap"));
    test_queue();
    test_group(indexed_priority_queue_sort, std::string("indexed priority queue"));

//    test_group(insert_sort, std::string("fast"), true);
//    test_group(insert_sort_slow, std::string("slow"), true);
//    insert_sort_test();
}