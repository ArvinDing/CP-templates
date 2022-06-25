#include <chrono>
using namespace std;

auto start = std::chrono::high_resolution_clock::now();
//cout<<(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start)).count()<<endl;