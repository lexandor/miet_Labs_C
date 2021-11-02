#include <iostream>
#include <ctype.h>
#include <string.h>

using namespace std;

char* readStr(){
    // считывает строку
    char buffer[120] = {'q'};
    char* str = nullptr;
 
    gets(buffer);				                // ввод с клавиатуры в статический буфер
    str = (char*) malloc (strlen(buffer)+1);    // выделение динамической памяти под строку
    str = strcpy(str, buffer);		            // копирование строки в динамическую память

    return str;
}

char* replaceStr(char* str, char* from, char* to){
    // Заменяет первое вхождение строеи "from" на "to"
    
    char* target = strstr(str,from); // строка начинающаяся с "from"

    if (target != NULL){
        int sizeOfOldStr = strlen(str);
        int sizeOfNewStr = sizeOfOldStr - strlen(from) + strlen(to);

        char* new_str = nullptr;
        new_str = (char*) malloc (sizeOfNewStr*sizeof(char) + 1);      // расширение памяти на новую строку
        new_str = strncpy(new_str,str,sizeOfOldStr - strlen(target));  // первая часть строки
        new_str = strcat(new_str, to);                                 // производит замену
        new_str = strcat(new_str, target + strlen(from));              // правая часть строки

        free(str);

        return new_str;
    } else {
        return str;
    }

    
}


int main(){

    // Создать функцию для замены подстроки в строке,
    // например, заменить подстроку after на before (возвращается измененная строка).
    // Тестовая программа: 
    //     Ввести с клавиатуры 2 динамические строки, содержащие по нескольку слов.
    //     Для каждой строки вызвать функцию замены подстроки с различными данными 

    system("cls");


    char FROM[] = "after";
    char TO[] = "before";

    // основная часть
    // ----------------------------
    cout << "Enter some string:" << endl;
    char* str1 = readStr();

    cout << "Enter some string:" << endl;
    char* str2 = readStr();

    cout << "\n\n\n";

    str1 = replaceStr(str1, FROM, TO);
    cout << str1 << endl;

    str2 = replaceStr(str2, FROM, TO);
    cout << str2 << endl;

    system("pause");
    return 0;
}