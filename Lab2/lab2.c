#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для записи времени выполнения в текстовый файл и вывода в консоли
void logExecutionTime(const char *functionName, clock_t start_time)
{
    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Время выполнения %s: %lf секунд\n", functionName, execution_time);

    FILE *time_file = fopen("times.txt", "a");
    if (time_file == NULL)
    {
        printf("Ошибка открытия файла для записи времени.\n");
        exit(1);
    }
    fprintf(time_file, "%s: %lf секунд\n", functionName, execution_time);
    fclose(time_file);
}

// Функция для создания массива указанного пользователем размера
int *createArray(int size)
{
    clock_t start_time = clock();
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("Ошибка выделения памяти для массива.\n");
        exit(1);
    }
    logExecutionTime("createArray", start_time);
    return array;
}

// Функция для заполнения массива индексами
void fillArrayWithIndices(int *array, int size)
{
    clock_t start_time = clock();
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
    logExecutionTime("fillArrayWithIndices", start_time);
}

// Функция для вывода  массива в заданном диапазоне
void printArrayInRange(int *array, int start, int end)
{
    clock_t start_time = clock();
    if (start < 0 || start > end)
    {
        printf("Некорректный диапазон.\n");
        return;
    }

    for (int i = start; i <= end; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    logExecutionTime("printArrayInRange", start_time);
}

// Функция для сохранения массива в двоичный файл
void saveArrayToBinaryFile(int *array, int size, const char *filename)
{
    clock_t start_time = clock();
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Ошибка открытия файла для записи.\n");
        exit(1);
    }
    fwrite(array, sizeof(int), size, file);
    fclose(file);
    logExecutionTime("saveArrayToBinaryFile", start_time);
}


// Функция для считывания массива из двоичного файла и вывода в консоль
void readArrayFromBinaryFile(int **array, int *size, const char *filename)
{
    clock_t start_time = clock();
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Ошибка открытия файла для чтения.\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file) / sizeof(int);
    fseek(file, 0, SEEK_SET);

    *array = (int *)malloc((*size) * sizeof(int));
    if (*array == NULL)
    {
        printf("Ошибка выделения памяти для массива.\n");
        exit(1);
    }

    fread(*array, sizeof(int), *size, file);
    fclose(file);

    logExecutionTime("readArrayFromBinaryFile", start_time);
}


int main()
{
    int size;
    printf("Введите размер массива: ");
    scanf("%d", &size);

    int *array = createArray(size);
    fillArrayWithIndices(array, size);

    int start, end;
    printf("Введите начальный индекс диапазона: ");
    scanf("%d", &start);
    printf("Введите конечный индекс диапазона: ");
    scanf("%d", &end);

    printf("Содержимое массива в заданном диапазоне: ");
    printArrayInRange(array, start, end);

    saveArrayToBinaryFile(array, size, "array.bin");
    printf("Массив сохранен в файле 'array.bin'.\n");

    int *loadedArray;
    int loadedSize;

    readArrayFromBinaryFile(&loadedArray, &loadedSize, "array.bin");
    printf("Содержимое загруженного массива: ");
    printArrayInRange(loadedArray, 0, loadedSize - 1);

    free(array);
    free(loadedArray);

    return 0;
}