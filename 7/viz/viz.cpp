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

struct fio{
    char* name;
    char* surname;
};

struct student{
    date   date;
    fio    fio;
    char*  vector;
    int    number;
};

// =============================
// Функции для работы с файлами
// =============================

void saveFile(FILE* file, student* DataBase, int* countOfStudents){
    // Сохраняет данные в файл

    student* DB_BUFFER;

    cout << "Saving..." << endl;

    file = fopen("DATA.bin", "wb");
        DB_BUFFER = DataBase;
        fwrite(DB_BUFFER, sizeof(student), *countOfStudents , file);	  
    fclose(file);    

    file = fopen("DATA.txt", "w");
        for (DB_BUFFER = DataBase; DB_BUFFER < DataBase + *countOfStudents; DB_BUFFER++)
        {
            fprintf (file, "%s\n", DB_BUFFER->fio.name);
            fprintf (file, "%s\n", DB_BUFFER->fio.surname);
            fprintf (file, "%s\n", DB_BUFFER->vector);
            fprintf (file, "%s\n", DB_BUFFER->date.month);
        }
    fclose(file);   

    cout << "Data saved!" << endl;
    
}

void readFile(FILE* file, student* DataBase, int* countOfStudents){
    // Подгружает данные из файла, если файла не существует, создаст файл.

    student* DB_BUFFER;
    char  buff[80]; 

    file = fopen("DATA.bin", "rb");
        cout << "Loading data... " << endl;
        
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++){
            fread (DB_BUFFER, sizeof(student),1, file);
            (*countOfStudents)++;
        }	
        (*countOfStudents)--;    

    fclose(file);

    file = fopen("DATA.txt", "r");
        for (DB_BUFFER=DataBase; !feof(file); DB_BUFFER++)	
        { 
            fscanf (file,"%s\n", buff); DB_BUFFER->fio.name   = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->fio.name, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->fio.surname= (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->fio.surname, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->vector= (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->vector, buff);
            fscanf (file,"%s\n", buff); DB_BUFFER->date.month = (char*) malloc (strlen(buff)+1); strcpy (DB_BUFFER->date.month, buff);
        }
    fclose(file);

}

// =============================
// Сортировки
// =============================

void bubble_sort_arr(student* DataBase, int size, bool up = false){
    // false - по убыванию | true - по возрастанию

    student tmp;
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
    cout << "1 -- Add student to DataBase" << endl;
    cout << "2 -- Disp DataBase" << endl;
    cout << "3 -- Find student by cafedra" << endl;
    cout << "4 -- Find student by group" << endl;
    cout << "5 -- Disp old and yong students" << endl;

    cout << "0 -- Exit!" << endl;
    cout << "__________________________" << endl;
    cout << "\n";
}

void printHeader(){
    cout << "-------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(20) << "F.I.O";
        cout << " |" << setw(15) << "Kafedra";
        cout << " |" << setw(15) << "Group";
        cout << " |" << setw(20) << "Date";
        cout << " |" << endl;
}

// =============================
// Основные функции
// =============================

void addStudent(student* DataBase, int* countOfStudents){
    // Добавляет информацию о новой книге в базу банных.


    char buff[20] = {};

    cout << "\n\n";
    cout << "==========================" << endl;
    cout << "Enter book info: " << endl;
    cout << "==========================" << endl;
    cout << "\n";
    gets(buff); // костыль :-)
    cout << "Enter author name: ";      gets(buff); DataBase[*countOfStudents].fio.name = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfStudents].fio.name ,buff);
    cout << "Enter author surname: ";   gets(buff); DataBase[*countOfStudents].fio.surname = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfStudents].fio.surname ,buff);
    cout << "Enter author birthday: ";  cin >> (DataBase[*countOfStudents].date).day;
    gets(buff); // костыль :-)
    cout << "Enter author birthmonth(3 letter): ";gets(buff); (DataBase[*countOfStudents].date).month = (char*) malloc (strlen(buff) + 1); strcpy((DataBase[*countOfStudents].date).month ,buff);
    cout << "Enter author birthyear: "; cin >> (DataBase[*countOfStudents].date).year;
    gets(buff); // костыль :-)
    cout << "Enter kafedra: ";       gets(buff); DataBase[*countOfStudents].vector   = (char*) malloc (strlen(buff) + 1); strcpy(DataBase[*countOfStudents].vector ,buff);
    cout << "Enter number: "; cin >> DataBase[*countOfStudents].number;

    (*countOfStudents)++;
    system("pause");
    system("cls");
}

void printStudents(student* DataBase, int* countOfStudents){
    // Распечатывает таблицу базы данных


        cout << "\nCount of students: " << *countOfStudents << endl;
        printHeader();
        cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfStudents; i++){
        cout << "|"  << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
        cout << " |" << setw(15) << DataBase[i].vector;
        cout << " |" << setw(15) << DataBase[i].number;
        cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
        cout << " |" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
    }
}

