//
// Created by Riton on 2022/7/25.
//
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>
#include <random>
#include <iostream>
#include <queue>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        auto slow = head, fast = head->next->next;
        while (true) {
            if (fast == slow) {
                return true;
            }

            if (fast == nullptr || fast->next == nullptr || fast->next->next == nullptr) {
                return false;
            }

            fast = fast->next->next;
            slow = slow->next;

        }
    }

    bool wordBreak(std::string s, std::vector<std::string> &wordDict) {
        auto wordDictSet = std::unordered_set<std::string>();
        for (auto w: wordDict) {
            wordDictSet.insert(w);
        }
        auto dp = std::vector<bool>(s.size() + 1);
        dp[0] = true;

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && (wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end())) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[s.size()];
    }

    int singleNumber(std::vector<int> &nums) {


    }

    std::vector<int> shuffle(std::vector<int> origin_nums) {
        auto v = std::vector<int>(origin_nums);
        std::default_random_engine e(static_cast<unsigned int>(time(nullptr)));

        auto left_number = v.size() - 1;
        for (int i = v.size() - 1; i > 0; --i) {
            auto u = std::uniform_int_distribution<unsigned int>(0, left_number);
            auto p = u(e);

            auto t = v[p];
            v[p] = v[i];
            v[i] = t;
        }
        return v;
    }

    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
        if (matrix.size() == 0) {
            return false;
        } else if (matrix[0].size() == 0) {
            return false;
        }
        int i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] > target) {
                j--;
            } else if (matrix[i][j] < target) {
                i++;
            } else {
                return true;
            }
        }
        return false;
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    }
};

class IndexedPriorityQueue {
    vector<int> _v;
    vector<int> _index_map;

};

class MedianFinder {
    vector<int> nums;

public:
    MedianFinder() = default;

    void addNum(int num) {
        nums.push_back(num);

    }

    double findMedian() {
        sort(nums.begin(), nums.end());
        if (nums.size() % 2 == 0) {
            return (nums[nums.size() / 2 - 1] + nums[nums.size() / 2]) / 2.0;
        } else {
            return nums[nums.size() / 2];
        }
    }
};


int main() {
    int l_value[28] = {-21, 10, 17, 8, 4, 26, 5, 35, 33, -7, -16, 27, -12,
                       6, 29, -12, 5, 9, 20, 14, 14, 2, 13, -24, 21, 23, -21, 5};

    auto head = new ListNode(l_value[0]), p = head;
    for (int i = 1; i < 28; ++i) {
        p->next = new ListNode(l_value[i]);
        p = p->next;
    }

    auto s = new Solution();

    s->hasCycle(head);

    auto wordDict = std::vector<std::string>{"aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa",
                                             "aaaaaaaaaa", "ba"};

    auto to_find = std::string(
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    s->wordBreak(to_find, wordDict);

    s->shuffle(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});

    int target = 5;
    auto matrix = vector<vector<int>>();
    matrix.push_back(vector<int>{1,4,7,11,15});
    matrix.push_back(vector<int>{2,5,8,12,19});
    matrix.push_back(vector<int>{3,6,9,16,22});
    matrix.push_back(vector<int>{10,13,14,17,24});
    matrix.push_back(vector<int>{18,21,23,26,30});

    s->searchMatrix(matrix, target);

    auto finder = MedianFinder();
    finder.addNum(1);
    finder.addNum(2);
    cout << finder.findMedian() << endl;
    finder.addNum(3);
    cout << finder.findMedian() << endl;
    finder.addNum(4);
    cout << finder.findMedian() << endl;
}