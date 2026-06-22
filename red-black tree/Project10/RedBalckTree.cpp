#include "RedBalckTree.h"
RedBlackTree::RedBlackTree(const RedBlackTree& other)
{
	o_root = copy_subtree(other.o_root);
}
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other)
{
	if (this != &other) {
		std::destroy_at(this);
		std::construct_at(this, other);
	}
	return *this;
}
RedBlackTree::~RedBlackTree()
{
	delete_subtree(o_root);
}
//shemobruneba marcxniv
Node* RedBlackTree::rotateLeft(Node* root)
{
	//iqmneba axali shua nawilli
	Node* new_root = root->right;
	root->right = new_root->left;
	if (new_root->left) {
		new_root->left->parent = root;
		new_root->left->isleftChild = false;
	}
	new_root->parent = root->parent;
	new_root->isleftChild = root->isleftChild;
	if (!root->parent) {
		o_root = new_root;
	}
	else if (root->isleftChild) {
		root->parent->left = new_root;
	}
	else {
		root->parent->right = new_root;
	}
	new_root->left = root;
	root->parent = new_root;
	root->isleftChild = true;
	return new_root;
}

Node* RedBlackTree::rotateRight(Node*root)
{
	Node* new_root = root->left;
	root->left = new_root->right;
	if (new_root->right) {
		new_root->right->parent = root;
		new_root->right->isleftChild = false;
	}
	new_root->parent = root->parent;
	new_root->isleftChild = root->isleftChild;
	if (!root->parent) {
		o_root = new_root;
	}
	else if (root->isleftChild) {
		root->parent->left = new_root;
	}
	else {
		root->parent->right = new_root;
	}
	new_root->right = root;
	root->parent = new_root;
	root->isleftChild = false;
	return new_root;
}

Node* RedBlackTree::copy_subtree(Node* other)
{
	if (!other)
		return nullptr;
	auto* root = new Node{ other->value,other->isBlack,other->isleftChild,other->parent };
	root->left = copy_subtree(other->left);
	root->right = copy_subtree(other->right);
	return root;
}

void RedBlackTree::delete_subtree(Node* root)
{
	if (!root)return;
	delete_subtree(root->left);
	delete_subtree(root->right);
	delete root;
}

