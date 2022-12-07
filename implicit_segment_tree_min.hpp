#include "template.hpp"

struct Node {
	int lB, rB;
	Node *left = nullptr, *right = nullptr;
	int minV;
	int cMin;
	int lazy; //apply to left and right eventually
	Node(int lb, int rb) {
		lB = lb;
		rB = rb;
		minV = 0;
		cMin = rB - lB + 1;
		lazy = 0;
	}
	void createC() {
		if (!left && lB != rB) {
			int mid = (lB + rB < 0) ? (lB + rB - 1) / 2 : (lB + rB) / 2;
			left = new Node(lB, mid);
			right = new Node(mid + 1, rB);
		}
	}
	void pushL() {
		assert(left);
		left->minV += lazy;
		right->minV += lazy;
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
	void pullUp() {
		minV = min(right->minV, left->minV);
		cMin = 0;
		if (minV == right->minV) {
			cMin += right->cMin;
		}
		if (minV == left->minV) {
			cMin += left->cMin;
		}
	}
	void add(int l, int r, int val) {
		if (r < lB || rB < l)
			return;
		if (l <= lB && rB <= r) {
			minV += val;
			lazy += val;
			return;
		}
		createC();
		pushL();
		left->add(l, r, val);
		right->add(l, r, val);
		pullUp();
	}
};