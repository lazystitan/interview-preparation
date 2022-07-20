//
// Created by Riton on 2022/7/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <ctime>


unsigned int ARRAY_SIZE = 100000;

std::vector<int> build_sorted_vector() {
    std::vector<int> v = {};
    for (int i = 0; i < ARRAY_SIZE; ++i) {
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

int* convert_vector_to_array(std::vector<int> &v) {
    auto arr = new int[ARRAY_SIZE];
    auto index = 0;
    for (auto i: v) {
        arr[index] = i;
        index++;
    }
    return arr;
}

#define quick_return(v) {/*if ((v).empty() || (v).size() == 1) return;*/}

long int exchange_count = 0;
long int compare_count = 0;

void exchange(int *v, unsigned int i, unsigned int j) {
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

std::vector<int> convert_array_to_vector(int *arr) {
    auto v = std::vector<int>();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        v.push_back(arr[i]);
    }

    return v;
}

void check_sorted(int *arr) {
    auto v = convert_array_to_vector(arr);
    assert(std::is_sorted(v.begin(), v.end()));
}

void show_reset_count() {
    show_count();
    reset_count();
}

void check_show_reset_count(int *p) {
    check_sorted(p);
    show_reset_count();
}

//选择排序
void select_sort(int *v) {
    quick_return(v);

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

//插入排序
void insert_sort(int *v) {
    quick_return(v);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = i; j > 0; j--) {
            if (less(v[j], v[j - 1])) {
                exchange(v, j, j - 1);
            }
        }
    }
}

//希尔排序
void shell_sort(int *v) {
    quick_return(v);

    int h = 1;
    while (h < (ARRAY_SIZE / 3))
        h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < ARRAY_SIZE; i++) {
            for (int j = i; j >= h; j -= h) {
                if (less(v[j], v[j - h]))
                    exchange(v, j, j - h);
            }
        }

        h = h / 3;
    }
}

unsigned int TEST_TIME = 10;

void show_cost(double &cost) {
    std::cout << "cost time: " << cost << "ms" << std::endl;
    cost = 0;
}

void test_group(void (*f)(int *p), const std::string &name) {
    std::cout << "**** " << name << " sort ****" << std::endl;
    std::cout << "----ordered vector----" << std::endl;
    auto v = build_sorted_vector();
    auto arr = convert_vector_to_array(v);

    auto start = clock();
    f(arr);
    auto end = clock();
    auto cost = (double(end - start) / CLOCKS_PER_SEC) * 1000;

    check_show_reset_count(arr);
    show_cost(cost);

    std::cout << "----" << TEST_TIME << " random vector----" << std::endl;
    for (int i = 0; i < TEST_TIME; ++i) {
        v = build_random_vector();
        arr = convert_vector_to_array(v);

        start = clock();
        f(arr);
        end = clock();
        cost += (double(end - start) / CLOCKS_PER_SEC) * 1000;

        check_sorted(arr);
    }

    std::cout << "average exchange count: " << exchange_count / (double) TEST_TIME << std::endl;
    std::cout << "average compare count: " << compare_count / (double) TEST_TIME << std::endl;
    show_cost(cost);
    reset_count();


    std::cout << "----reversed vector----" << std::endl;
    v = build_sorted_vector();
    std::reverse(v.begin(), v.end());
    arr = convert_vector_to_array(v);

    start = clock();
    f(arr);
    end = clock();
    cost = (double(end - start) / CLOCKS_PER_SEC) * 1000;

    check_show_reset_count(arr);
    show_cost(cost);
    std::cout << "*******************" << std::endl;
}

int main() {
    test_group(select_sort, std::string("select"));
    test_group(insert_sort, std::string("insert"));
    test_group(shell_sort, std::string("shell"));

}