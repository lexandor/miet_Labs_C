#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctime>



using namespace std;

struct passport{
    char* name;
    char* surname;
    char* fathername;
    char* adress;
};


// =============================
// Работа с интерфейсом
// =============================

void dispInterface(){
    // Отрисовывает интерфейс

    cout << "\n";
    cout << "1 -- Add passport to DataBase" << endl;
    cout << "2 -- Disp DataBase" << endl;
    cout << "3 -- Find passport by letter" << endl;
    cout << "4 -- Find passport by name" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    // Распечатывает шапку таблицы

    cout << "---------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(20) << "Name";
        cout << " |" << setw(20) << "Surname";
        cout << " |" << setw(20) << "F.Name";
        cout << " |" << setw(30) << "Adress";
        cout << " |" << endl;
}

// =============================
// Основные функции
// =============================

void addPassport(passport* DataBase, int* countOfPassports){
    // Добавляет информацию о новой книге в базу банных.


    char buff[20] = {};

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter passport info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff); // костыль :-)
    cout << "Enter preson name: ";        gets(buff); DataBase[*countOfPassports].name       = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfPassports].name ,buff);
    cout << "Enter preson surname: ";     gets(buff); DataBase[*countOfPassports].surname    = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfPassports].surname ,buff);
    cout << "Enter preson father name: "; gets(buff); DataBase[*countOfPassports].fathername = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfPassports].fathername ,buff);
    cout << "Enter adress: ";             gets(buff); DataBase[*countOfPassports].adress     = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfPassports].adress ,buff);

    (*countOfPassports)++;
    system("pause");
    system("cls");
}


void printPassports(passport* DataBase, int* countOfPassports){
    // Распечатывает таблицу базы данных


        cout << "\nCount of passports: " << *countOfPassports << endl;
        printHeader();
        cout << "---------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPassports; i++){
        cout << "|"  << setw(20) << DataBase[i].name;
        cout << " |" << setw(20) << DataBase[i].surname;
        cout << " |" << setw(20) << DataBase[i].fathername;
        cout << " |" << setw(30) << DataBase[i].adress;
        cout << " |" << endl;
        cout << "---------------------------------------------------------------------------------------------------" << endl;
    }
}


void findAuthorByLetter(passport* DataBase, int* countOfPassports){
    // Функция выводит паспорта, в которых
    // первая буква фамилии совпадает с введённой

    // Ввод с консоли
    char letter;
    cout << "\n\n";
    cout << "Enter first letter of surname: "; cin >> letter;


    // Создаем массив для паспартов удовлетворяющих условию фильтрации
    passport* Persons = (passport*) malloc (sizeof(passport)); // Выделяем новый массив для паспартов.
    int countOfPersons = 0;
    for (int i = 0; i < *countOfPassports; i++){
        if (DataBase[i].surname[0] == letter) {
            Persons[countOfPersons] = DataBase[i];
            countOfPersons++;
            Persons = (passport*) realloc (Persons, (countOfPersons+1)*sizeof(passport));
        }
    }
    
    printPassports(Persons, &countOfPersons);  // Распечатка
    free(Persons);
}


void findPassportByName(passport* DataBase, int* countOfPassports){
    // Функция выводит паспорта, в которых
    // имя совпадает с введённым

    char buff[20] = {};

    cout << "\n\n";
    gets(buff);
    cout << "Enter person name: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);

    // Создаем массив для паспартов удовлетворяющих условию фильтрации
    passport* Persons = (passport*) malloc (sizeof(passport)); // Выделяем новый массив для паспартов.
    int countOfPersons = 0;
    for (int i = 0; i < *countOfPassports; i++){
        if (!strcmp(DataBase[i].name, name)) {
            Persons[countOfPersons] = DataBase[i];
            countOfPersons++;
            Persons = (passport*) realloc (Persons, (countOfPersons+1)*sizeof(passport));
        }
    }
    
    printPassports(Persons, &countOfPersons);  // Распечатка
    free(Persons);
}



int main(){

    // Создать массив из n  паспаротов (ввод с клавиатуры)
    // Реализовать функции : 
    // -	добавить новую запись о паспорте;
    // -	распечатать информацию о паспорте в табличном виде;
    // -	сформировать дин.массив результатов для фамилий начинающихся с определенной буквы;
    // -	сформировать дин.массив результатов для имен совпадающих с введённым;


    system("cls");
    setlocale(LC_ALL, "Russian");

    // основная часть
    // ----------------------------
    int code;
    FILE* file;
    passport Passports[20];    // Массив с паспортами
    int countOfPassports = 0;  // Счётчик паспортов в базе (глобальная переменная)


    while(true){
        dispInterface();
        cout << "Enter code: "; cin >> code;
        switch (code)
        {
        case 1:
            addPassport(Passports, &countOfPassports);
            break;
        case 2:
            printPassports(Passports, &countOfPassports);
            break;
        case 3:
            findAuthorByLetter(Passports, &countOfPassports);
            break;
        case 4:
            findPassportByName(Passports, &countOfPassports);
            break;
        case 0:
            exit(0);
        default:
            cout << "Input Error, try again!" << endl;
            break;
        }
    }


    system("pause");
    return 0;
}