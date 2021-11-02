#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h> // для файлов

using namespace std;

struct plane{
    char* company;
    char* surname;
    char* name;
    int   race;
    int   price;
};

void bubble_sort_arr(plane* DataBase, int size, bool up = false){
    // false - по убыванию | true - по возрастанию

    plane tmp;
    int cond;

    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){

            cond = strcmp(DataBase[j].surname, DataBase[j + 1].surname);

            if (!up && cond < 0) {
                tmp = DataBase[j];
                DataBase[j] = DataBase[j + 1];
                DataBase[j + 1] = tmp;
            }
            if (up && cond > 0) {
                tmp = DataBase[j];
                DataBase[j] = DataBase[j + 1];
                DataBase[j + 1] = tmp;
            }
        }
    }
}

void dispInterface(){
    cout << "\n";
    cout << "1 -- Add passenger to DataBase" << endl;
    cout << "2 -- Disp plane info" << endl;
    cout << "3 -- Find planes of company" << endl;
    cout << "4 -- Find passengers list" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(20) << "Surname";
        cout << " |" << setw(15) << "Name";
        cout << " |" << setw(20) << "Company";
        cout << " |" << setw(15) << "Race";
        cout << " |" << setw(15) << "Price";
        cout << " |" << endl;
}

void addPassenger(plane* DataBase, int* countOfPlanes){
    // Добавляет информацию о новом пассажире в базу банных.

    char buff[15] = {};
    plane* p_DataBase = DataBase + *countOfPlanes;

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter plane info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff); // костыль :-)
    cout << "Enter name: ";      gets(buff); p_DataBase->name    = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->name ,buff);
    cout << "Enter surname: ";   gets(buff); p_DataBase->surname = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->surname ,buff);
    cout << "Enter company: ";   gets(buff); p_DataBase->company = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->company ,buff);
    cout << "Enter race: ";      cin >> p_DataBase->race;
    cout << "Enter price: ";     cin >> p_DataBase->price;

    (*countOfPlanes)++;
    system("cls");
}

void printPlanes(plane* DataBase, int* countOfPlanes){
    // Распечатывает таблицу базы данных
        cout << "\nCount of planes: " << *countOfPlanes << endl;
        printHeader();
        cout << "------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPlanes; i++){
        cout << "|" << setw(20) << DataBase[i].surname;
        cout << " |" << setw(15) << DataBase[i].name;
        cout << " |" << setw(20) << DataBase[i].company;
        cout << " |" << setw(15) << DataBase[i].race;
        cout << " |" << setw(15) << DataBase[i].price;
        cout << " |" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
    }
}

void findPlaneByCompany(plane* DataBase, int* countOfPlanes){
    // Функция находит все рейсы заданной компании, результат вывести на экран
    // На вход принимает название компании

    char buff[20] = {};
    int cond;

    cout << "\n\n";
    gets(buff);
    cout << "Enter company name: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);

    printHeader();
    cout << "------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPlanes; i++){
        cond = strcmp(DataBase[i].company, name);

        if (cond == 0){
            cout << "|"  << setw(15) << DataBase[i].name;
            cout << " |" << setw(20) << DataBase[i].surname;
            cout << " |" << setw(20) << DataBase[i].company;
            cout << " |" << setw(15) << DataBase[i].race;
            cout << " |" << setw(15) << DataBase[i].price;
            cout << " |" << endl;
            cout << "------------------------------------------------------------------------------------------------" << endl;
        }
        
    }
    
}

void findPassengerByRace(plane* DataBase, int* countOfPlanes){
    
    // Ввод с консоли
    int race;
    cout << "\n\n";
    cout << "Enter race number: "; cin >> race;
    

    // Подсчитываем кол-во самолётов определенного издательства
    int countOfRaces = 0;
    for (int i = 0; i < *countOfPlanes; i++){
        if (DataBase[i].race == race) {
            countOfRaces++;
        }
    }
    
    plane* Races = (plane*) malloc (countOfRaces*sizeof(plane)); // Выделяем новый массив для рейсов.

    // Заполнение нового массива
    countOfRaces = 0;
    for (int i = 0; i < *countOfPlanes; i++){
        if (DataBase[i].race == race) {
            Races[countOfRaces] = DataBase[i];
            countOfRaces++;
        }
    }

    // TODO: Добавить сортировку по имени(прокидывать в функцию b_sort аргументы по которым мы сортируем)
    bubble_sort_arr(Races, countOfRaces, true); // Сортировка нового массива

    printPlanes(Races, &countOfRaces);
    free(Races);
}

int main(){
    bool DEBUG = false;

    system("cls");
    setlocale(LC_ALL, "Russian");


    // основная часть
    // ----------------------------
    int code;
    plane Planes[20];       // Массив с книгами
    int countOfPlanes = 0;  // Счётчик книг в базе

    while(true){
        dispInterface();
        cout << "Enter code: "; cin >> code;
        switch (code)
        {
        case 1:
            addPassenger(Planes, &countOfPlanes);
            break;
        case 2:
            printPlanes(Planes, &countOfPlanes);
            break;
        case 3:
            findPlaneByCompany(Planes, &countOfPlanes);
            break;
        case 4:
            findPassengerByRace(Planes, &countOfPlanes);
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