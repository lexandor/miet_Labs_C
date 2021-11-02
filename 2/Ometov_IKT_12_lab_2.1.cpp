
// В массиве Х(N) найти S1 – сумму положительных элементов массива в 
// первой половине массива и S2 – сумму отрицательных элементов массива во 
// второй половине массива.

#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

int main(){

    time_t t;
    srand(time(&t));

    // Задаем размер массива
    int N = 0;
    cout << "Enter Size of Array: ";
    cin >> N;

    // Инициализация переменных
    int X[N] = {};
    int sumOfPositive = 0;
    int sumOfNegative = 0;


    for (int i = 0; i < N; i++){ 
        X[i] = rand() % 200 - 100;   // Наполняем массив случайными значениями [-100 ; 100]
        cout << X[i] << "\t";  // Выводим массив
    }

    for (int i = 0; i < N; i++){
        if (i < N/2 && X[i] > 0) {  // Пополняем сумму положительных в первой половине массива
            sumOfPositive += X[i];
        }
        if (i > N/2 && X[i] < 0) {  // Пополняем сумму отрицательных во второй половине массива
            sumOfNegative += X[i];
        }
    }

    // Распечатка результата
    cout << "\n";
    cout << "Sum of positive: " << sumOfPositive << endl;
    cout << "Sum of negative: " << sumOfNegative << endl;

    system ("pause");

    return 0;

}


 
