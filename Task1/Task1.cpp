#include <iostream>
#include <fstream>
#include <cstdlib>
#include <clocale>

bool** getMatrixFromFile(std::string fileName, int& matrixSize);
void deleteMatrix(bool** matrix, int matrixSize);
void printOrgraphInfo(bool** matrix, int matrixSize);

int main()
{
    setlocale(LC_ALL, "Russian");
    std::string fileName{ "input.txt" };

    int matrixSize{};
    bool** matrix{ getMatrixFromFile(fileName, matrixSize) };
    printOrgraphInfo(matrix, matrixSize);

    deleteMatrix(matrix, matrixSize);
    return EXIT_SUCCESS;
}

// Создание матрицы из информации, записаной в файле
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

// Вывод в консоль информации
void printOrgraphInfo(bool** matrix, int matrixSize)
{
    std::cout << "Текстовый вид орграфа:\n";
    for (int raw{}; raw < matrixSize; ++raw)
    {
        std::cout << raw + 1 << ": ";
        bool isNotEmpty{};
        for (int column{}; column < matrixSize; ++column)
        {
            if (matrix[raw][column])
            {
                isNotEmpty = true;
                std::cout << column + 1 << ' ';
            }
        }
        if (!isNotEmpty)
        {
            std::cout << "нет";
        }
        std::cout << '\n';
    }
}