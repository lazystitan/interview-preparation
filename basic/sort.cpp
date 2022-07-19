//
// Created by Riton on 2022/7/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>

unsigned int VECTOR_SIZE = 100;

std::vector<int> build_sorted_vector() {
    std::vector<int> v = {};
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        v.push_back(i);
    }
    return v;
}

std::vector<int> build_random_vector() {
    auto v = build_sorted_vector();
    auto rng = std::mt19937(std::random_device()());
    std::shuffle(v.begin(), v.end(), rng);
    return v;
}

#define quick_return(v) {if ((v).empty() || (v).size() == 1) return;}

int exchange_count = 0;
int compare_count = 0;

void exchange(std::vector<int> &v, unsigned int i, unsigned int j) {
    exchange_count++;
    auto temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

bool less(int m, int n) {
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

void check_sorted(std::vector<int> &v) {
    assert(std::is_sorted(v.begin(), v.end()));
}

void show_reset_count() {
    show_count();
    reset_count();
}

void check_show_reset_count(std::vector<int> &v) {
    check_sorted(v);
    show_reset_count();
}

//选择排序
void select_sort(std::vector<int> &v) {
    quick_return(v);

    auto index_to_put = 0;
    while (index_to_put < v.size()) {
        auto min_value_index = index_to_put;
        for (int i = index_to_put; i < v.size(); i++) {
            if (less(v[i], v[min_value_index])) {
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

    for (int i = 0; i < v.size(); ++i) {
        for (int j = i; j > 0; j--) {
            if (less(v[j], v[j - 1])) {
                exchange(v, j, j - 1);
            }
        }
    }
}

void shell_sort(std::vector<int> &v) {
    quick_return(v);
}

unsigned int TEST_TIME = 100;

void test_group(void (*f)(std::vector<int> &), const std::string &name) {
    std::cout << "**** " << name << " sort ****" << std::endl;
    std::cout << "----ordered vector----" << std::endl;
    auto v = build_sorted_vector();
    f(v);
    check_show_reset_count(v);

    std::cout << "----" << TEST_TIME << " random vector----" << std::endl;
    for (int i = 0; i < TEST_TIME; ++i) {
        v = build_random_vector();
        f(v);
        check_sorted(v);
    }

    std::cout << "average exchange count: " << exchange_count / (double) TEST_TIME << std::endl;
    std::cout << "average compare count: " << compare_count /  (double) TEST_TIME << std::endl;
    reset_count();



    std::cout << "----reversed vector----" << std::endl;
    v = build_sorted_vector();
    std::reverse(v.begin(), v.end());
    f(v);
    check_show_reset_count(v);
    std::cout << "*******************" << std::endl;
}

int main() {
    test_group(select_sort, std::string("select"));
    test_group(insert_sort, std::string("insert"));

}