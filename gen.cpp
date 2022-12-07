#include <bits/stdc++.h>

using namespace std;
int rand(int l, int r) {
	static mt19937 rng(
			chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> test(l, r);
	return test(rng);
}

int main(){
    freopen("input.txt","w",stdout);
    int m=rand(1,20);
    cout<<m<<"\n";
    int n= m+1;  
    for(int i=0;i<n;i++){
        cout<<rand(1,1000000000)<<" "<<rand(1,1000000000)<<"\n";
    }

}