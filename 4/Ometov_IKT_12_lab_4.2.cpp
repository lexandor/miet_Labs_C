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

int findSumOfMatrix(int* X){
    int sum = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8-i; j++){
            sum += X[(i * 8) + j];
        }
    }

    return sum;
}

int main(){

    system("cls");

    time_t t;
    srand(time(&t));

    
    // Инициализация переменных
    const int SIZE = 64;
    int A[SIZE] = {};

    // Вызов функций
    setRandom(A, SIZE);
    
    printMatrix(A, 8, SIZE);
    int sumOfMatrix = findSumOfMatrix(A);
    cout << "Sum of elements: " << sumOfMatrix << endl;

    return 0;
}