#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctime>


using namespace std;

struct date{
    int   day;
    char* month;
    int   year;
};

struct supplier{
    date   date;
    int    section;
    char*  name;
    char*  firm;
    double price;
    int    count = 1;
};

// =============================
// Функции для работы с файлами
// =============================

void saveFile(FILE* file, supplier* DataBase, int* countOfSuppliers){
    // Сохраняет данные в файл

    supplier* DB_BUFFER;

    cout << "Saving..." << endl;

    file = fopen("DATA.bin", "wb");
        DB_BUFFER = DataBase;
        fwrite(DB_BUFFER, sizeof(supplier), *countOfSuppliers , file);	  
    fclose(file);    

    file = fopen("DATA.txt", "w");
        for (DB_BUFFER = DataBase; DB_BUFFER < DataBase + *countOfSuppliers; DB_BUFFER++)
        {
            fprintf (file, "%s\n", DB_BUFFER->name);
            fprintf (file, "%s\n", DB_BUFFER->firm);
            fprintf (file, "%s\n", DB_BUFFER->date.month);
        }
    fclose(file);   

    cout << "Data saved!" << endl;
    
}

void readFile(FILE* file, supplier* DataBase, int* countOfSuppliers){
    // Подгружает данные из файла, если файла не существует, создаст файл.

    supplier* DB_BUFFER;
    char  buff[80]; 

    file = fopen("DATA.bin", "rb");
        cout << "Loading data... " << endl;
        
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++){
            fread (DB_BUFFER, sizeof(supplier),1, file);
            (*countOfSuppliers)++;
        }	
        (*countOfSuppliers)--;    

    fclose(file);

    file = fopen("DATA.txt", "r");
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++)	
        { 
            fscanf (file,"%s\n", buff); DB_BUFFER->name       = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->name, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->firm       = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->firm, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->date.month = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->date.month, buff);
        }
    fclose(file);

}

// =============================
// Сортировки
// =============================

void bubble_sort_arr(supplier* DataBase, int size, bool up = false){
    // false - по убыванию | true - по возрастанию

    supplier tmp;
    int cond;

    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){

            cond = strcmp(DataBase[j].name, DataBase[j + 1].name);

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

// =============================
// Работа с интерфейсом
// =============================

void dispInterface(){
    cout << "\n";
    cout << "1 -- Add supplier to DataBase" << endl;
    cout << "2 -- Disp DataBase" << endl;
    cout << "3 -- Find supplier by section" << endl;
    cout << "4 -- Find supplier by count" << endl;
    cout << "5 -- Disp retirees list" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(20) << "Name";
        cout << " |" << setw(20) << "Price";
        cout << " |" << setw(15) << "Count";
        cout << " |" << setw(15) << "Firm";
        cout << " |" << setw(15) << "Section";
        cout << " |" << setw(20) << "Date";
        cout << " |" << endl;
}

// =============================
// Основные функции
// =============================

void addSupplier(supplier* DataBase, int* countOfSuppliers){
    // Добавляет информацию о новой книге в базу банных.


    char buff[20] = {};
    char* name;
    char* firm;
    int   sect;
    bool inBase = false;

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter supplier info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";

    // Сичтыаем название и фирму из консоли
    gets(buff); // костыль :-)
    cout << "Enter name: ";           gets(buff); name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);
    cout << "Enter supplier firm: ";  gets(buff); firm = (char*) malloc (strlen(buff) + 1); strcpy(firm ,buff);
    cout << "Enter section: ";        cin >> sect;

    // Ищем есть ли такой товар в базе, есди да, то увеличиваем кол-во
    for (int i = 0; i < (*countOfSuppliers); i++){
        cout << i << endl;
        if(!strcmp(DataBase[i].name, name) && !strcmp(DataBase[i].firm, firm) && DataBase[i].section == sect ){
            cout << "in: " << i << endl;
            DataBase[i].count = DataBase[i].count + 1;
            inBase = true;
        }
    }

    // Если товара в базе нет, то заносим товар в базу
    if (!inBase){

        DataBase[*countOfSuppliers].name = (char*) malloc (strlen(name) + 1); strcpy(DataBase[*countOfSuppliers].name, name);
        DataBase[*countOfSuppliers].firm = (char*) malloc (strlen(firm) + 1); strcpy(DataBase[*countOfSuppliers].firm, firm);
        DataBase[*countOfSuppliers].section = sect;

        cout << "Enter price: ";      cin >>  DataBase[*countOfSuppliers].price;
        cout << "Enter date->day: ";  cin >> (DataBase[*countOfSuppliers].date).day;
        gets(buff); // костыль :-)
        cout << "Enter date->mon(3 letter): ";  gets(buff); (DataBase[*countOfSuppliers].date).month = (char*) malloc (strlen(buff) + 1); strcpy((DataBase[*countOfSuppliers].date).month ,buff);
        cout << "Enter date->year: ";           cin >> (DataBase[*countOfSuppliers].date).year;

        (*countOfSuppliers)++;
    }
    
    
    system("pause");
    system("cls");
}

