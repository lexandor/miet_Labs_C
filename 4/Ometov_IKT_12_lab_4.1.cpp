#include <iostream>
#include <iomanip>
#include <clocale>
#include <time.h>

using namespace std;

void setRandom(int* X, int N){
    cout << "\n";
    for (int* item = X; item < (X+N); item++){ 
        *item = rand() % 21 - 10;   // Наполняем массив случайными значениями [-10; 10]
        cout << *item << "\t";      // Выводим массив
    }
    cout << "\n";
}

int* findMinPos(int* X, int N){
    // Возвращает ссылку на индекс минимального элемента
    int min = INT_MAX;
    int posMin = -1;

    for(int i = 0; i < N; i++){
        if (X[i] < min) {
            min = X[i];
            posMin = i;
        }
    }

    return &X[posMin]; // или  return (X + posMin)
}

int findSum(int* X, int* pos){
    // Возвращает сумму элеметов первой половины
    int sum = 0;

    for (int* i = X; i < pos; i++){
        sum = sum + *i;
    }

    return sum;
}

int main(){

    system("cls");
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

    // Вызов функций
    setRandom(A, N1);
    setRandom(B, N2);

    int* posA = findMinPos(A, N1);
    int* posB = findMinPos(B, N2);

    int sumA = findSum(A, posA);
    int sumB = findSum(B, posB);

    // Распечатка результатов
    cout << "\n";
    cout << "min of A: " << *posA << endl;
    cout << "sum A: " << sumA << endl;

    cout << "\n";
    cout << "min of B: " << *posB << endl;
    cout << "sum B: " << sumB << endl;

    cout << "\n";
    if (sumA > sumB){
        cout << "sum A > sum B" << endl;
    } else if (sumB > sumA){
        cout << "sum B > sum A" << endl;
    } else if (sumA == sumB){
        cout << "sum A = sum B" << endl;
    } else {
        cout << "Error!";
    }

    system("pause");

    return 0;
}