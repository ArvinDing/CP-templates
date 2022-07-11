#include "template.hpp"
#include "mod.hpp"

mint fact[MAXN], invF[MAXN], invOf[MAXN];
int main(){
    //only works for prime modulo   
	fact[0] = fact[1] = 1, invF[0] = 1, invF[1] = 1, invOf[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fact[i] = fact[i - 1] * i;
		invOf[i] =  - (invOf[MODULO % i] * (MODULO / i));
		invF[i] = invF[i - 1] * invOf[i];
	}
}