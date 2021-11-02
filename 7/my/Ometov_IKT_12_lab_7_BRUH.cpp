#include <iostream>
#include <iomanip>
#include <clocale>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctime>

// TODO:
// 1. Добавить валидацию на входе

using namespace std;

struct date{
    int day;
    char* month;
    int year;
};

struct fio{
    char* name;
    char* surname;
};

struct book{
    fio fio;
    date  date;
    char* title;
    char* publish;
    int   year;
};

// =============================
// Функции для работы с файлами
// =============================

void saveFile(FILE* file, book* DataBase, int* countOfBooks){
    // Сохраняет данные в файл

    book* DB_BUFFER;

    cout << "Saving..." << endl;

    file = fopen("DATA.bin", "wb");
        DB_BUFFER = DataBase;
        fwrite(DB_BUFFER, sizeof(book), *countOfBooks , file);	  
    fclose(file);    

    file = fopen("DATA.txt", "w");
        for (DB_BUFFER = DataBase; DB_BUFFER < DataBase + *countOfBooks; DB_BUFFER++)
        {
            fprintf (file, "%s\n", DB_BUFFER->fio.name);
            fprintf (file, "%s\n", DB_BUFFER->fio.surname);
            fprintf (file, "%s\n", DB_BUFFER->title);
            fprintf (file, "%s\n", DB_BUFFER->publish);
            fprintf (file, "%s\n", DB_BUFFER->date.month);
        }
    fclose(file);   

    cout << "Data saved!" << endl;
    
}

void readFile(FILE* file, book* DataBase, int* countOfBooks){
    // Подгружает данные из файла, если файла не существует, создаст файл.

    book* DB_BUFFER;
    char  buff[80]; 

    file = fopen("DATA.bin", "rb");
        cout << "Loading data... " << endl;
        
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++){
            fread (DB_BUFFER, sizeof(book),1, file);
            (*countOfBooks)++;
        }	
        (*countOfBooks)--;    

    fclose(file);

    file = fopen("DATA.txt", "r");
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++)	
        { 
            fscanf (file,"%s\n", buff); DB_BUFFER->fio.name   = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->fio.name, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->fio.surname= (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->fio.surname, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->title      = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->title, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->publish    = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->publish, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->date.month = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->date.month, buff);
        }
    fclose(file);

}

// =============================
// Сортировки
// =============================

void bubble_sort_arr(book* DataBase, int size, bool up = false){
    // false - по убыванию | true - по возрастанию

    book tmp;
    int cond;

    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){

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

// =============================
// Работа с интерфейсом
// =============================

void dispInterface(){
    cout << "\n";
    cout << "1 -- Add book to DataBase" << endl;
    cout << "2 -- Disp DataBase" << endl;
    cout << "3 -- Find book in DataBase" << endl;
    cout << "4 -- Disp author list" << endl;
    cout << "5 -- Disp retirees list" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(20) << "F.I.O.";
        cout << " |" << setw(20) << "Title";
        cout << " |" << setw(15) << "Publish";
        cout << " |" << setw(15) << "Year";
        cout << " |" << setw(20) << "Date of Birth";
        cout << " |" << endl;
}

// =============================
// Основные функции
// =============================

void addBook(book* DataBase, int* countOfBooks){
    // Добавляет информацию о новой книге в базу банных.


    char buff[20] = {};

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter book info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff); // костыль :-)
    cout << "Enter author name: ";       gets(buff); DataBase[*countOfBooks].fio.name = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfBooks].fio.name ,buff);
    cout << "Enter author surname: ";       gets(buff); DataBase[*countOfBooks].fio.surname = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfBooks].fio.surname ,buff);
    cout << "Enter author birthday: ";  cin >> (DataBase[*countOfBooks].date).day;
    gets(buff); // костыль :-)
    cout << "Enter author birthmonth(3 letter): ";gets(buff); (DataBase[*countOfBooks].date).month = (char*) malloc (strlen(buff) + 1); strcpy((DataBase[*countOfBooks].date).month ,buff);
    cout << "Enter author birthyear: "; cin >> (DataBase[*countOfBooks].date).year;
    gets(buff); // костыль :-)
    cout << "Enter book title: ";       gets(buff); DataBase[*countOfBooks].title   = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfBooks].title ,buff);
    cout << "Enter publishing house: "; gets(buff); DataBase[*countOfBooks].publish = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfBooks].publish ,buff);
    cout << "Enter year of publish: ";  cin >> DataBase[*countOfBooks].year;


    (*countOfBooks)++;
    system("pause");
    system("cls");
}

