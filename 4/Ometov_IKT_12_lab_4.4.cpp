#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

struct extr
{
    int min;
    int max;
};


void setRandom(int* X, int N){
    // Наполняем массив случайными значениями [-10; 10]
    for (int* item = X; item < (X+N); item++){ 
        *item = rand() % 201 - 100;   // Наполняем массив случайными значениями [-10 ; 10]        
    }
}

void printMatrix(int* X, int N, int SIZE){
    // Выводим массив
    cout << "\n\n";
    int* item = X;                          // Указатель на начало массива
    for (int i = 0; i < SIZE; i++, item++){ // одновременный сдвиг итерации и положения указателя
        cout << setw(4) << *item;

        if ((i+1) % N){          
            cout << "\t";
        } else {
            cout << "\n";
        }
    }
    cout << "\n\n";
}

void printArea(int* X, int N){
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N-i; j++){

            cout << setw(4) << *(X + ((i * N) + j)); // распечатывает область
            
            if ((i+1) % N){          
                cout << "\t";
            } else {
                cout << "\n";
            }
        }
        cout << "\n";
    }
    cout << "\n\n";
}

extr findExtrInArea(int* X, int N){
    int max = INT_MIN;
    int min = INT_MAX;
    extr ex;

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N-i; j++){

            if (*(X + ((i * N) + j)) < min){
                min = *(X + ((i * N) + j));  // Поиск минимумуа
            }
            if (*(X + ((i * N) + j)) > max){
                max = *(X + ((i * N) + j));  // Поиск максимума
            }
        }
    }

    ex.min = min;
    ex.max = max;

    return ex;

}


int main(){

    system("cls");

    time_t t;
    srand(time(&t));

    // Задаем размер матрицы
    int N = 0;
    cout << "Enter N: ";
    cin >> N;

    const int SIZE = N * N;
    int A[SIZE] = {};

    setRandom(A, SIZE);
    printMatrix(A, N, SIZE);
    printArea(A, N);
    extr ex = findExtrInArea(A, N);

    cout << "Maximum: " << ex.max << endl;
    cout << "Minimum: " << ex.min << endl;


    system("pause");
    return 0;
}