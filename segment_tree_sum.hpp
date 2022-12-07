#include "template.hpp"

ll segT[4 * MAXN];
void update(int idx, int lB, int rB, int x, int val) {
	if (x < lB || rB < x) {
		return;
	}
	if (x == lB && rB == x) {
		segT[idx] = val;
		return;
	}
	int mid = (lB + rB) / 2;
	update(2 * idx, lB, mid, x, val);
	update(2 * idx + 1, mid + 1, rB, x, val);
	segT[idx] = segT[2 * idx]+ segT[2 * idx + 1];
}
ll query(int idx, int lB, int rB, int l, int r) {
	if (r < lB || rB < l) {
		return 0;
	}
	if (l <= lB && rB <= r)
		return segT[idx];
	int mid = (lB + rB) / 2;
	return query(2 * idx, lB, mid, l, r) + query(2 * idx + 1, mid + 1, rB, l, r);
}