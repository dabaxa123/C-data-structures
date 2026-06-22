#pragma once
#include "node.h"
#include <iostream>
#include <cassert>
#include <memory>
class RedBlackTree {
	static void setBlack(Node* node) { if (node) node->isBlack = true; }
	static void setRed(Node* node) { if (node) node->isBlack = false; }
	static bool isBlack(const Node* node) { return node == nullptr || node->isBlack; }
	static bool isRed(const Node* node) { return node != nullptr && !node->isBlack; }
	Node* o_root{};
	Node* rotateLeft(Node*);
	Node* rotateRight(Node*);
	Node* copy_subtree(Node*);
	void delete_subtree(Node*);
	Node* search(const int, Node*);
	void transplant(Node* u, Node* v);
	void deleteFixup(Node* x, Node* x_parent);
	Node* minimum(Node* node) {
		while (node && node->left)node = node->left;
		return node;
	}
	void inorder(Node* root, std::ostream& out) const;
	void preorder(Node* root, std::ostream& out) const;
	void postorder(Node* root, std::ostream& out) const;
	void insert_fix(Node* node);
	Node* insert(Node* root, Node* parent, int val, bool isLeft, Node*& inserted);

public:
	RedBlackTree()=default;
	RedBlackTree(const RedBlackTree& other);
	RedBlackTree& operator=(const RedBlackTree& other);
	~RedBlackTree();
	void insert(int value);
	bool search(int value);
	void erase(const int value);
	void inorder(std::ostream &out)const;
	void postorder(std::ostream& out)const;
	void preorder(std::ostream& out)const;

	
};