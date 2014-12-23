// created date : 2008/11/14
// last updated : 2014/12/23 20:28:43
// C++11 std::thread サンプル
// g++-4.9.2 -O2 -std=c++11 thread2.cpp -lm -lpthread -o thread2

#include <vector>
#include <future>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
    std::vector<int> v(10);
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([i, &v] { v[i] = i * i; }));
    }
    for (std::thread &th : threads) {
        th.join();
    }
    for (int i : v) {
        cout << i << endl;
    }
    return 0;
}
