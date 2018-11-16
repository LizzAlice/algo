#ifndef ASSIGNMENT3_SKIPLIST_H
#define ASSIGNMENT3_SKIPLIST_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <limits>

using namespace std;
class SkipList {
private:
    struct Node {
        int64_t value = numeric_limits<int64_t>::min();
        Node* rightNode = nullptr;
        Node* downNode = nullptr;
        Node* leftNode = nullptr;
        int level = 0;

        Node() {

        }

        Node(int64_t value, int level) {
            this->value = value;
            this->level = level;
        }
    };
    Node* head;
    Node* findEndNodeInLevel(int64_t const x, int level);
    size_t elems = 0;
    int height;
public:
    SkipList(vector<int64_t> const &init);
    ~SkipList();
    size_t numElem();
    bool find(int64_t const x);
    bool insert(int64_t const x);
    bool remove(int64_t const x);


};


#endif //ASSIGNMENT3_SKIPLIST_H
