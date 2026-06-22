#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;


template<typename T>
class Staque {
	class Node {
	public:
		T data;
		Node* next;
		Node* prev;
		Node(T val, ) {
			data = val;
			next = nullptr;
			prev = nullptr;
		}
	};
	Node* top;//top cgem shemtxvevashi iqneba  pirveli shemotani ricxvi ris mixedvitac gadavalt marjvniv an marxcniv
	Node* left;//marcxniv myofi kenti
	Node* right;//marjvniv luzi
	int size;
	int evens;//shemdegshi gamoviyenebt shesadareblad
	int odds;
	vector<Node*> order;
	int index(Node* n)const {
		for (size_t i = 0; i < order.size(); i++)
			if (order[i] == n)return static_cast<int>(i);
		return -1;
	}
	void remove(Node* n) {
		if (!n)return;
		if (n->prev)  n->prev->next = n->next;
	}
public:
	Staque();
	~Staque();
	Staque(const Staque& other)
	{
		//samive pointer vunulebt
		top = left = right = nullptr;
		size = 0;//radgan shemdegshi cven gamoviyenebt push-s romelic isedac zrdis zomas
		if (!other.IsEmpty())//rasac vakopirebt tu ar aris carieli
		{
			Node8 Temp = other.left//viwyebt marcxnidan
				while (Temp != nullptr)
				{
					push_some(cur->data);
					cur = cur->next;
				}
		}
	}
	//gansvaveba marto isaa rom unda shemowmdes xdeba tu ara tavis tavis gatoleba
	Staque& operator=(const Staque& other)
	{
		//aseve unda moxdes ganadgureba jer da shemdeg dakopireba
		if (this != &other)
		{
			size = other.size;
			this->~MyQueue();
			if (other.Empty())
				top = left = right = nullptr;
			else
			{
				top = left = right = nullptr;
				size = 0;
				Node* Temp = other.left;
				while (Temp != nullptr)
				{
					push_some(cur->data);
					Temp = Temp->next;
				}
			}

		}

		return *this;
	}
	friend ostream& operator<<(ostream& os, const Staque<T>& s) {
		typename Staque<T>::Node* temp = s.left;
		while (temp != nullptr) {
			os << temp->data << " ";
			temp = temp->next;
		}
	}
	bool Empty()const;
	int size()const { return size; }
	int even_c()const{return evens;}
	int odd_c()const { return odds; }
	bool gvaqvs(int val)const {
		for (Node* n : order)
			if (n->data == val)return true;
		return false;
	}
	void push_some(T val)//!!!!!!!!!!!
	{
		if (gvaqvs(val))return;
		Node* ptr = new Node(val);

		if (Empty())
		{
			top = left = right = ptr;

		}
		else if(val%2==0) {
			ptr->prev= right;
			right->next = ptr;
			right = ptr;
		}
		else {
			ptr->next = left;
			left->prev = ptr;
			left = ptr;
		}
		order.push_back(node);
		++size;;
		if (val % 2 == 0)++evens;
		else ++odds;	
	}
	void clear() {
		Node* current = left;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next
		}
		top = left = right = nullptr;
		order.clear();
		size = 0;
		evens = odds = 0;
	}
	int pick_last()const {
		if (empty())throw runtime_error("staque is empty");
		Node* l = order.back();
		return last->data
	}
	int pop_last() {
		if (empty())throw runtime_error("staque is empty");
		Node* last = order.back();
		int val = last->data;
		remove(last);
		return val;
	}
	bool search(int val)const {
		if (empty())return false;
		if (val % 2 == 0) {
			Node* cur = right;
			while (cur && (cur->data % 2 == 0)) {
				if (cur->data == val)return true;
				cur = cur->prev;
			}
			return false;
		}
		else {
			Node* cur = left;
			while (cur && (cur->data % 2 != 0)) {
				if (cur->data == val)return true;
				cur = cur->next;
			}
			return false;
		}
	}
	void deleteItems(int evens_d = 0, int odds_d = 0, int total = 0) {
		if (evens_d > 0) {
			if (evens_d > evens) {
				cout << "not enough elements to delete" << endl;
			}
			else {
				for (int i = 0; i < evens_d; i++) {
					remove(right):
				}
				cout << "deletedc " << evens_d << endl;
			}
		}
		if (odds_d > 0) {
			if (odds_d > odds) {
				cout << "not enough elements to delete" << endl;
			}
			else {
				for (int i = 0; i < evens_d; ++i)
					remove(left);
			}
			cout << "deleted " << odds_d << endl;
		}
	}
	if (total > 0) {
		if (total >= ) {
			clear();
			cout << "deleted " << total << endl;
		}
		else {
			for (int i = 0; i < total; ++i)
				Node* last = order.back();
				remove(last);
		}
		cout << " deleted " << total << end;
	}
	int wyoba(bool even)const {
		return even ? evens : odds;
	}
	vector<int> wyoba(bool even)const {
		vector<int> res;
		if (even) {
			Node* cur = right;
			while (cur) {
				if (cur->data % 2 == 0)res.pushback(cur->data);
				else break;
				cur = cur->prev;
			}
		}
		else {
			Node* cur = left;
			while (cur) {
				if (cur->data % 2 == 1)res.pushback(cur->data);
				else break;
				cur = cur->next;
			}
		}
		return res;
	}
};
template<typename T>
Staque<T>::Staque() {
	top = left = right = nullptr;
	size = 0;
}
template<typename T>
bool Staque<T>::Empty()const {
	return size == 0;
}
template<typename T>
Staque<T>::~Staque()
{
	clear();
}

