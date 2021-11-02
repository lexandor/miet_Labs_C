#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h> // для файлов

using namespace std;

struct book{
        char* surname;
        char* name;
        char* title;
        char* publish;
        int   year;
    };

void bubble_sort_arr(book* DataBase, int size, bool up = false){
    // false - по убыванию | true - по возрастанию

    book tmp;
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
    cout << "1 -- Add book to DataBase" << endl;
    cout << "2 -- Disp books info" << endl;
    cout << "3 -- Find book in DataBase" << endl;
    cout << "4 -- Disp author list" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(15) << "Name";
        cout << " |" << setw(20) << "Surname";
        cout << " |" << setw(20) << "Title";
        cout << " |" << setw(15) << "Publish";
        cout << " |" << setw(15) << "Year";
        cout << " |" << endl;
}

void addBook(book* DataBase, int* countOfBooks){
    // Добавляет информацию о новой книге в базу банных.

    char buff[15] = {};
    book* p_DataBase = DataBase + *countOfBooks;

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter book info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff); // костыль :-)
    cout << "Enter author name: ";      gets(buff); p_DataBase->name    = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->name ,buff);
    cout << "Enter author surname: ";   gets(buff); p_DataBase->surname = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->surname ,buff);
    cout << "Enter book title: ";       gets(buff); p_DataBase->title   = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->title ,buff);
    cout << "Enter publishing house: "; gets(buff); p_DataBase->publish = (char*) malloc (strlen(buff) + 1); strcpy(p_DataBase->publish ,buff);
    cout << "Enter year of publish: ";  cin >> p_DataBase->year;

    (*countOfBooks)++;
    system("cls");
}

void printBooks(book* DataBase, int* countOfBooks){
    // Распечатывает таблицу базы данных
        cout << "\nCount of books: " << *countOfBooks << endl;
        printHeader();
        cout << "------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfBooks; i++){
        cout << "|" << setw(15) << DataBase[i].name;
        cout << " |" << setw(20) << DataBase[i].surname;
        cout << " |" << setw(20) << DataBase[i].title;
        cout << " |" << setw(15) << DataBase[i].publish;
        cout << " |" << setw(15) << DataBase[i].year;
        cout << " |" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
    }
}

void findBookByAuthor(book* DataBase, int* countOfBooks){
    // Функция выводит книги конкретного автора
    // на вход принимает имя и фамилию

    // TODO: Сделать поиск книг через бинарный поиск
    char buff[20] = {};
    int isN;
    int isSn;

    cout << "\n\n";
    gets(buff);
    cout << "Enter author name: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);

    cout << "Enter author surname: "; gets(buff);
    char* surname = (char*) malloc (strlen(buff) + 1); strcpy(surname ,buff);

    printHeader();
    cout << "------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfBooks; i++){
        isN  = strcmp(DataBase[i].name, name);
        isSn = strcmp(DataBase[i].surname, surname);

        if (isN == 0 and isSn == 0){
            cout << "|" << setw(15) << DataBase[i].name;
            cout << " |" << setw(20) << DataBase[i].surname;
            cout << " |" << setw(20) << DataBase[i].title;
            cout << " |" << setw(15) << DataBase[i].publish;
            cout << " |" << setw(15) << DataBase[i].year;
            cout << " |" << endl;
            cout << "------------------------------------------------------------------------------------------------" << endl;
        }
        
    }
    
}

void findAuthorByHouse(book* DataBase, int* countOfBooks){


    // FIXME: Пофиксить условия в if
    
    // Ввод с консоли
    char buff[20] = {};
    cout << "\n\n";
    gets(buff);
    cout << "Enter publish house: "; gets(buff);
    char* phName = (char*) malloc (strlen(buff) + 1); strcpy(phName ,buff);

    // Подсчитываем кол-во авторов определенного издательства
    int countOfAuthors = 0;
    int cond;
    for (int i = 0; i < *countOfBooks; i++){
        cond = strcmp(DataBase[i].publish, phName);
        if (cond == 0) {
            countOfAuthors++;
        }
    }
    
    book* Authors = (book*) malloc (countOfAuthors*sizeof(book)); // Выделяем новый массив для авторов.

    // Заполнение нового массива
    countOfAuthors = 0;
    for (int i = 0; i < *countOfBooks; i++){
        cond = strcmp(DataBase[i].publish, phName);
        if (cond == 0) {
            Authors[countOfAuthors] = DataBase[i];
            countOfAuthors++;
        }
    }

    // TODO: Добавить сортировку по имени(прокидывать в функцию b_sort аргументы по которым мы сортируем)
    bubble_sort_arr(Authors, countOfAuthors, true); // Сортировка нового массива

    printBooks(Authors, &countOfAuthors);
}

int main(){
    bool DEBUG = false;
    // Создать массив из n  книг (ввод с клавиатуры)
    // Реализовать функции : 
    // -	добавить новую книгу;
    // -	распечатать информацию о книге в табличном виде;
    // -	найти все книги заданного автора, результат вывести на экран;
    // -	найти всех авторов заданного издательства,  результат отсортировать по алфавиту, запомнить в массиве и вывести на экран;

    system("cls");
    setlocale(LC_ALL, "Russian");


    // основная часть
    // ----------------------------
    int code;
    book Books[20];       // Массив с книгами
    int countOfBooks = 0; // Счётчик книг в базе

    while(true){
        dispInterface();
        cout << "Enter code: "; cin >> code;
        switch (code)
        {
        case 1:
            addBook(Books, &countOfBooks);
            break;
        case 2:
            printBooks(Books, &countOfBooks);
            break;
        case 3:
            findBookByAuthor(Books, &countOfBooks);
            break;
        case 4:
            findAuthorByHouse(Books, &countOfBooks);
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