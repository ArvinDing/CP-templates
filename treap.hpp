#include <chrono>
#include <iostream>
#include <random>
#include "template.hpp"
using namespace std;
mt19937 rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
struct Node {
	Node *l = 0, *r = 0;
	int val, y, cnt = 1;
	Node(int val) :
			val(val), y(rng()) {
	}
};
//max heap
int cnt(Node *a) {
	if (!a)
		return 0;
	return a->cnt;
}
void updCnt(Node *a) {
	a->cnt = cnt(a->l) + cnt(a->r) + 1;
}
//reference to a pointer, pass by reference
void split(Node *x, Node *&l, Node *&r, int key, int toLeft) {
	if (!x) {
		l = r = 0;
		return;
	}
	int mid = toLeft + cnt(x->l);
	if (key <= mid) {
		split(x->l, l, x->l, key, toLeft);
		r = x;
	} else {
		split(x->r, x->r, r, key, toLeft + cnt(x->l) + 1);
		l = x;
	}
	updCnt(x);
}
Node* merge(Node *l, Node *r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		updCnt(l);
		return l;
	} else {
		r->l = merge(l, r->l);
		updCnt(r);
		return r;
	}
}

void printN(Node *x) {
	if (!x)
		return;
	printN(x->l);
	cout << x->val<<" ";
	printN(x->r);

}