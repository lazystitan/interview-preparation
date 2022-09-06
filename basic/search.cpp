//
// Created by Riton on 2022/8/4.
//


#include <fstream>
#include <vector>
#include <iostream>
#include <optional>

template<typename Key, typename Value>
class SymbolTable {
public:
    virtual std::optional<Value> get(Key key) = 0;

    virtual void put(Key key, Value value) = 0;

    virtual void deleteItem(Key key) = 0;

    virtual bool contains(Key key) {
        auto r = get(key);
        return r.has_value();
    };

    virtual bool empty() = 0;

    virtual int size() = 0;

    virtual std::vector<Key> keys() = 0;

};

template<typename Key, typename Value>
class SequentialSearchSymbolTable : public SymbolTable<Key, Value> {
private:
    class Node {
    public:
        Key key;
        Value value;
        Node* next;
        Node(Key key, Value value, Node * next): key(key), value(value), next(next) {}
    };
    Node *first = nullptr;
public:
    std::optional<Value> get(Key key) override {
        auto p = first;
        while (p != nullptr) {
            if (p->key == key) {
                return std::optional<Value> (p->value);
            }
            p = p->next;
        }
        return std::optional<Value>();
    }

    void put(Key key, Value value) override {
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

    bool contains(Key key) override {
        auto p = first;
        while (p != nullptr) {
            if (p->key == key)
                return true;
            p = p->next;
        }
        return false;
    }

    std::vector<Key> keys() override {
        auto r = std::vector<Key>();
        auto p = first;
        while (p != nullptr) {
            r.push_back(p->key);
            p = p->next;
        }
        return r;
    }

    bool empty() override {
        return first == nullptr;
    }

    int size() override {
        auto len = 0;
        auto p = first;
        while (p != nullptr) {
            len++;
            p = p->next;
        }
        return len;
    }

    void deleteItem(Key key) override {
        if (first == nullptr) return;
        if (first->next == nullptr && first->key == key) {
            delete first;
            first = nullptr;
        }

        auto p = first->next;
        while (p->next != nullptr) {
            if (p->next->key == key) {
                auto temp = p->next;
                p->next = p->next->next;
                delete temp;
            }
            p = p->next;
        }
    }
};


void read_test_file(SymbolTable<std::string, int> *st) {
    using namespace std;
    auto min_len = 5;
//    auto st = new SequentialSearchSymbolTable<string, int>();
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
        if (buff == "Lisbon") {
            auto x = 1;
        }
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

    st->deleteItem(max);
    for (const auto& key: keys) {
        if (st->get(key) > st->get(max)) {
            max = key;
        }
    }
    cout << max << " " << st->get(max).value() << endl;
}

template<typename Key, typename Value>
class BinarySearchSymbolTable : public SymbolTable<Key, Value> {
private:
    std::vector<std::pair<Key, Value>> pairs;
public:
//    explicit BinarySearchSymbolTable() {
//        pairs = std::vector<std::pair<Key, Value>>(capacity);
//    }

    int size() override {
        return pairs.size();
    }

    std::optional<Value> get(Key key) override {
        if (pairs.empty()) {
            return std::optional<Value>();
        }

        auto i = rank(key);
        if (i < pairs.size() && pairs[i].first == key) {
            return pairs[i].second;
        }
        return std::optional<Value>();
    }

