#include <chrono>
#include <iostream>
#include <random>

#include "template.hpp"
using namespace std;
mt19937 rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
struct Node {
	Node *l = 0, *r = 0;
	ll val, y, cnt = 1;
	ll sumV = 0;
	Node(ll val) :
			val(val), y(rng()) {
		sumV = val;
	}
};
ll cnt(Node *a) {
	if (!a)
		return 0;
	return a->cnt;
}
ll sumV(Node *a) {
	if (!a)
		return 0;
	return a->sumV;
}
void updateN(Node *a) {
	a->cnt = cnt(a->l) + cnt(a->r) + 1;
	a->sumV = sumV(a->l) + sumV(a->r) + a->val;
}
//assuming x is sorted,split by val with  l containing all nodes with val< key
void split_val(Node *x, Node *&l, Node *&r, ll key) {
	if (!x) {
		l = r = 0;
		return;
	}
	ll mid = x->val;
	if (key <= mid) {
		split_val(x->l, l, x->l, key);
		r = x;
	} else {
		split_val(x->r, x->r, r, key);
		l = x;
	}
	updateN(x);
}
void split_idx(Node *x, Node *&l, Node *&r, ll inLeft) {
	// split x so that inLeft nodes in l
	if (!x) {
		r = l = nullptr;
		return;
	}
	if (inLeft <= cnt(x->l)) {
		split_idx(x->l, l, x->l, inLeft);
		r = x;
	} else {
		split_idx(x->r, x->r, r, inLeft - (1 + cnt(x->l)));
		l = x;
	}
	updateN(x);
}

Node* merge(Node *l, Node *r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		updateN(l);
		return l;
	} else {
		r->l = merge(l, r->l);
		updateN(r);
		return r;
	}
}
void prllN(Node *x) {
	if (!x)
		return;
	prllN(x->l);
	cout << x->val << " ";
	prllN(x->r);
}
struct Treap {
	// cnt is the number of nodes in the subtree
	Node *root = nullptr;
	Treap() {

	}
	Treap(Node *root) :
			root(root) {
	}
	operator Node *() {
		return root;
	}
	// max heap
	void prllT() {
		prllN(root);
		cout << "\n";
	}
	ll get(ll k) {
		assert(0 <= k && k < cnt(root));
		Node *a, *b, *c;
		split_idx(root, a, b, k);
		split_idx(b, b, c, 1);
		ll res = b->val;
		// get the value at the kth index
		root = merge(a, merge(b, c));
		return res;
	}
	void push_back(ll val) {
		if (cnt(root) == 0)
			root = new Node(val);
		else
			root = merge(root, new Node(val));
	}
	ll size() {
		return cnt(root);
	}
	//*** assuming treap is sorted***
	//how many values are strictly less
	void insert(ll val) {
		if (contains(val))
			return;
		Node *a, *b;
		split_val(root, a, b, val);
		root = merge(a, merge(new Node(val), b));
	}
	ll order_of_key(ll val) {
		Node *a, *b;
		split_val(root, a, b, val);
		ll res = cnt(a);
		root = merge(a, b);
		return res;
	}
	bool contains(ll val) {
		Node *a, *b;
		split_val(root, a, b, val);
		bool ans = false;
		Treap temp(b);
		if (cnt(b) != 0 && temp.get(0) == val) {
			ans = true;
		}
		root = merge(a, b);
		return ans;
	}

	//return erased succesfully or not
	bool erase_val(ll val) {
		Node *a, *b, *c;
		split_val(root, a, b, val);
		split_idx(b, b, c, 1);
		bool erased = b && (b->val == val);
		// get the value at the kth index
		if (erased)
			root = merge(a, c);
		else
			root = merge(a, merge(b, c));
		return erased;
	}
};
