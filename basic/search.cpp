//
// Created by Riton on 2022/8/4.
//


#include <fstream>
#include <vector>
#include <iostream>
#include <optional>

template<typename Key, typename Value>
class SequentialSearchSymbolTable {
private:
    class Node {
    public:
        Key key;
        Value value;
        Node* next;
        Node(Key key, Value value, Node * next): key(key), value(value), next(next) {}
    };
    Node *first;
public:
    std::optional<Value> get(Key key) {
        auto p = first;
        while (p != nullptr) {
            if (p->key == key) {
                return std::optional<Value> (p->value);
            }
            p = p->next;
        }
        return std::optional<Value>();
    }

    void put(Key key, Value value) {
        auto p = first;
        while (p != nullptr) {
            if (p->key == key) {
                p->value = value;
                return;
            }
            p = p->next;
        }
        first = new Node(key, value, first);
    }

    bool contains(Key key) {
        auto p = first;
        while (p != nullptr) {
            if (p->key == key)
                return true;
            p = p->next;
        }
        return false;
    }

    std::vector<Key> keys() {
        auto r = std::vector<Key>();
        auto p = first;
        while (p != nullptr) {
            r.push_back(p->key);
            p = p->next;
        }
        return r;
    }
};

void read_test_file() {
    using namespace std;
    auto min_len = 5;
    auto st = new SequentialSearchSymbolTable<string, int>();
    string filename = "/mnt/f/code/interview-preparation/basic/test.txt";
//    string filename = "/mnt/f/code/interview-preparation/basic/leipzig1M.txt";
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "open file " << filename << " failed" << endl;
        return;
    }

    while (!fin.eof()) {
        string buff;
        fin >> buff;
        if (buff.length()  < min_len) {
            continue;
        }
        if (!st->contains(buff)) {
            st->put(buff, 1);
        } else {
            st->put(buff, st->get(buff).value() + 1);
        }
    }

    auto max = string(" ");
    st->put(max, 0);
    auto keys = st->keys();
    for (const auto& key: keys) {
        if (st->get(key) > st->get(max)) {
            max = key;
        }
    }

    cout << max << " " << st->get(max).value() << endl;
}

int main() {
    read_test_file();
}