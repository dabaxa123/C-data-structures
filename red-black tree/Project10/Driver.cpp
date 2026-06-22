// driver.cpp
#include <iostream>
#include <vector>
#include <cassert>
#include "RedBalckTree.h"

static void printTitle(const char* t) {
    std::cout << "\n " << t << "\n";
}

int main() {
   //vamowmebt
    RedBlackTree t;
    //chavwerot ricxvebi
    std::vector<int> vals{ 10, 20, 30, 15, 25, 5, 1, 50, 60, 55, 40 };
    for (int x : vals) t.insert(x);
    std::cout << "Inorder chamatebis mere\n";
    t.inorder(std::cout);
    std::cout << "\n";
    // Search
    std::cout << "Search 25: " << std::boolalpha << t.search(25) << "\n";
    std::cout << "Search 99: " << std::boolalpha << t.search(99) << "\n";
    //wavshalot fotoli
    t.erase(1);
    //kide rame wavshalot
    t.erase(20);
    std::cout << "washlis mere:\n";
    t.inorder(std::cout);
    std::cout << "\n";
    t.erase(10);
    std::cout << "washlis mere(10):\n";
    t.inorder(std::cout);
    std::cout << "\n";
    //kopireba
    RedBlackTree copyTree(t);  // copy ctor
    std::cout << "CopyTree inorder:\n";
    copyTree.inorder(std::cout);
    std::cout << "\n";
   //miniweba
    RedBlackTree assignTree;
    assignTree.insert(1000);
    assignTree.insert(2000);
    std::cout << "miniwebamde:\n";
    assignTree.inorder(std::cout);
    std::cout << "\n";
    assignTree = t; // operator=
    std::cout << "miniwebis mere:\n";
    assignTree.inorder(std::cout);
    std::cout << "\n";
    std::cout << "\nyvelaferi shemowmda\n";
    return 0;
}
