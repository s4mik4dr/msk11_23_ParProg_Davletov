#include <iostream>
#include <thread>

using namespace std;

// Функция, которую будут выполнять потоки
void threadFunction(int intValue, float floatValue, double *doubleValue)
{
    cout << "Поток ID: " << this_thread::get_id() << endl;
    cout << "int значение: " << intValue << endl;
    cout << "float значение: " << floatValue << endl;
    cout << "double значение: " << *doubleValue << endl;
}

int main()
{
    int intValue = 42;
    float floatValue = 3.14;
    double doubleValue = 2.71828;

    // Создание и запуск 3 потоков
    thread thread1(threadFunction, intValue, floatValue, &doubleValue);
    thread thread2(threadFunction, intValue + 1, floatValue + 1, &doubleValue);
    thread thread3(threadFunction, intValue + 2, floatValue + 2, &doubleValue);

    // Ожидание завершения потоков
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}
