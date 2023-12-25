#include <thread>
#include <iostream>

using namespace std;

void threadProc()
{
    printf("Inside thread = %d", this_thread::get_id());
}

int main()
{
    thread t(threadProc);
    t.join();
}