    int rank(Key key) {
        auto low = 0, high = (int) pairs.size() - 1;
        while (low <= high) {
            auto mid = low + (high - low) / 2;
            if (key <  pairs[mid].first) {
                high = mid - 1;
            } else if (key == pairs[mid].first) {
                return mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }

    void put(Key key, Value value) override {
        auto i = rank(key);

        if (i < pairs.size() && pairs[i].first == key) {
            pairs[i].second = value;
            return;
        }

        pairs.push_back(std::make_pair(key, value));
        for (int j = pairs.size() - 1; j > i; j--) {
            auto temp = pairs[j];
            pairs[j] = pairs[j - 1];
            pairs[j - 1] = temp;
        }
    }

    void deleteItem(Key key) override {
        auto i = rank(key);
        for (int j = pairs.size() - 1; j > i; j--) {
            pairs[j - 1] = pairs[j];
        }
    }

    std::optional<Key> min() {
        if (pairs.empty()) {
            return std::optional<Key>();
        }
        return std::optional<Key>(pairs[0].first);
    }

    std::optional<Key> max() {
        if (pairs.empty()) {
            return std::optional<Key>();
        }
        return std::optional<Key>(pairs[pairs.size() - 1].first);
    }

    std::optional<Key> select(int k) {
        if (k > pairs.size() - 1) {
            return std::optional<Key>();
        }
        return std::optional<Key>(pairs[k].first);
    }

    bool contains(Key key) override {
        auto r = get(key);
        return r.has_value();
    }

    std::vector<Key> keys() override {
        auto r = std::vector<Key>();
        auto low_i = 0, high_i = (int) pairs.size();
        for (int i = low_i; i < high_i; ++i) {
            r.push_back(pairs[i].first);
        }
        return r;
    }

    std::vector<Key> keys(Key low, Key high) {
        auto r = std::vector<Key>();
        auto low_i = rank(low), high_i = rank(high);
        for (int i = low_i; i < high_i; ++i) {
            r.push_back(pairs[i].first);
        }
        if (contains(high)) {
            r.push_back(pairs[high_i].first);;
        }
        return r;
    }

    bool empty() override {
        return pairs.empty();
    }

};

template <typename Key, typename Value>
class BinarySearchTree : public SymbolTable<Key, Value> {
private:
    class Node {
    public:
        Key key;
        Value value;
        Node *left = nullptr, *right = nullptr;
        int N;
        Node(Key key, Value value, int N) : key(key), value(value), N(N) {}
    };
    Node *root = nullptr;
    int size(Node *n) {
        if (n == nullptr) {
            return 0;
        }
        return n->N;
    }

    Node* get(Node *n, Key key) {
        if (n == nullptr) {
            return n;
        }
        if (key > n->key) {
            return get(n->right, key);
        } else if (key == n->key) {
            return n;
        } else {
            return get(n->left, key);
        }
    }

    Node* put(Node *n, Key key, Value value) {
        if (n == nullptr) {
            return new Node(key, value, 1);
        }

        if (key > n->key) {
            n->right = put(n->right, key, value);
        } else if (key == n->key) {
            n->value = value;
        } else {
            n->left = put(n->left, key, value);
        }
        n->N = size(n->left) + size(n->right) + 1;
        return n;
    }

    void free(Node *n) {
        if (n == nullptr) {
            return;
        }
        free(n->left);
        if (n->left != nullptr)
            delete n->left;

        free(n->right);
        if (n->right != nullptr)
            delete n->right;
    }


    void keys(std::vector<Key> &r, Node *n) {
        if (n == nullptr) return;
        keys(r, n->left);
        r.push_back(n->key);
        keys(r, n->right);
    }

    Node* min(Node *node) {
        if (node->left == nullptr) {
            return node;
        }
        return min(node->left);
    }

    Node* deleteMin(Node *node, bool free = false) {
        if (node->left == nullptr) {
            auto r = node->right;
            if (free)  delete node; //free
            return r;
        }

        node->left = deleteMin(node->left);
        node->N = 1 + size(node->left) + size(node->right);
        return node;
    }

    Node* deleteItem(Node* node, Key key) {
        if (node == nullptr) return node;
        if (key < node->key) {
            node->left = deleteItem(node->left, key);
        } else if (key == node->key) {
            if (node->right == nullptr) {
                return node->left;
            }
            if (node->left == nullptr) {
                return node->right;
            }
            Node *t = node;
            node = min(t->right);
            node->right = deleteMin(t->right);
            node->left = t->left;
            delete t;
        } else {
            node->right = deleteItem(node->right, key);
        }
        node->N = 1 + size(node->left) + size(node->right);
        return node;
    }

public:
    void deleteMin() {
        deleteMin(root, true);
    }

    void deleteItem(Key key) override {
        root = deleteItem(root, key);
    }

    int size() override {
        if (root == nullptr) {
            return 0;
        }
        return size(root);
    }

    std::optional<Value> get(Key key) override {
        auto p = get(root, key);
        if (p == nullptr) {
            return std::optional<Value>();
        } else {
            return std::optional<Value>(p->value);
        }
    }

    void put(Key key, Value value) override {
        root = put(root, key, value);
    }

    bool empty() override {
        return size() == 0;
    }

    std::vector<Key> keys() override {
        auto r = std::vector<Key>();
        keys(r, root);
        return r;
    }

    ~BinarySearchTree() {
        free(root);
    }
};



template<typename Key, typename Value>
class RedBlackTree : public SymbolTable<Key, Value> {
private:
    enum Color {
        Red, Black
    };
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node *left = nullptr, *right = nullptr;
        int N;
        Node(Key key, Value value, int N, Color c) : key(key), value(value), N(N), color(c) {};
    };
    Node *root = nullptr;

    bool isRed(Node *node) {
        if (node == nullptr) {
            return false;
        }
        return node->color == Red;
    }

    int size(Node *n) {
        if (n == nullptr) {
            return 0;
        }
        return n->N;
    }

    Node* rotateLeft(Node *node) {
        auto r = node->right;
        node->right = r->left;
        r->left = node;
        r->color = node->color;
        node->color = Red;
        r->N = node->N;
        node->N = 1 + size(node->left) + size(node->right);
        return r;
    }

    Node* rotateRight(Node *node) {
        auto r = node->left;
        node->left = r->right;
        r->right = node;
        r->color = node->color;
        node->color = Red;
        r->N = node->N;
        node->N = 1 + size(node->left) + size(node->right);
        return r;
    }

    void flipColors(Node *node) {
        node->color = Red;
        node->left->color = Black;
        node->right->color = Black;
    }

    Node* put(Node *node, Key key, Value value) {
        if (node == nullptr) {
            return new Node(key, value, 1, Red);
        }

        if (key < node->key) {
            node->left = put(node->left, key, value);
        } else if (key == node->key) {
            node->value = value;
        } else {
            node->right = put(node->right, key, value);
        }

        if (isRed(node->left) && node->left != nullptr && isRed(node->left->left)) {
            node = rotateRight(node);
        } else if (isRed(node->left) && isRed(node->right)) {
            flipColors(node);
        } else if (!isRed(node->left) && isRed(node->right)) {
            node = rotateLeft(node);
        }

        node->N = 1 + size(node->left) + size(node->right);
        return node;
    }

    std::optional<Value> get(Node *n, Key key) {
        if (n == nullptr) {
            return std::optional<Value>();
        }
        if (key > n->key) {
            return get(n->right, key);
        } else if (key == n->key) {
            return std::optional<Value>(n->value);
        } else {
            return get(n->left, key);
        }
    }

public:
    int size() override {
        if (root == nullptr) {
            return 0;
        }
        return size(root);
    }

    void put(Key key, Value value) {
        root = put(root, key, value);
        root->color = Black;
    }

    std::optional<Value> get(Key key) override {
        return get(root, key);
    }

    bool empty() override {
        return size() == 0;
    }

    void keys(std::vector<Key> &r, Node *n) {
        if (n == nullptr) return;
        keys(r, n->left);
        r.push_back(n->key);
        keys(r, n->right);
    }

    std::vector<Key> keys() override {
        auto r = std::vector<Key>();
        keys(r, root);
        return r;
    }

};

int main() {
    using namespace std;
// very slow
//    auto *sst = new SequentialSearchSymbolTable<string, int>();
//    read_test_file(sst);

    auto bsst = BinarySearchSymbolTable<string, int>();
    read_test_file(&bsst);

    auto bst = BinarySearchTree<string, int>();
    read_test_file(&bst);

//    auto rbt = RedBlackTree<string, int>();
//    read_test_file(&rbt);

}