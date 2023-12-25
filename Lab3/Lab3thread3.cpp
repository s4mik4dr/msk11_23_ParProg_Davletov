#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

using namespace std;

// Функция для вычисления скалярного произведения векторов
size_t partialDotProduct(const vector<int> &v1, const vector<int> &v2, size_t start, size_t end)
{
    size_t result = 0;
    for (size_t i = start; i < end; ++i)
    {
        result += v1[i] * v2[i];
    }
    return result;
}

int main()
{
    // Инициализация векторов
    vector<int> vector1 = {1, 2, 3, 4, 5};
    vector<int> vector2 = {6, 7, 8, 9, 10};

    // Проверка на одинаковую длину векторов
    if (vector1.size() != vector2.size())
    {
        cerr << "Ошибка: Векторы должны быть одинаковой длины." << endl;
        return 1;
    }

    // Получение количества потоков, которые могут быть использованы
    const size_t numThreads = thread::hardware_concurrency();

    // Вычисление размера блока для каждого потока
    const size_t blockSize = vector1.size() / numThreads;

    // Вектор для хранения результатов вычислений каждого потока
    vector<int> partialResults(numThreads);

    // Вектор потоков
    vector<thread> threads;

    // Запуск потоков
    for (size_t i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(thread([&vector1, &vector2, &partialResults, i, numThreads, blockSize]()
                                    {
            size_t start = i * blockSize;
            size_t end =  (i == numThreads - 1) ? vector1.size() : start + blockSize;
            partialResults[i] = partialDotProduct(vector1, vector2, start, end); }));
    }

    // Ожидание завершения всех потоков
    for (auto &thread : threads)
    {
        thread.join();
    }

    // Суммируем результаты из всех потоков
    int finalResult = accumulate(partialResults.begin(), partialResults.end(), 0);

    // Выводим результат
    cout << "Скалярное произведение векторов: " << finalResult << endl;

    return 0;
}
