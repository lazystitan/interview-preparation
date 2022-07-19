//
// Created by Riton on 2022/7/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>

unsigned int VECTOR_SIZE = 100;

std::vector<int> build_random_vector() {
    std::vector<int> v = {};
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        v.push_back(i);
    }
    auto rng = std::mt19937(std::random_device()());
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

#define quick_return(v) {if ((v).empty() || (v).size() == 1) return;}

void exchange(std::vector<int> &v, unsigned int i, unsigned int j) {
    auto temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//选择排序
void select_sort(std::vector<int> &v) {
    quick_return(v);

    auto index_to_put = 0;
    while (index_to_put < v.size()) {
        auto min_value_index = index_to_put;
        for (int i = index_to_put; i < v.size(); i++) {
            auto value = v[i];
            if (v[min_value_index] > value) {
                min_value_index = i;
            }
        }
        exchange(v, min_value_index, index_to_put);
        index_to_put++;
    }
}

//插入排序
void insert_sort(std::vector<int> &v) {
    quick_return(v);

    auto to_insert = 1;
    while ( to_insert < v.size() ) {
        for (int i = 0; i < to_insert; i++) {
            if (v[to_insert] < v[i]) {
                auto temp = v[to_insert];
                for (int j = i; j < to_insert; ++j) {
                    v[j+1] = v[j];
                }
                v[i] = temp;
                break;
            }
        }
        to_insert++;
    }
}

void shell_sort(std::vector<int> &v) {
    quick_return(v);


}

int main() {
    auto v = build_random_vector();
    select_sort(v);
    assert(std::is_sorted(v.begin(), v.end()));

    v = build_random_vector();
    insert_sort(v);
    assert(std::is_sorted(v.begin(), v.end()));

}