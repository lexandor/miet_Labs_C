#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

void setRandom(int X[], int N){
    // Наполняем массив случайными значениями [-10; 10]
    for (int i = 0; i < N; i++){ 
        X[i] = rand() % 20 - 10;   
    }
}

void printMatrix(int X[], int N, int SIZE){
    // Выводим массив
    cout << "\n\n";
    for (int i = 0; i < SIZE; i++){ 
        cout << setw(4) << X[i];

        if ((i+1) % N){          
            cout << "\t";
        } else {
            cout << "\n";
        }
    }
    cout << "\n\n";
}

int findMinPosElemOfColum(int X[], int N, int SIZE, int col){

    int min = INT_MAX; // инициализация минимума
    int index = 0;     // точка отсчёта

    // В случае если кол-во сторк НЕЧЁТНО, функция будет захватывать большую область
    if (SIZE % 2 == 0){
        index =  SIZE / 2;
    } else {
        index =  (SIZE / 2) - (SIZE / 2 / N); 
        // index =  (SIZE / 2) + (SIZE / 2 / N) + 1; // Если понадобиться меньшая область
    }
    

    for (int i = index + col - 1; i < SIZE; i+=N){
        if (X[i] < min && X[i] >= 0){
            min = X[i];
        }
    }
    // Обработка случая если минимальное позитивное число не найдено
    if (min == INT_MAX){
        min = -1;
    }

    return min;
}

int main(){

    // TASK #2
    // Дана целочисленная матрица NxM, содержащая как положительные, так и отрицательные элементы.
    // Создать функцию, которая возвращает  минимумы положительных элементов в заданном столбце  заштрихованной области.
    // Отразить на экране результаты для всех столбцов.

    system("cls");

    time_t t;
    srand(time(&t));

    // Задаем размеры матрицы
    int N,M;
    cout << "\n\n";
    cout << "Enter N: ";
    cin >> N;
    cout << "Enter M: ";
    cin >> M;

    
    // Инициализация переменных
    int SIZE = N * M;
    int A[SIZE] = {};

    // Вызов функций
    setRandom(A, SIZE);
    printMatrix(A, N, SIZE);

    for (int i = 1; i <= N; i++){

        int m = findMinPosElemOfColum(A, N, SIZE, i);

        if (m == -1){
            cout << "[" << i << "] " << "Positive number in colum not found!" << endl;
        } else {
            cout << "[" << i << "] " << "Min positine number: " << m << endl;
        }
    }
    
    cout << "\n";
    system("pause");

    return 0;
}