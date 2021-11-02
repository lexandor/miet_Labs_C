#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

using namespace std;

struct date {
    int day;
    char* month;
    int year;
};

struct fio {
    char* name;
    char* surname;
};

struct plane {
    char* company;
    fio fio;
    date  date;
    int   race;
    int   price;
};

// =============================
// Функции для работы с файлами
// =============================

void saveFile(FILE * file, plane * DataBase, int* countOfPlanes) {
    // Сохраняет данные в файл

    plane* DB_BUFFER;

    cout << "Saving..." << endl;

    file = fopen("DATA.bin", "wb");
    DB_BUFFER = DataBase;
    fwrite(DB_BUFFER, sizeof(plane), *countOfPlanes, file);
    fclose(file);

    file = fopen("DATA.txt", "w");
    for (DB_BUFFER = DataBase; DB_BUFFER < DataBase + *countOfPlanes; DB_BUFFER++)
    {
        fprintf(file, "%s\n", DB_BUFFER->fio.name);
        fprintf(file, "%s\n", DB_BUFFER->fio.surname);
        fprintf(file, "%s\n", DB_BUFFER->company);
        fprintf(file, "%s\n", DB_BUFFER->date.month);
    }
    fclose(file);

    
    cout <<" ___________$$$$$$$$$ \n";
    cout <<" _______$$$$$$$$$$$$$$$$$ \n";
    cout <<" _____$$$$$$$_______$$$$$$$ \n";
    cout <<" ___$$$$$_$$$$_____$$$$__$$$$ \n";
    cout <<" __$$$$____$$$$___$$$$____$$$$ \n";
    cout <<" _$$$$______$$$$__$$$______$$$$ \n";
    cout <<" _$$$$$______$$$$$$$______$$$$$$ \n";
    cout <<" $$$_$$$_______$$$$______$$$_$$$ \n";
    cout <<" $$$__$$$_______$$______$$$__$$$ \n";
    cout <<" $$$___$$$_____$$$$____$$$___$$$ \n";
    cout <<" $$$___$$$$___$$$$$$__$$$$___$$$ \n";
    cout <<" _$$$___$$$$_$$$$$$$$_$$$___$$$$ \n";
    cout <<" _$$$$___$$$$$$$_$$$$$$$___$$$$ \n";
    cout <<" __$$$$___$$$$$___$$$$$___$$$$ \n";
    cout <<" ___$$$$$__$$$_____$$$___$$$$ \n";
    cout <<" _____$$$$_$$_______$$_$$$$ \n";
    cout <<" _______$$$$$$$$$$$$$$$$$ \n";
    cout <<" ___________$$$$$$$$$ \n";

    
    cout << "Data saved!" << endl;

}

void readFile(FILE* file, plane* DataBase, int* countOfPlanes) {
    // Подгружает данные из файла, если файла не существует, создаст файл.

    plane* DB_BUFFER;
    char  buff[80];

    file = fopen("DATA.bin", "rb");
    cout << "Loading data... " << endl;

    for (DB_BUFFER = DataBase; !feof(file); DB_BUFFER++) {
        fread(DB_BUFFER, sizeof(plane), 1, file);
        (*countOfPlanes)++;
    }
    (*countOfPlanes)--;

    fclose(file);

    file = fopen("DATA.txt", "r");
    for (DB_BUFFER = DataBase; !feof(file); DB_BUFFER++)
    {
        fscanf(file, "%s\n", buff); DB_BUFFER->fio.name    = (char*)malloc(strlen(buff) + 1); strcpy(DB_BUFFER->fio.name, buff);
        fscanf(file, "%s\n", buff); DB_BUFFER->fio.surname = (char*)malloc(strlen(buff) + 1); strcpy(DB_BUFFER->fio.surname, buff);
        fscanf(file, "%s\n", buff); DB_BUFFER->company     = (char*)malloc(strlen(buff) + 1); strcpy(DB_BUFFER->company, buff);
        fscanf(file, "%s\n", buff); DB_BUFFER->date.month  = (char*)malloc(strlen(buff) + 1); strcpy(DB_BUFFER->date.month, buff);
    }
    fclose(file);

}


