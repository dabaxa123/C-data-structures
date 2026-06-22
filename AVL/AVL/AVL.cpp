#include <iostream>
#include <algorithm>
class AVL {
	class Node{
	public:
		int key;
		Node* right;
		Node* left;
		int height;
		Node(int val) {
			key = val;
			right = left = nullptr;
			height = 1;
		}
	};
	int Height(Node* node) {
		if (node == nullptr)
			return 0;
		return node->height;
	}
	int get_factor(Node* root) {
		if (root == nullptr)
			return 0;
		return Height(root->left) - Height(root->right);
	}
	Node* rotate_right(Node* root) {
		Node* newroot = root->left;
		Node* temp = newroot->right;
		newroot->right = root;
		root->left = temp;
		root->height = std::max(Height(root->left), Height(root->right)) + 1;
		newroot->height = std::max(Height(newroot->left), Height(newroot->right)) + 1;
		return newroot;
	}
	Node* rotate_left(Node* root) {
		Node* newRoot = root->right;
		Node* temp = newRoot->left;
		newRoot->left = root;
		root->right = temp;
		//update heights
		root->height = std::max(Height(root->left), Height(root->right)) + 1;
		newRoot->height = std::max(Height(newRoot->left), Height(newRoot->right)) + 1;
		return newRoot;
	}
	Node* insertNode(Node* node,int key) {
		if (node == nullptr)return (new Node(key));
		if (key < node->key)node->left = insertNode(node->left, key);
		else if (key > node->key)node->right = insertNode(node->right, key);
		else return node;
		//balansi
		node->height = 1+std::max(Height(node->left),Height(node->right));
		int balance = get_factor(node);
		if (balance > 1) {
			if (key < node->left->key)
				return rotate_right(node);
			else if (key > node->left->key) {
				node->left = rotate_left(node->left);
				return rotate_right(node);
			}
		}
		if (balance < -1) {
			if (key < node->right->key) {
				node->right = rotate_right(node->right);
				return rotate_left(node);
			}
			else if (key > node->right->key)
				return rotate_left(node);
		}
		return node;
	}
	Node* minimum(Node* node) {
		Node* current = node;
		while (current->left) {
			current = current->left;
		}
		return current;
	}
	Node* deletenode(Node* node, int key) {
		if (!node)return node;
		if (key < node->key)node->left = deletenode(node->left, key);
		else if (key > node->key)node->right = deletenode(node->right, key);
		else
		{
			if ((node->left == nullptr) || (node->right == nullptr)) {
				Node* temp = node->left ? node->left : node->right;
				if (temp == nullptr) {
					temp = node;
					node = nullptr;
				}
				else
					*node = *temp;
				delete temp;
			}
			else {
				Node* temp = minimum(node->right);
				node->key = temp->key;
				node->right = deletenode(node->right, temp->key);
			}

		}
		if (node == nullptr)
			return node;
		node->height = 1 + std::max(Height(node->left), Height(node->right));
		int balanceFactor = get_factor(node);
		if (balanceFactor > 1) {
			if (get_factor(node->left) >= 0) {
				return rotate_right(node);
			}
			else {
				node->left = rotate_left(node->left);
				return rotate_right(node);
			}
		}
		if (balanceFactor < -1) {
			if (get_factor(node->right) <= 0) {
				return rotate_left(node);
			}
			else {
				node->right = rotate_right(node->right);
				return rotate_left(node);
			}
		}
		return node;
	}
	void print_tree(Node* root) {
		if (root != nullptr) {
			print_tree(root->left);
			std::cout << root->key << " ";
			print_tree(root->right);
		}
	}
	Node* root;
	public:
		AVL() {
			root = nullptr;
		}
		void insert(int val) {
			root = insertNode(root, val);
		}
		void display() {
			print_tree(root);
		}

};
int main()
{
	AVL a1;
	a1.insert(33);
	a1.insert(13);
	a1.insert(53);
	a1.insert(9);
	a1.insert(21);
	a1.insert(61);
	a1.insert(8);
	a1.insert(12);
	a1.display();
}