#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>
#include <vector>

bool** getMatrixFromFile(std::string fileName, int& matrixSize);
void deleteMatrix(bool** matrix, int matrixSize);
bool* initArray(int matrixSize);
int* dfs(bool** matrix, bool* isWalked, int matrixSize);
void printArray(int* arr, int arraySize);

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string fileName{ "input.txt" };

    int matrixSize{};
    bool** matrix{ getMatrixFromFile(fileName, matrixSize) };
    bool* isWalked{ initArray(matrixSize) };
    int* arr{ dfs(matrix, isWalked, matrixSize) };
    printArray(arr, matrixSize);

    deleteMatrix(matrix, matrixSize);
    delete[] isWalked;
    delete[] arr;
    return EXIT_SUCCESS;
}

bool** getMatrixFromFile(std::string fileName, int& matrixSize)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        //int matrixSize{};
        file >> matrixSize;
        bool** matrix{ new bool* [matrixSize] };
        for (int raw{}; raw < matrixSize; ++raw)
        {
            bool* arr{ new bool[matrixSize] };
            for (int column{}; column < matrixSize; ++column)
            {
                file >> arr[column];
            }
            matrix[raw] = arr;
        }
        file.close();
        return matrix;
    }
    else
    {
        std::cout << "File is not found" << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Удаление матрицы из кучи
void deleteMatrix(bool** matrix, int matrixSize)
{
    for (int i{}; i < matrixSize; ++i)
    {
        delete[] matrix[i];
    }
    delete matrix;
}

// Создание массива информации о том, пройден ли узел графа
bool* initArray(int matrixSize)
{
    bool* isWalked{ new bool[matrixSize] };
    for (int i{}; i < matrixSize; ++i)
    {
        isWalked[i] = false;
    }
    return isWalked;
}

// Обход очередного узла
void dfs(bool** matrix, int index, int count, bool* isWalked, std::vector<int> &order, int matrixSize)
{
    //result[count] = index + 1;
    order.insert(order.begin() + count, index + 1);
    isWalked[index] = true;
    for (int i{}; i < matrixSize; ++i)
    {
        if (matrix[index][i])
        {
            if (!isWalked[i])
            {
                dfs(matrix, i, count + 1, isWalked, order, matrixSize);
            }
        }
    }

    for (int i{}; i < matrixSize; ++i)
    {
        if (matrix[i][index])
        {
            if (!isWalked[i])
            {
                dfs(matrix, i, count, isWalked, order, matrixSize);
            }
        }
    }
}

// Создание массива с последовательностью обхода графа
int* dfs(bool** matrix, bool* isWalked, int matrixSize)
{
    int* result{ new int[matrixSize] };
    std::vector<int> order{};

    int count{};

    for (int i{}; i < matrixSize; ++i)
    {
        if (!isWalked[i])
        {
            dfs(matrix, i, count, isWalked, order, matrixSize);
        }
    }

    for (int i{}; i < matrixSize; ++i)
    {
        result[i] = order.at(i);
    }
    return result;
}

// Вывод топологической сортировки
void printArray(int* arr, int arraySize)
{
    std::cout << "Топологический порядок вершин: ";
    for (int i{}; i < arraySize; ++i)
    {
        std::cout << arr[i] << ' ';
    }
}