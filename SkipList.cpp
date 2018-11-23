#include <string>
#include <iostream>
#include <random>
#include "SkipList.h"



SkipList::SkipList(vector<int64_t> const &init) {
    Node * minusInfinityNode = new Node();
    head = minusInfinityNode;
    srand(static_cast<unsigned int>(time(0))); //set to 42
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
            minusInfinityNode->level = level + 1;
            minusInfinityNode->downNode = head;
            height = level + 1;
            head = minusInfinityNode;
        }

        Node* newNode = new Node(x, level);

        newNode->rightNode = endNode->rightNode;
        endNode->rightNode = newNode;
        newNode->leftNode = endNode;
        newNode->downNode = downNode;
        if (newNode->rightNode != nullptr)
            newNode->rightNode->leftNode = newNode;

        coinFlip = static_cast<bool>(rand() % 2); //TODO flip coin
        ++level;
        downNode = newNode;
    }
    ++elems;
    return true;
}

SkipList::Node *SkipList::findEndNodeInLevel(int64_t const x, int level) {
    Node* currentNode = head;

    while(true) {
        if (currentNode->rightNode != nullptr && x >= currentNode->rightNode->value) {
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
    int level = 0;
    while(currentNode->value == x) {
        currentNode->leftNode->rightNode = currentNode->rightNode;
        if(currentNode->rightNode != nullptr) {
            currentNode->rightNode->leftNode = currentNode->leftNode;
        }
        delete(currentNode);

        /*if (level == height-1) { //TODO reduce levels if highest node gets deleted
            if (head->downNode->rightNode == nullptr) {
                Node *newHead = head->downNode;
                delete(head);
                head = newHead;
                height = height - 1;
            }
        }*/
        ++level;
        currentNode = findEndNodeInLevel(x,level);
    }

    --elems;
    return true;
}

void SkipList::printSkipList() {
    Node *currentMinusInfinityNode = head;
    while(currentMinusInfinityNode != nullptr) {
        Node *currentNode = currentMinusInfinityNode;
        while(currentNode != nullptr) {
            cout << currentNode->value << " ";
            currentNode = currentNode->rightNode;
        }
        cout << endl;
        currentMinusInfinityNode = currentMinusInfinityNode->downNode;
    }
}
