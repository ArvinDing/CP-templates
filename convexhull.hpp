#include "template.hpp"

//terrible precision problems, if using long doubles use kactl
vector<array<long long, 2>> p;
array<long long, 2> pivot;

long long norm(array<long long, 2> &a) {
	return a[0] * a[0] + a[1] * a[1];
}
long long cross(array<long long, 2> &a, array<long long, 2> &b, array<long long, 2> &cp) {
//cross vector a-cp, b-cp
	array<long long, 2> v { a[0] - cp[0], a[1] - cp[1] };
	array<long long, 2> v1 { b[0] - cp[0], b[1] - cp[1] };
	return v[0] * v1[1] - v[1] * v1[0];
}
bool cmp(array<long long, 2> a, array<long long, 2> b) {
	long long val = cross(a, b, pivot);
	array<long long ,2> aM{a[0]-pivot[0],a[1]-pivot[1]},bM{b[0]-pivot[0],b[1]-pivot[1]};
	return (val != 0) ? val > 0 : norm(aM) < norm(bM);
}
void convexHull() {
	int low = 0;
	//lowest point
	assert(p.size() >= 1);
	for (int i = 0; i < (int) p.size(); i++) {
		if (p[low][1] > p[i][1]
				|| (p[low][1] == p[i][1] && p[low][0] > p[i][0])) {
			low = i;
		}
	}
	pivot = p[low];
	vector<array<long long, 2>> temp, hull { pivot };
	for (array<long long, 2> a : p) {
		if (a!=pivot)
			temp.push_back(a);
	}
	sort(temp.begin(), temp.end(), &cmp);

	for (array<long long, 2> &a : temp) {
		while (hull.size() >= 2
				&& cross(a, hull[hull.size() - 2], hull[hull.size() - 1]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(a);
	}
//	cout<<hull.size()<<"\n";
//	for (auto a : hull) {
//		cout << a[0] << " " << a[1] << "\n";
//	}

}		