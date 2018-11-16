#include "SkipList.h"



SkipList::SkipList(vector<int64_t> const &init) {
    Node * minusInfinityNode = new Node();

    for (int64_t i : init) {
        insert(i);
    }

}

size_t SkipList::numElem() {
    return elems;
}

bool SkipList::find(int64_t const x) {
    Node* endNode = findEndNodeInLevel(x, 0);
    return x == endNode->value;

}



bool SkipList::insert(int64_t const x) {

    bool coinFlip = true;
    int level = 0;
    Node* downNode = nullptr;
    while(coinFlip) {
        Node *endNode = findEndNodeInLevel(x, level);
        if (endNode->value == x) {
            return false;
        }
        if(level >= height) {
            Node *minusInfinityNode = new Node();
            minusInfinityNode->level = level;
            height = level;
            head = minusInfinityNode;
        }

        Node* prevNode = endNode->leftNode;
        Node* nextNode = endNode;
        Node* insertionNode = new Node(x, level);


        insertionNode->leftNode = prevNode;
        insertionNode->rightNode = nextNode;
        insertionNode->downNode = downNode;
        prevNode->rightNode = insertionNode;

        coinFlip = false; //TODO flip coin
        ++level;
        downNode = insertionNode;
    }
    ++elems;
    return true;
}

SkipList::Node *SkipList::findEndNodeInLevel(int64_t const x, int level) {
    Node* currentNode = head;

    while(true) {
        if (x > currentNode->value && currentNode->rightNode != nullptr) {
            currentNode = currentNode->rightNode;
        } else {
            if (currentNode->level == level) {
                break;
            }
            currentNode = currentNode->downNode;
        }
    }
    return currentNode;

}

SkipList::~SkipList() {
    //TODO delete all nodes
}

bool SkipList::remove(int64_t const x) {

    Node *currentNode= findEndNodeInLevel(x, 0);;
    if(currentNode->value != x) {
        return false;
    }
    int level = 1;
    while(currentNode->value == x) {
        currentNode->leftNode->rightNode = currentNode->rightNode;
        currentNode->rightNode->leftNode = currentNode->leftNode;
        delete(currentNode);
        currentNode = findEndNodeInLevel(x,level);
    }

    --elems;
    return true;
}
