#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>
#include <ctype.h>
#include <string.h>

using namespace std;

void setRandom(float* X, int N, int M){
    for (int i = 0; i < N*M; i++){ 
        X[i] = rand() % 20 - 10;     // Наполняем массив случайными значениями [-10 ; 10]
    }
}

void printMatrix(float* X, int N, int M){
    // Выводим матрицу
    int SIZE = N * M;
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

float sumOfArea(float* X, int N, int M){
    float sum = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++){
            if ((i <= N/2 && j <= M/2) || (i >= N/2 && j >= M/2)){
                sum = sum + X[(i * N) + j];
            }
        }
    }

    return sum;
}

int main(){

    // Создать динамическую вещественную матрицу NxM (N и M ввести с клавиатуры).
    // Создать функцию для вычисления суммы строк заштрихованной области.


    system("cls");

    int N,M;

    cout << "Enter N: ";
    cin >> N;
    cout << "Enter M: ";
    cin >> M;

    float* X = (float*) calloc (N*M, sizeof(float));
    setRandom(X, N, M);
    printMatrix(X, N, M);
    float sum = sumOfArea(X, N, M);

    cout << "Sum of Area: " << sum << endl;

    system("pause");
    return 0;
}