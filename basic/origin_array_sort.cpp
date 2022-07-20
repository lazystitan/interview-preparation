//
// Created by Riton on 2022/7/19.
//
#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <ctime>
#include <chrono>


const unsigned int ARRAY_SIZE = 100000;
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

double* convert_vector_to_array(std::vector<double> &v) {
    auto arr = new double[ARRAY_SIZE];
    auto index = 0;
    for (auto i: v) {
        arr[index] = i;
        index++;
    }
    return arr;
}

void exchange(double *v, unsigned int i, unsigned int j) {
    exchange_count++;
    auto temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

bool less(double m, double n) {
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

//插入排序
void insert_sort(double *v) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int j = i; j > 0 && less(v[j], v[j - 1]); j--) {
            exchange(v, j, j - 1);
        }
    }
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
        while(true) {
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
        while(true) {
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


void show_cost(std::chrono::duration<double> &cost) {
    std::cout << "cost time: " << cost.count() << "s" << std::endl;
    cost = cost - cost;
}

void test_group(void (*f)(double *p), const std::string &name, bool single_random = false) {
    using namespace std::chrono;
    std::cout << "**** " << name << " sort ****" << std::endl;
    std::vector<double> v;
    double *arr;
    time_point<steady_clock> start, end;
    duration<double> cost{};
    if (!single_random) {
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


    if (!single_random) {
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
    test_group(select_sort, std::string("select"));
    test_group(insert_sort, std::string("insert"));
    test_group(shell_sort, std::string("shell"));

//    test_group(insert_sort, std::string("fast"), true);
//    test_group(insert_sort_slow, std::string("slow"), true);
//    insert_sort_test();
}