void printBooks(book* DataBase, int* countOfBooks){
    // Распечатывает таблицу базы данных


        cout << "\nCount of books: " << *countOfBooks << endl;
        printHeader();
        cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfBooks; i++){
        cout << "|"  << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
        cout << " |" << setw(20) << DataBase[i].title;
        cout << " |" << setw(15) << DataBase[i].publish;
        cout << " |" << setw(15) << DataBase[i].year;
        cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
        cout << " |" << endl;
        cout << "-----------------------------------------------------------------------------------------------------" << endl;
    }
}

void findBookByAuthor(book* DataBase, int* countOfBooks){
    // Функция выводит книги конкретного автора
    // на вход принимает имя и фамилию

    char buff[20] = {};

    cout << "\n\n";
    gets(buff);
    cout << "Enter author name: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);
    cout << "Enter author surname: "; gets(buff);
    char* surname = (char*) malloc (strlen(buff) + 1); strcpy(surname ,buff);


    printHeader();
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfBooks; i++){
        int cond = strcmp(DataBase[i].fio.surname, surname);
            cond = strcmp(DataBase[i].fio.name, name);

        if (cond == 0){
            cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
            cout << " |" << setw(20) << DataBase[i].title;
            cout << " |" << setw(15) << DataBase[i].publish;
            cout << " |" << setw(15) << DataBase[i].year;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
        }
        
    }
    
}

void findAuthorByHouse(book* DataBase, int* countOfBooks){

    
    // Ввод с консоли
    char buff[20] = {};
    cout << "\n\n";
    gets(buff);
    cout << "Enter publish house: "; gets(buff);
    char* phName = (char*) malloc (strlen(buff) + 1); strcpy(phName ,buff);

    

    // Создаем массив для авторов удовлетворяющих условию фильтрации
    book* Authors = (book*) malloc (sizeof(book)); // Выделяем новый массив для авторов.
    int countOfAuthors = 0;
    int cond;
    for (int i = 0; i < *countOfBooks; i++){
        cond = strcmp(DataBase[i].publish, phName);
        if (cond == 0) {
            Authors[countOfAuthors] = DataBase[i];
            countOfAuthors++;
            Authors = (book*) realloc (Authors, (countOfAuthors+1)*sizeof(book));
        }
    }
    
    bubble_sort_arr(Authors, countOfAuthors, true); // Сортировка нового массива
    printBooks(Authors, &countOfAuthors);           // Распечатка
}

void findRetiree(book* DataBase, int* countOfBooks){

    const time_t timer = time(NULL);
    struct tm *u = localtime(&timer);
    int current_year = u->tm_year + 1900;

    cout << "Current Year: " << current_year << endl;

    printHeader();
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfBooks; i++){

        if ((current_year - DataBase[i].date.year) >= 60){
            cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
            cout << " |" << setw(20) << DataBase[i].title;
            cout << " |" << setw(15) << DataBase[i].publish;
            cout << " |" << setw(15) << DataBase[i].year;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "-----------------------------------------------------------------------------------------------------" << endl;
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
    book Books[20];    // Массив с книгами
    int countOfBooks = 0;                           // Счётчик книг в базе (глобальная переменная)

    if ((file = fopen("DATA.bin", "rb")) != NULL){
        fclose(file);
        cout << "DataBase file already exist..." << endl;

        readFile(file, Books, &countOfBooks);
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
        case 5:
            findRetiree(Books, &countOfBooks);
            break;
        case 0:
            saveFile(file, Books, &countOfBooks);
            exit(0);
        default:
            cout << "Input Error, try again!" << endl;
            break;
        }
    }


    system("pause");
    return 0;
}