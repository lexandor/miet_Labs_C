
// TASK #2
// Дана целочисленная матрица 8x8. 
// Найти сумму элементов в заштрихованной области.
// Сформировать одномерный массив, содержащий средние арифметические значения строк.

#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

int main(){

    time_t t;
    srand(time(&t));

    // Задаем размер массива
    int N = 64;

    // Инициализация переменных
    int X[N] = {};          // матрица
    float A[8] = {};        // массив средних арифметических
    int sum = 0;            // сумма
    float sumOfString = 0;  // сумма строки
    float a = 0;            // средне арифметическое одной строки


    for (int i = 0; i < N; i++){ 
        X[i] = rand() % 200 - 100;   // Наполняем массив случайными значениями [-100 ; 100]

        // Выводим матрицу
        cout << setw(4) << X[i];

        if ((i+1) % 8){          
            cout << "\t";
        } else {
            cout << "\n";
        }
        
    }

    cout << "\n\n";
    cout << "AREA OF ITERATION:\n";
    cout << "===============================\n";

    for (int i = 0; i < 8; i++){
        sumOfString = 0;
        for(int j = 0; j < 8-i; j++){
        
            sumOfString += X[(i * 8) + j]; // счиатет сумму строки
            sum += sumOfString;            // cчитает общую сумму

            // выводим область по которой счиатем
            cout << setw(4) << X[(i * 8) + j]; // распечатывает область
            
            if ((i+1) % 8){          
                cout << "\t";
            } else {
                cout << "\n";
            }
            
        }
        cout << "\n";
        a = sumOfString / (8-i);
        A[i] = a;
    }

    // Распечатка результата
    cout << "\n";
    cout << "Sum of area elements: " << sum << "\n" << endl;
    for (int i = 0; i < 8; i++){
        cout << "Arithmetic sum of [" << i+1 << "] string: " << A[i] << endl;
    }

    system ("\npause");

    return 0;

}


 