void findStudentByCafedra(student* DataBase, int* countOfStudents){
    // Функция выводит книги конкретного автора
    // на вход принимает имя и фамилию

    char buff[20] = {};

    cout << "\n\n";
    gets(buff);
    cout << "Enter cafedra: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);
    

    printHeader();
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < *countOfStudents; i++){
        int cond = strcmp(DataBase[i].vector, name);
        
        if (cond == 0){
            cout << "|" << setw(10) << DataBase[i].fio.name << setw(10) << DataBase[i].fio.surname;
            cout << " |" << setw(15) << DataBase[i].vector;
            cout << " |" << setw(15) << DataBase[i].number;
            cout << " |" << setw(11) << DataBase[i].date.day << " " << setw(3) << DataBase[i].date.month << " " << setw(4) << DataBase[i].date.year;
            cout << " |" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
        }
        
    }
    
}

void findStudentByGroup(student* DataBase, int* countOfStudents){

    
    // Ввод с консоли
    char buff[20] = {};
    int num;
    cout << "\n\n";
    gets(buff);
    cout << "Enter cafedra: "; gets(buff);
    char* name = (char*) malloc (strlen(buff) + 1); strcpy(name ,buff);
    cout << "Enter number of group: "; cin >> num;


    // Создаем массив для записей удовлетворяющих условию фильтрации
    student* Group = (student*) malloc (sizeof(student)); // Выделяем новый массив для авторов.
    int countOfGroup = 0;
    for (int i = 0; i < *countOfStudents; i++){
        if (!strcmp(DataBase[i].vector, name) && DataBase[i].number == num) {
            Group[countOfGroup] = DataBase[i];
            countOfGroup++;
            Group = (student*) realloc (Group, (countOfGroup+1)*sizeof(student));
        }
    }
    
    bubble_sort_arr(Group, countOfGroup, true); // Сортировка нового массива
    printStudents(Group, &countOfGroup);        // Распечатка
    free(Group);                                  // Отчистка памяти
}

void findOlds(student* DataBase, int* countOfStudents){

    const time_t timer = time(NULL);
    struct tm *u = localtime(&timer);
    int current_year  = u->tm_year + 1900;
    int current_month = u->tm_mon + 1;
    int current_day   = u->tm_wday + 6;

    char months[12][4] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

    student* Tmp = (student*) malloc (2*sizeof(student));
    Tmp[0] = DataBase[0];
    Tmp[1] = DataBase[0];

    for (int i = 0; i < *countOfStudents; i++){

        // превод месяца в базе из char в int
        int m1 = 0;
        for (int j = 0; j < 12; j++){
            if (!strcmp(DataBase[i].date.month, months[j])){
                m1 = j + 1;
            }
        }

        int m2 = 0;
        for (int j = 0; j < 12; j++){
            if (!strcmp(Tmp[0].date.month, months[j])){
                m2 = j + 1;
            }
        }

        int m3 = 0;
        for (int j = 0; j < 12; j++){
            if (!strcmp(Tmp[1].date.month, months[j])){
                m3 = j + 1;
            }
        }

        if (DataBase[i].date.year > Tmp[0].date.year){
            Tmp[0] = DataBase[i];
        } else {
            if (DataBase[i].date.year == Tmp[0].date.year && m1 > m2){
               Tmp[0] = DataBase[i]; 
            } else {
                if (DataBase[i].date.year == Tmp[0].date.year && m1 == m2 && DataBase[i].date.day >= Tmp[0].date.day){
                    Tmp[0] = DataBase[i]; 
                }
            }
        }

        if (DataBase[i].date.year < Tmp[1].date.year){
            Tmp[1] = DataBase[i];
        } else {
            if (DataBase[i].date.year == Tmp[1].date.year && m1 < m3){
               Tmp[1] = DataBase[i]; 
            } else {
                if (DataBase[i].date.year == Tmp[1].date.year && m1 == m3 && DataBase[i].date.day <= Tmp[1].date.day){
                    Tmp[1] = DataBase[i]; 
                }
            }
        }

        m1 = 0;
        m2 = 0;
        m3 = 0;
    }
    int countOfArray = 2;
    printStudents(Tmp, &countOfArray);  
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
    student Students[20];    // Массив с книгами
    int countOfStudents = 0;                           // Счётчик книг в базе (глобальная переменная)

    if ((file = fopen("DATA.bin", "rb")) != NULL){
        fclose(file);
        cout << "DataBase file already exist..." << endl;

        readFile(file, Students, &countOfStudents);
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
            addStudent(Students, &countOfStudents);
            break;
        case 2:
            printStudents(Students, &countOfStudents);
            break;
        case 3:
            findStudentByCafedra(Students, &countOfStudents);
            break;
        case 4:
            findStudentByGroup(Students, &countOfStudents);
            break;
        case 5:
            findOlds(Students, &countOfStudents);
            break;
        case 0:
            saveFile(file, Students, &countOfStudents);
            exit(0);
        default:
            cout << "Input Error, try again!" << endl;
            break;
        }
    }


    system("pause");
    return 0;
}