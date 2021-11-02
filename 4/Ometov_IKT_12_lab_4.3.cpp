#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

void setRandom(int* X, int N){
    // Наполняем массив случайными значениями [-10; 10]
    for (int* item = X; item < (X+N); item++){ 
        *item = rand() % 21 - 10;   // Наполняем массив случайными значениями [-10 ; 10]        
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

double getMiddleVal(int* X, int N, int i){
    
    double sumOfRow = 0;

    for (int j = 0; j < N; j++){
        sumOfRow = sumOfRow + (double) X[(i*N) + j];
    }
    sumOfRow = sumOfRow / N;

    return sumOfRow;
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
    double MV[N] = {};

    setRandom(A, SIZE);
    printMatrix(A, N, SIZE);
    
    for (int i = 0; i < N; i++){
        MV[i] = getMiddleVal(A, N, i);
        cout << "Sum of str[" << i+1 << "] : " << MV[i] << endl;
    }


    system("pause");
    return 0;
}