#include "template.hpp"

//if par[curr] is negative, curr is a root and -par[curr] is its size
int par[MAXN];
void intialize(int n){
	fill_n(par,n,-1);
}
int getPar(int curr){
	if(par[curr]<0)
		return curr;
	return par[curr]=getPar(par[curr]);
}

bool merge(int a,int b){
	int pA=getPar(a);
	int pB=getPar(b);
	if(pA==pB)
		return false;
	if(-par[pA]>-par[pB])
		swap(pA,pB);
	par[pB]+=par[pA];
	par[pA]=pB;
	return true;
}