void printSuppliers(supplier* DataBase, int* countOfSuppliers){
    // Распечатывает таблицу базы данных


        cout << "\nCount of suppliers: " << *countOfSuppliers << endl;
        printHeader();
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfSuppliers; i++){
        cout << "|"  << setw(20) << DataBase[i].name;
        cout << " |" << setw(20) << DataBase[i].price;
        cout << " |" << setw(15) << DataBase[i].count;
        cout << " |" << setw(15) << DataBase[i].firm;
        cout << " |" << setw(15) << DataBase[i].section;
        cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
        cout << " |" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void findSupplierByCnt(supplier* DataBase, int* countOfSuppliers){
    // Функция выводит книги конкретного автора
    // на вход принимает имя и фамилию

    int cnt;

    cout << "\n\n";
    cout << "Enter count: "; cin >> cnt; 
    

    printHeader();
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfSuppliers; i++){

        if (DataBase[i].count < cnt){
            cout << "|"  << setw(20) << DataBase[i].name;
            cout << " |" << setw(20) << DataBase[i].price;
            cout << " |" << setw(15) << DataBase[i].count;
            cout << " |" << setw(15) << DataBase[i].firm;
            cout << " |" << setw(15) << DataBase[i].section;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        }
        
    }
    
}

void findSupplierBySection(supplier* DataBase, int* countOfSuppliers){

    
    // Ввод с консоли
    char buff[20] = {};
    int  section;
    cout << "\n\n";
    
    cout << "Enter section: "; cin >> section; 

    // Создаем массив для записей удовлетворяющих условию фильтрации
    supplier* Tovars = (supplier*) malloc (sizeof(supplier)); // Выделяем новый массив для авторов.
    int countOfTovars = 0;
    for (int i = 0; i < *countOfSuppliers; i++){
        if (DataBase[i].section == section) {
            Tovars[countOfTovars] = DataBase[i];
            countOfTovars++;
            Tovars = (supplier*) realloc (Tovars, (countOfTovars+1)*sizeof(supplier));
        }
    }
    
    bubble_sort_arr(Tovars, countOfTovars, true); // Сортировка нового массива
    printSuppliers(Tovars, &countOfTovars);        // Распечатка
    free(Tovars);                                  // Отчистка памяти
}

void findRetiree(supplier* DataBase, int* countOfSuppliers){

    const time_t timer = time(NULL);
    struct tm *u = localtime(&timer);
    int current_year  = u->tm_year + 1900;
    int current_month = u->tm_mon + 1;
    int current_day   = u->tm_wday + 6;

    char months[12][4] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

    cout << "Current time: " << current_day <<"."<< current_month <<"."<< current_year << endl;

    printHeader();
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfSuppliers; i++){

        // превод месяца в базе из char в int
        int m = 0;
        for (int j = 0; j < 12; j++){
            if (!strcmp(DataBase[i].date.month, months[j])){
                m = j + 1;
            }
        }

        if ( (current_year*12 + current_month) - (DataBase[i].date.year*12 + m) > 12){
            cout << "|"  << setw(20) << DataBase[i].name;
            cout << " |" << setw(20) << DataBase[i].price;
            cout << " |" << setw(15) << DataBase[i].count;
            cout << " |" << setw(15) << DataBase[i].firm;
            cout << " |" << setw(15) << DataBase[i].section;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        }
        
    }
}



int main(){
    bool DEBUG = false;
    

    // Создать массив из n  книг (ввод с клавиатуры)
    // Реализовать функции : 
    // -	добавить новую книгу;
    // -	распечатать информацию о книге в табличном виде;
    // -	найти все книги заданного автора, результат вывести на экран;
    // -	найти всех авторов заданного издательства,  результат отсортировать по алфавиту, запомнить в массиве и вывести на экран;

    // При запуске программы данные ввести с клавиатуры (первый запуск программы) или загрузить с диска (все последующие запуски)
    // -	Добавить несколько новых элементов массива данных(ввод с клавиатуры)
    // -	Все реализованные ранее функции нужно доработать в соответствии со сделанными изменениями, функции должны по-прежнему работать
    // -	Интерфейс программы дополнить функцией поиска авторов пенсионного возраста (используем понятие «текущая дата»)
    // -	При выходе из программы запомнить измененную базу на диске


    system("cls");
    setlocale(LC_ALL, "Russian");


    // основная часть
    // ----------------------------
    int code;
    FILE* file;
    supplier Suppliers[20];    // Массив с книгами
    int countOfSuppliers = 0;                           // Счётчик книг в базе (глобальная переменная)

    if ((file = fopen("DATA.bin", "rb")) != NULL){
        fclose(file);
        cout << "DataBase file already exist..." << endl;

        readFile(file, Suppliers, &countOfSuppliers);
    } else {
        fclose(file);
        cout << "DataBase file not exist.. -> creating file..." << endl;

        file = fopen("DATA.bin", "wb");fclose(file);
        file = fopen("DATA.txt", "w");fclose(file);
    }


    while(true){
        dispInterface();
        cout << "Enter code: "; cin >> code;
        switch (code)
        {
        case 1:
            addSupplier(Suppliers, &countOfSuppliers);
            break;
        case 2:
            printSuppliers(Suppliers, &countOfSuppliers);
            break;
        case 3:
            findSupplierBySection(Suppliers, &countOfSuppliers);
            break;
        case 4:
            findSupplierByCnt(Suppliers, &countOfSuppliers);
            break;
        case 5:
            findRetiree(Suppliers, &countOfSuppliers);
            break;
        case 0:
            saveFile(file, Suppliers, &countOfSuppliers);
            exit(0);
        default:
            cout << "Input Error, try again!" << endl;
            break;
        }
    }


    system("pause");
    return 0;
}