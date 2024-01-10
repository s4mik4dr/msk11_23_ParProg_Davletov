#include <iostream>

int main()
{
    #pragma omp parallel
    {
        std::cout << "hello world" << std::endl;
    }
    return 0;
}