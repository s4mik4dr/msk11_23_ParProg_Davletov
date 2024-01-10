#include <iostream>
#include <vector>

using namespace std;

// Функция для сложения двух векторов
void addVectors(const vector<int> &a, const vector<int> &b, vector<int> &result, const int &size) {
    // Директива pragma omp parallel for распараллеливает цикл
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    // Инициализация векторов
    vector<int> vector1 = {1, 2, 3, 4, 5};
    vector<int> vector2 = {6, 7, 8, 9, 10};

    // Проверка на одинаковую длину векторов
    if (vector1.size() != vector2.size())
    {
        cerr << "Ошибка: Векторы должны быть одинаковой длины." << endl;
        return 1;
    } 

    int size = vector1.size();

    vector<int> result(size);

    addVectors(vector1, vector2, result, size);

    // Вывод результата
    cout << "Результат сложения векторов: {";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    return 0;
}