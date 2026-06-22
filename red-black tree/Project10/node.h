#pragma once
class RedBlackTree;

class Node
{
    friend class RedBlackTree;
private:
    int value;
    bool isBlack;
    bool isleftChild;
    Node* parent;
    Node* left;
    Node* right;

public:
    //konstruqtori imisaTvis rom gamoviyenoT kopirebistvis
    Node(int val, bool black, bool leftChild, Node* par)
        : value(val), isBlack(black), isleftChild(leftChild), parent(par), left(nullptr), right(nullptr)
    {}
    //default kostruqtori
    Node(): value(0), isBlack(false), isleftChild(false), parent(nullptr), left(nullptr), right(nullptr){}
};