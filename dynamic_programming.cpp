//
// Created by Riton on 2022/8/26.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

std::vector<int> build_random_vector(int size) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);
    std::uniform_int_distribution<int> dist(-10, 10);
    auto v = std::vector<int>();
    for (int i = 0; i < size; ++i) {
        v.push_back(dist(rand_num));
    }
    return v;
}

int COUNT = 0;

int maxValue(std::vector<int> values) {
    COUNT = 0;
    int max = INT32_MIN;
    for (int start = 0; start < values.size(); ++start) {
        for (int end = start; end < values.size(); ++end) {
            int s = 0;
            for (int i = start; i <= end; ++i) {
                s += values[i];
                COUNT++;
            }
            if (s > max) {
                max = s;
            }
//            std::cout << start << " " << end << " sum:" << s << std::endl;
        }
    }
    return max;
}

int maxValueN2(std::vector<int> values) {
    COUNT = 0;
    int max = INT32_MIN;
    for (int end = 0; end < values.size(); ++end) {
        int s = 0;
        for (int start = end; start >= 0; --start) {
            s += values[start];
            if (s > max) {
                max = s;
            }
            COUNT++;
        }
    }
    return max;
}

int maxValueN3(std::vector<int> values) {
    COUNT = 0;
    auto dp_arr = std::vector<int>(values.size());

    dp_arr[0] = values[0];
    for (int i = 1; i < values.size(); ++i) {
          dp_arr[i] = std::max(dp_arr[i - 1] + values[i], values[i]);
          COUNT++;
    }

    auto max = 0;
    for (auto s: dp_arr) {
        if (s > max) max = s;
    }
    return max;
}


std::vector<int> draw_graph(int f(std::vector<int>), const std::vector<std::vector<int>>& values_array) {
    auto r = std::vector<int>();
    for (const auto& values : values_array) {
        r.push_back(f(values));
        std::cout << values.size() <<" "<< COUNT << std::endl;
    }
    return r;
}

int main() {
    std::vector<std::vector<int>> values_array;
    for (int i = 10; i < 1000; i += 10) {
        values_array.push_back(build_random_vector(i));
    }
    for (auto v: values_array[0]) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    auto r1 = draw_graph(maxValueN3, values_array);
    auto r2 = draw_graph(maxValueN2, values_array);
    for (int i = 0; i < r1.size(); ++i) {
        if (r1[i] != r2[i]) {
            std::cout << "wrong at "<< i << ":" << r1[i] << "-" << r2[i] << std::endl;
        }
    }

}