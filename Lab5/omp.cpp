#include <iostream>
#include <vector>

using namespace std;

double dotProduct(const vector<int> &a, const vector<int> &b, const int &size) {
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < size; ++i) {
        result += a[i] * b[i];
    }

    return result;
}

int main() {
    vector<int> vector1 = {1, 2, 3, 4, 5};
    vector<int> vector2 = {6, 7, 8, 9, 10};

    if (vector1.size() != vector2.size())
    {
        cerr << "Ошибка: Векторы должны быть одинаковой длины." << endl;
        return 1;
    } 

    int size = vector1.size();
    
    int result = dotProduct(vector1, vector2, size);

    cout << "Скалярное произведение: " << result << endl;

    return 0;
}