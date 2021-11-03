#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// тази функция създава масива, като прочита информацията от бинарен файл и я зарежда в динамична структура
// връща указател към масива
// приема указател към броя на файловете
NODE* create_array(int * files_count)
{
    // отваряме файла за четене
    FILE* fp = fopen("data.bin","rb");
    if(fp == NULL)
    {
        // ако нямаме такъв файл
        printf("Unable to open file!\n");
        return NULL;
    }
    // прочитаме броя на файловете записани
    if(fread(files_count, sizeof(int), 1, fp) != 1)
    {
        printf("File does not have entries!\n");
        return NULL;
    }
    // заделяме памет за динамичен масив
    NODE * array = (NODE *) malloc(sizeof(NODE) * (*files_count));
    if(array==NULL) // проверяваме за грешки
    {
        printf("Memory allocation problem!\n");
        exit(2);
    }
    // прочитаме инфото за файловете от бинарния файл
    if(fread(array,sizeof(NODE),(*files_count),fp) != (*files_count))
    {
        printf("Cannot read entries from file!\n");
        return NULL;
    }
    printf("File loaded!\n");
    fclose(fp); // затваряме файла
    return array; // връщаме указател към масива
}

// чрез тази функция, потребителят може да добави нов елемент в масива
// приема като параметър указателя към масива и указател към броя на елементите в него
// връща указател към масива
NODE * add_new(NODE* array, int * files_count)
{
    // заделяме памет за същия масив, само че с един елемент повече
    NODE * new_array = (NODE *) malloc(sizeof(NODE) * ((*files_count)+1));
    if(new_array==NULL) // проверяваме за грешки
    {
        printf("Memory allocation problem!\n");
        exit(2);
    }
    int i;
    // обхождаме стария масив
    for (i = 0; i < (*files_count); i++)
    {
        new_array[i] = array[i]; // копираме елементите от стария в новия масив
    }
    free(array); // освобождаваме паметта на стария масив

    // прочитаме инфото за новия файл и го запазваме в последната незапълнена позиция на новия масив
    printf("Enter file name: ");
    scanf("%s", new_array[(*files_count)].name);
    printf("Enter file path: ");
    scanf("%s", new_array[(*files_count)].path);
    printf("Enter file size: ");
    scanf("%d", &new_array[(*files_count)].file_size);
    printf("Enter create date in the following format (DD.MM.YYYY): ");
    scanf("%d.%d.%d", &new_array[(*files_count)].create_day, &new_array[(*files_count)].create_month,
          &new_array[(*files_count)].create_year);
    printf("Enter modification date in the following format (DD.MM.YYYY): ");
    scanf("%d.%d.%d", &new_array[(*files_count)].modified_day, &new_array[(*files_count)].modified_month,
          &new_array[(*files_count)].modified_year);
    printf("Is the file hidden? Enter 0 for NO and 1 for YES: ");
    scanf("%d", &new_array[(*files_count)].hidden);
    printf("Is the file read-only? Enter 0 for NO and 1 for YES: ");
    scanf("%d", &new_array[(*files_count)].read_only);
    printf("Is it system file? Enter 0 for NO and 1 for YES: ");
    scanf("%d", &new_array[(*files_count)].system_file);
    printf("Is the file executable? Enter 0 for NO and 1 for YES: ");
    scanf("%d", &new_array[(*files_count)].executable);
    printf("File entry saved!\n");
    (*files_count)++; // увеличаваме броя на файловете
    return new_array; // връщаме новия масив
}

// чрез тази функция потребителя може да търси файл в масива
// приема като параметър указателя към масива и броя на елементите в него
// не връща стойности
void find_file(NODE * array, int files_count)
{
    char filename[30];
    printf("Enter file name: ");
    scanf("%s", filename); // прочитаме името на файла
    int found = 0;
    int i;
    
    for (i = 0; i < files_count; i++)
    {
        // проверяваме дали името на текущия файл съдържа въведеното от потребителя име на файл
        if (strstr(array[i].name, filename) != NULL)
        {
            print_file_info(array[i]); // извикваме функцията, която принтира инфо за файла
            found = 1; // отбелязваме, че сме открили файл
        }
    }
    if (found == 0)
    {
        printf("No files found!\n"); // ако не сме открили файл
    }
}

// тази функция принтира инфо за файл
// приема като параметър една структура на файл
// не връща стойност
void print_file_info(NODE file)
{
    printf("file: %s; path: %s; size: %d; created %d.%d.%d; modified %d.%d.%d;", file.name, file.path, file.file_size,
           file.create_day, file.create_month, file.create_year, file.modified_day, file.modified_month, file.modified_year);
    if (file.hidden)
        printf(" hidden;");
    if (file.system_file)
        printf(" system file;");
    if (file.read_only)
        printf(" read-only;");
    if (file.executable)
        printf(" executable;");
    printf("\n");
}

// тази функция принтира инфо за папка посочена от потребителя
// приема като параметър указателя към масива и броя на елементите в него
void view_dir_info(NODE * array, int files_count)
{
    char directory[30];
    printf("Enter directory: ");
    scanf("%s", directory); // прочитаме име на папка;
    int i;
    int total_size = 0;
    int total_files = 0;
    printf("Dir \"%s\" contains:\n", directory);
    // обхождаме масива
    for (i = 0; i < files_count; i++)
    {
        // проверяваме дали името на папката се съдържа в пътя на файла
        if (strstr(array[i].path, directory) != NULL)
        {
            // ако се съдържа увеличаваме броячите
            printf("File %s/%s with size %d\n", array[i].path, array[i].name, array[i].file_size);
            total_size += array[i].file_size;
            total_files++;
        }
    }
    printf("Total files contained: %d\n", total_files);
    printf("Total size of directory: %d\n", total_size);
}

// тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
// приема като параметър указателя към масива и броя на файловете
void exitProgramm(NODE* array, int files_count)
{
    // отваряме файла с информацията в режим записване на бинарен файл
    FILE* fp = fopen("data.bin","wb");

    // проверяваме за проблеми
    if(fp == NULL)
    {
        printf("Unable to open file!\n");
        exit(1);
    }

    fwrite(&files_count, sizeof(int), 1, fp);
    fwrite(array, sizeof(NODE), files_count, fp);
    free(array);
    fclose(fp);

    
    exit(0);
}
