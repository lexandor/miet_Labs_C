#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

void setRandom(int X[], int N){
    for (int i = 0; i < N; i++){ 
        X[i] = rand() % 20 - 10;   // Наполняем массив случайными значениями [-10 ; 10]
        cout << X[i] << "\t";        // Выводим массив
    }
    cout << "\n";
}

int findPosOfLastPositive(int X[], int N){
    // Возвращает позицию последнего положительного числа
    int posOfLastPositive = -1;
    for (int i = 0; i < N; i++){
        if (X[i] >= 0){
            posOfLastPositive = i;
        }
    }
    return posOfLastPositive;
}

int findMin(int X[], int limit){
    // Возвращает значение минимального элемента
    int min = 3000;
    for (int i = 0; i < limit; i++){
        if (X[i] < min){
            min = X[i];
        }
    }
    return min;
}

void validPrint(int pos, int value){
    cout << "\n";
    if (pos == -1){
        cout << "Positive numbers: NOT EXIST!" << endl;
    } else if (pos == 0){
        cout << "Index of last positive number in array: " << pos << endl;
        cout << "Min value in frist part of array: NOT EXIST!" << endl;
    } else {
        cout << "Index of last positive number in array: " << pos << endl;
        cout << "Min value in frist part of array: " << value << endl;
    }
    
    

}

int main(){

    // TASK #1
    // Создать функцию для поиска положения (индекса) последнего положительного элемента произвольного массива целых чисел. 
    // Тестовая программа:
    //      1.	Создать и инициализировать 2 массива A[N1], B[N2]
    //      2.	Найти положение положительного элемента массива. Полученный индекс разделяет массив на 2 части.
    //      3.	Определить минимальный элемент в первой  части массив
    //      4.	Пункты 2 и 3 выполнить для массивов A и B

    time_t t;
    srand(time(&t));

    // Задаем размер массива
    int N1 = 0;
    cout << "Enter Size of First Array: ";
    cin >> N1;
    
    int N2 = 0;
    cout << "Enter Size of Second Array: ";
    cin >> N2;

    // Инициализация переменных
    int A[N1] = {};
    int B[N2] = {};
    int posForA = -1;
    int posForB = -1;
    int minOfA = 404;
    int minOfB = 404;
    
    // Вызов функций
    setRandom(A, N1);
    setRandom(B, N2);
    
    posForA = findPosOfLastPositive(A,N1);
    posForB = findPosOfLastPositive(B,N2);
    
    minOfA = findMin(A, posForA);
    minOfB = findMin(B, posForB);
        

    // Распечатка результата
    cout << "\n";
    
    validPrint(posForA, minOfA);
    validPrint(posForB, minOfB);

    system("pause");

    return 0;

}