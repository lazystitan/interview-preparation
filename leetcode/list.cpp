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
#include <unordered_map>

#include "../basic/origin_array_sort.h"
#include "test_constants.h"

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
    //判断链表是否有环
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

    //是否能从字典中拼接出目标字符串，可重复
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

    //找出只出现一次的数字
    int singleNumberSlow(std::vector<int> &nums) {
        auto m = std::unordered_map<int, int>();
        for (auto v : nums) {
            if (m.find(v) != m.end()) {
                m[v]++;
            } else {
                m[v] = 1;
            }
        }

        for (auto v : m) {
            if (v.second == 1) {
                return v.first;
            }
        }
        return 0;
    }

    int singleNumber(std::vector<int> &nums) {
        auto r = 0;
        for (auto v : nums) {
            r ^= v;
        }
        return r;
    }

    /**
     * k = 2, f = 4, n = 8
     * 2, 4, 6 | 5 = 4
     * 3, 6 | 4, 5 = 4
     * 4, 8 | 5 = 4
     *
     * k = 3, f = 4, n = 9
     *
     *
     * @param k
     * @param n
     * @return
     */
    int superEggDrop(int k, int n) {

    }

    //打乱数组
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

    //特殊矩阵中查找
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

    //滑动窗口的最大序列
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        auto q = IndexedPriorityQueue<int>(nums.size());
        q.find_by_value();
        auto r = std::vector<int>();
        for (int i = 0; i < k; ++i) {
            q.insert(i, nums[i]);
        }

        auto earliest = 0, next_add = k;
        while (next_add < nums.size()) {
            r.push_back(q.min());
            q.deleteByIndex(earliest);
            q.insert(next_add, nums[next_add]);
            earliest++;
            next_add++;
        }
        r.push_back(q.min());
        return r;
    }

    std::vector<int> leetCodeMaxSlidingWindow(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::priority_queue<std::pair<int, int>> q;
        for (int i = 0; i < k; ++i) {
            q.emplace(nums[i], i);
        }
        std::vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i) {
            q.emplace(nums[i], i);
            while (q.top().second <= i - k) {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};

class MedianFinder {
    std::vector<int> nums;

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
    using namespace std;
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

    auto nums = vector<int> {1,3,-1,-3,5,3,6,7};
    auto k = 3;

    nums = vector<int>();
    for (auto i : INPUT) {
        nums.push_back(i);
    }

    k = WINDOW_SIZE;

    cout << nums.size() << endl;

    auto r = s->maxSlidingWindow(nums, k);
    cout << r.size() << endl;


    auto r2 = s->leetCodeMaxSlidingWindow(nums, k);
    cout << r2.size() << endl;

    for (int i = 0; i < r.size(); ++i) {
        if (r[i] != r2[i]) {
            cout << i << " : " << r[i] << "!=" << r2[i] << endl;
        }
    }

    nums = vector<int> {4,1,2,1,2};
    cout << s->singleNumber(nums) << endl;

//    for (auto i : r) {
//        cout << i << ", ";
//    }
//    cout << endl;
}