void bubble_sort_arr(plane* DataBase, int size, bool up = false) {
    // false - по убыванию | true - по возрастанию

    plane tmp;
    int cond;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {

            cond = strcmp(DataBase[j].fio.surname, DataBase[j + 1].fio.surname);

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

void dispInterface() {
    cout << "\n";
    cout << "1 -- Add passenger to DataBase" << endl;
    cout << "2 -- Disp plane info" << endl;
    cout << "3 -- Find planes of company" << endl;
    cout << "4 -- Find passengers list" << endl;
    cout << "5 -- Find passengers by date" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader() {
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(20) << "F.I.O.";
    cout << " |" << setw(20) << "Company";
    cout << " |" << setw(15) << "Race";
    cout << " |" << setw(15) << "Price";
    cout << " |" << setw(20) << "Date";
    cout << " |" << endl;
}

void addPassenger(plane* DataBase, int* countOfPlanes) {
    // Добавляет информацию о новом пассажире в базу банных.

    char buff[20] = {};

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter plane info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff);
    cout << "Enter name: ";      gets(buff); DataBase[*countOfPlanes].fio.name    = (char*)malloc(strlen(buff) + 1); strcpy(DataBase[*countOfPlanes].fio.name, buff);
    cout << "Enter surname: ";   gets(buff); DataBase[*countOfPlanes].fio.surname = (char*)malloc(strlen(buff) + 1); strcpy(DataBase[*countOfPlanes].fio.surname, buff);
    cout << "Enter plane date: ";  cin >> (DataBase[*countOfPlanes].date).day;
    gets(buff); // костыль :-)
    cout << "Enter plane month(3 letter): "; gets(buff); (DataBase[*countOfPlanes].date).month = (char*)malloc(strlen(buff) + 1); strcpy((DataBase[*countOfPlanes].date).month, buff);
    cout << "Enter plane year: ";            cin >> (DataBase[*countOfPlanes].date).year;
    gets(buff);
    cout << "Enter company: ";   gets(buff); DataBase[*countOfPlanes].company = (char*)malloc(strlen(buff) + 1); strcpy(DataBase[*countOfPlanes].company, buff);
    cout << "Enter race: ";      cin >> DataBase[*countOfPlanes].race;
    cout << "Enter price: ";     cin >> DataBase[*countOfPlanes].price;

    (*countOfPlanes)++;
    system("cls");
}

void printPlanes(plane* DataBase, int* countOfPlanes) {
    // Распечатывает таблицу базы данных
    cout << "\nCount of planes: " << *countOfPlanes << endl;
    printHeader(); 
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPlanes; i++) {
        cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
        cout << " |" << setw(20) << DataBase[i].company;
        cout << " |" << setw(15) << DataBase[i].race;
        cout << " |" << setw(15) << DataBase[i].price;
        cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
        cout << " |" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;
    }
}

void findPlaneByCompany(plane* DataBase, int* countOfPlanes) {
    // Функция находит все рейсы заданной компании, результат вывести на экран
    // На вход принимает название компании

    char buff[20] = {};
    int cond;

    cout << "\n\n";
    gets(buff);
    cout << "Enter company name: "; gets(buff);
    char* name = (char*)malloc(strlen(buff) + 1); strcpy(name, buff);

    printHeader();
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPlanes; i++) {
        cond = strcmp(DataBase[i].company, name);

        if (cond == 0) {
            cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
            cout << " |" << setw(20) << DataBase[i].company;
            cout << " |" << setw(15) << DataBase[i].race;
            cout << " |" << setw(15) << DataBase[i].price;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
        }

    }

}

void findPassengerByRace(plane* DataBase, int* countOfPlanes) {

    // Ввод с консоли
    int race;
    cout << "\n\n";
    cout << "Enter race number: "; cin >> race;


    // Подсчитываем кол-во самолётов определенного издательства
    int countOfRaces = 0;
    for (int i = 0; i < *countOfPlanes; i++) {
        if (DataBase[i].race == race) {
            countOfRaces++;
        }
    }

    plane* Races = (plane*)malloc(countOfRaces * sizeof(plane)); // Выделяем новый массив для рейсов.

    // Заполнение нового массива
    countOfRaces = 0;
    for (int i = 0; i < *countOfPlanes; i++) {
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

void findPassengerByDate(plane* DataBase, int* countOfPlanes) {

    int s_day, s_year, e_day, e_year;
    bool cond;
    char s_month[3];
    char e_month[3];
    char buff[20];

    cout << "Enter start plane date: ";  cin >> s_day;
    gets(buff); // костыль :-)
    cout << "Enter start plane month(3 letter): "; gets(buff); strcpy(s_month, buff);
    cout << "Enter start plane year: "; cin >> s_year;
    cout << "  <-==)~  " << endl;
    cout << "Enter end plane date: ";  cin >> e_day;
    gets(buff); // костыль :-)
    cout << "Enter end plane month(3 letter): "; gets(buff); strcpy(e_month, buff);
    cout << "Enter end plane year: "; cin >> e_year;

    printHeader();
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfPlanes; i++) {
        
        if( s_year < DataBase[i].date.year && DataBase[i].date.year < e_year){
            cond = true;
        } else {
            if ( s_year == DataBase[i].date.year || e_year == DataBase[i].date.year){
                if( s_day < DataBase[i].date.day && e_day < DataBase[i].date.day){
                    cond = true;
                } else {
                    cond = false;
                }
            }
        }

        if (cond) {
            cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
            cout << " |" << setw(20) << DataBase[i].company;
            cout << " |" << setw(15) << DataBase[i].race;
            cout << " |" << setw(15) << DataBase[i].price;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
        }

        cond = false;

    }

}

int main() {
    bool DEBUG = false;

    system("cls");
    setlocale(LC_ALL, "Russian");


    // основная часть
    // ----------------------------
    int code;
    FILE* file;
    plane Planes[20];       // Массив с самолетов
    int countOfPlanes = 0;  // Счётчик самолетов в базе

    if ((file = fopen("DATA.bin", "rb")) != NULL) {
        fclose(file);
        cout << "DataBase file already exist..." << endl;

        readFile(file, Planes, &countOfPlanes);
    }
    else {
        fclose(file);
        cout << "DataBase file not exist.. -> creating file..." << endl;

        file = fopen("DATA.bin", "wb"); fclose(file);
        file = fopen("DATA.txt", "w"); fclose(file);
    }

    while (true) {
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
        case 5:
            findPassengerByDate(Planes, &countOfPlanes);
            break;
        case 0:
            saveFile(file, Planes, &countOfPlanes);
            system("pause");
            exit(0);
        default:
            cout << "Input Error, try again!" << endl;
            break;
        }
    }


    system("pause");
    return 0;
}