Node* RedBlackTree::search(const int val, Node*root)
{
	if (!root)return nullptr;
	if (val < root->value)return search(val, root->left);
	if (val > root->value)return search(val, root->right);
	return root;
}
void RedBlackTree::insert(int value)
{
	Node* new_node = nullptr;
	o_root = insert(o_root, nullptr, value, false, new_node);
	//tu ukve arsebobs vwyvetavt
	if (!new_node)return;
	insert_fix(new_node);
	if(o_root)
	setBlack(o_root);
}
bool RedBlackTree::search(int value)
{
	return search(value,o_root);
}
void RedBlackTree::inorder(std::ostream& out) const
{
	inorder(o_root, out);
}
void RedBlackTree::preorder(std::ostream& out) const
{
	inorder(o_root, out);
}
void RedBlackTree::postorder(std::ostream& out) const
{
	inorder(o_root, out);
}
void RedBlackTree::transplant(Node* node, Node* node_)
{
	//washlis dros gamogvadgeba
	if (!node->parent)o_root = node_;
	else if (node->isleftChild)node->parent->left =node_;
	else node->parent->right = node_;
	if (node_) {
		node_->parent = node->parent;
		node_->isleftChild = node->isleftChild;
	}
}
//iteraciuli
void RedBlackTree::deleteFixup(Node* x, Node* x_parent)
{
	while (x != o_root && x->isBlack == true&&x) {
		if (!x_parent)break;
		if (x == x_parent->left) {
			Node* w = x_parent->right;
			if (w->isBlack == false) {
				setBlack(w);
				setRed(x_parent);
				rotateLeft(x_parent);
				w = x_parent->right;
			}
			if (w->left->isBlack == true && w->right->isBlack == true) {
				setRed(w);
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else {
				if (isBlack(w->right)) {
					setBlack(w->left);
					setRed(w);
					rotateRight(w);
					w = x_parent->right;
				}
				if (w) w->isBlack = x_parent ? x_parent->isBlack : true;
				setBlack(x_parent);
				setBlack(w->right);
				rotateLeft(x_parent);
				x = o_root;
				break;
			}
		}
		else {
			Node* w = x_parent->left;
			if (isBlack(w)) {
				setBlack(w);
				setRed(x_parent);
				rotateRight(x_parent);
				w = x_parent->left;
			}
			if (w->left->isBlack == true && w->right->isBlack == true) {
				setRed(w);
				x = x_parent;
				x_parent = x_parent->parent;
			}
			else {
				if (isBlack(w->left)) {
					setBlack(w->right);
					setRed(w);
					rotateLeft(w);
					if(x_parent->left)
					w = x_parent->left;
				}
				if (w) w->isBlack = x_parent ? x_parent->isBlack : true;
				setBlack(x_parent);
				setBlack(w->left);
				rotateRight(x_parent);
				x = o_root;
				break;
			}
		}
	}
	setBlack(x);
}
//iteraciuli versia
void RedBlackTree::erase(const int val) {
	//tu ar arsebobs saertot root
	Node* root = search(val, o_root);
	if (!root)return;
	Node* y = root;
	bool original_color = isBlack(y);
	Node* x = nullptr;
	Node* xparent = nullptr;
	if (!root->left) {
		x = root->right;
		xparent = root->parent;
		transplant(root, root->right);
		delete root;
	}
	else if (!root->right) {
		x = root->left;
		xparent = root->parent;
		transplant(root, root->left);
		delete root;
	}
	else {
		y = minimum(root->right);//memkvidre ritac chavanacvlebt
		original_color = isBlack(y);
		x = y->right;//unda shevinaxot rom ar davkargot
		xparent = y->parent;
		if (y->parent == root) {
			xparent = y;
		}
		else {
			transplant(y, y->right);
			y->right = root->right;
			if (y->right) {
				y->right->parent = y;
				y->right->isleftChild = false;
			}
		}
		transplant(root, y);
		y->left = root->left;
		if (y->left) {
			y->left->parent = y;
			y->left->isleftChild = true;
		}
		y->isBlack = root->isBlack;
		delete root;
	}
	//tu chven wavshalet shavi unda shevasworot shavebis raodenoba gzebze
	if (original_color) {
		deleteFixup(x, xparent);
	}
    //tu rutia mashin gavashavot
	if (o_root)o_root->isBlack = true;
}

void RedBlackTree::inorder(Node* root, std::ostream& out) const
{
	if (root) {
		inorder(root->left, out);
		out << root->value << ' '<<root->isBlack<<' ';
		inorder(root->right, out);
	}
}
void RedBlackTree::preorder(Node* root, std::ostream& out) const
{
	if (root) {
		preorder(root->left, out);
		out << root->value << ' ' << root->isBlack << ' ';
		preorder(root->right, out);
	}
}
void RedBlackTree::postorder(Node* root, std::ostream& out) const
{
	if (root) {
		postorder(root->left, out);
		out << root->value << ' ' << root->isBlack << ' ';
		postorder(root->right, out);
	}
}
void RedBlackTree::insert_fix(Node* node)
{
	if (!node) return;
	// root an parent dasruldeba
	if (node == o_root || !node->parent || isBlack(node->parent)) {
		setBlack(o_root);
		return;
	}
	Node* parent = node->parent;
	Node* grand = parent->parent;
	if (!grand) { // parent iyo root
		setBlack(o_root);
		return;
	}
	// parent aris grandparent-is marcxena shvili
	if (parent == grand->left) {
		Node* unt = grand->right; // mamida
// pirveli shemTxveva gadagebva
		if (isRed(unt)) {
			setBlack(parent);
			setBlack(unt);
			setRed(grand);
			insert_fix(grand);
			return;
		}
		//meore LR
		if (node == parent->right) {
			rotateLeft(parent);
// rotation-is mere "node" da "p" icvleba: axali z dzveli parent
			node = parent;
			parent = node->parent;
			grand = parent ? parent->parent : nullptr;
			if (!grand) { setBlack(o_root); return; }
		}
		// mesame LL 
		setBlack(parent);
		setRed(grand);
		rotateRight(grand);
		setBlack(o_root);
		return;
	}
	//axla piriqit
	else {
		Node* unt = grand->left;
		if (isRed(unt)) {
			setBlack(parent);
			setBlack(unt);
			setRed(grand);
			insert_fix(grand);
			return;
		}
		//rl
		if (node == parent->left) {
			rotateRight(parent);
			node = parent;
			parent = node->parent;
			grand = parent ? parent->parent : nullptr;
			if (!grand) { setBlack(o_root); return; }
		}
		//rr
		setBlack(parent);
		setRed(grand);
		rotateLeft(grand);
		setBlack(o_root);
		return;
	}
}

Node* RedBlackTree::insert(Node* root, Node* parent, int val, bool isLeft, Node*& inserted)
{
	//chveulebriv rogorc avl tree-shi
	if (!root) {
		inserted=new Node{ val,false,isLeft,nullptr };
		return inserted;
	}
	if (val <root->value) { 
		root->left = insert(root->left, root, val, true, inserted);
	}
	else if (val > root->value) { 
		root->right = insert(root->right, root, val, false, inserted);
	}
	else inserted = nullptr;
	return root;
}
