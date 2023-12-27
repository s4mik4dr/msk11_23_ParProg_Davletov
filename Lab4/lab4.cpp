#include <iostream>
#include <thread>
#include <future>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    future<int> f = async(add, 5, 15);
    int result = f.get();
    cout << "Результат: " << result << endl;
    return 0;
}