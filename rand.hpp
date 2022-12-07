#include "template.hpp"

int rand(int l, int r) {
	static mt19937 rng(
			chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> test(l, r);
	return test(rng);
}