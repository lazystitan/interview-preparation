//
// Created by Riton on 2022/7/28.
//

#ifndef INTERVIEW_PREPARATION_ORIGIN_ARRAY_SORT_H
#define INTERVIEW_PREPARATION_ORIGIN_ARRAY_SORT_H

#include <optional>
#include <algorithm>


const int ARRAY_SIZE = 100000;
//const int ARRAY_SIZE = 10;
const unsigned int TEST_TIME = 10;
long int exchange_count = 0;
long int compare_count = 0;



std::vector<double> build_sorted_vector() {
    std::vector<double> v = {};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        v.push_back(i);
    }
    return v;
}

std::vector<double> build_random_vector() {
    auto v = build_sorted_vector();
    auto rng = std::mt19937(std::random_device()());
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

double *convert_vector_to_array(std::vector<double> &v) {
    auto arr = new double[ARRAY_SIZE];
    auto index = 0;
    for (auto i: v) {
        arr[index] = i;
        index++;
    }
    return arr;
}

template<typename T>
void exchange(T *v, unsigned int i, unsigned int j) {
    exchange_count++;
    auto temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

template<typename T>
bool less(T m, T n) {
    compare_count++;
    return m < n;
}

void reset_count() {
    exchange_count = compare_count = 0;
}

void show_count() {
    std::cout << "exchange count: " << exchange_count << std::endl;
    std::cout << "compare count: " << compare_count << std::endl;
}

template<typename T>
class IndexedPriorityQueue {
private:
    int count;
    std::vector<T> keys; // index是索引k，值是T
    std::vector<int> pq; // 堆排序的地方，index是计数count，exchange后会变；值是索引k
    std::vector<std::optional<int>> qp; // index是索引k，值是（如果有）pq中的index——既当时插入的count++的值，跟着pq的swap变化

    void swim(int p) {
        while (p > 1 && less(keys[pq[p / 2]], keys[pq[p]])) {
            exchange(p, p / 2);
            p = p / 2;
        }

    }

    void sink(int p) {
        while (p * 2 <= count) {
            auto left_child_index   = 2 * p,
                 right_child_index  = 2 * p + 1,
                 min_child_index    = left_child_index;

            if (right_child_index <= count && less(keys[pq[left_child_index]], keys[pq[right_child_index]])) {
                min_child_index = right_child_index;
            }

            if (!less(keys[pq[p]], keys[pq[min_child_index]])) break;

            exchange(p, min_child_index);
            p = min_child_index;
        }
    }

    void exchange(int i, int j) {
        std::swap(pq[i], pq[j]); //堆上的swap
        std::swap(qp[pq[i]], qp[pq[j]]); //跟着swap qp
    }

public:
    explicit IndexedPriorityQueue(int capacity) :
            count(0),
            keys(capacity),
            pq(capacity + 1),
            qp(capacity, std::nullopt) {}


    bool find_by_value() {
        auto p = std::find(keys.begin(), keys.end(), 2);
        auto index = p - keys.begin();
        auto index_k = std::find(pq.begin(), pq.end(),index);
        if (index_k != pq.end())
            return true;
        return false;

    }

    void insert(int k, T v) {
        count++;
        keys[k] = v;
        pq[count] = k;
        qp[k] = count;
        swim(count);
    }

    void change(int k, T v) {
        keys[k] = v;
        swim(*qp[k]);
        sink(*qp[k]);
    }

    bool containsByIndex(int k) {
        return qp[k].has_value();
    }

    void deleteByIndex(int k) {
        auto oldPositionOfK = *qp[k];
        exchange(oldPositionOfK, count--);
        swim(oldPositionOfK);
        sink(oldPositionOfK);
        qp[pq[count + 1]] = std::nullopt;
    }

    T min() {
        auto index = pq[1];
        return keys[index];
    }

    int minIndex() {
        return pq[1];
    }

    int delMin() {
        auto min_index = pq[1];
        exchange(1, count--);
        sink(1);
        qp[pq[count + 1]] = std::nullopt;
        return min_index;
    }

    bool isEmpty() {
        return keys.empty();
    }

    int size() {
        return keys.size();
    }
};

#endif //INTERVIEW_PREPARATION_ORIGIN_ARRAY_SORT_H
