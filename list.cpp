/*
g++ -std=c++11 list.cpp -o list
*/
#include<iostream>
#include<cassert>

template<typename T>
class list {
	
	struct Node {
	public:
		T val;
		struct Node *next;
		Node() : val(T(0)), next(nullptr) {}
		Node(T val) : val(val), next(nullptr) {}
		Node(T val, struct Node *next) : val(val), next(next) {}
	};

private:
	
	struct Node *start;

	/*
	swap values in a and b
	*/
	void __swap__(Node *a, Node *b) {
		T tmp = a->val;
		a->val = b->val;
		b->val = tmp;
	}

	/* 
	if(a>b){ return true; }
	if(a<=b){ return false; }
	*/
	bool __cmp__(Node *a, Node *b) {
		return a->val > b->val ? true : false;
	}
	
public:
	/*
	Initialize with a dummy node so that we dont need to check
	if it is a next or base pointer
	*/
	list() : start(new Node(T(0), nullptr)) { }

	/*
	Add new node at the end
	*/
	bool Append(T val) {
		Node *n = start;
		while (n->next != nullptr) {
			n = n->next;
		}
		n->next = new Node(val, nullptr);
		return true;
	}

	/*
	The algorithm here is to start deleting the
	next pointer from the before pointer rather 
	than the current pointer
	Example,
	list<0>(val, next) -> list<1>(val, next) -> list<2>(val, next) 
	be the current state in the while loop.
	We assign tmp = list<0>->next (which is list<1>)
	list<0>->next = list<0>->next->next (which is list<2>)
	now, delete tmp
	Hence it will be
	list<0>->next -> list<2>(val, next)
	*/
	bool Remove(T val) {
		// Set n to start
		Node *n = start;
		// Loop around if n->next 
		while (n->next != nullptr) {
			if (n->next->val == val) {
				Node *tmp = n->next;
				n->next = n->next->next;
				delete tmp;
				return true;
			}
			n = n->next;
		}
		/*
		if there is no val in the list, return false
		*/
		return false;
	}

	void Print() {
		Node *tmp = start->next;
		while (tmp->next != nullptr) {
			std::cout << tmp->val << " ";
			tmp = tmp->next;
		}
		std::cout << tmp->val << " ";
		std::cout << std::endl;
		return;
	}

	/*
	Do Bubble Sort
	*/
	void BubbleSort() {
		Node *tmp = start->next;
		while (tmp->next != nullptr) {
			Node *n = start->next;
			while (n->next != nullptr) {
				if (__cmp__(n, n->next)) {
					__swap__(n, n->next);
				}
				n = n->next;
			}
			tmp = tmp->next;
		}
	}

};


int main() {
	list<float> l;

	l.Append(13);
	l.Append(12);
	l.Append(11);
	l.Append(10);
	l.Print();
	l.BubbleSort();
	l.Print();
	
	assert(l.Remove(12) == true);
	l.Print();
	assert(l.Remove(12) == false);
	assert(l.Remove(13) == true);
	l.Print();

	std::cout << std::endl;
}
