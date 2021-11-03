#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    int files_count = 0;
    // тази функция създава масива, като прочита информацията от бинарен файл и я зарежда в динамична структура
    NODE* array = create_array(&files_count);

    int option;

    for(;;)
    {
        printf("\nMenu:\n");
        printf("Option 1: find file\n");
        printf("Option 2: add file\n");
        printf("Option 3: display directory info\n");
        printf("Option 4: save changes and exit the program\n");
        printf("Enter your option: ");

        scanf("%d",&option);

        if(option==1)
        {
            // тази функция извежда инфо за файл посочен от потребителя
            find_file(array, files_count);
        }
        else if(option==2)
        {
            // чрез тази функция, потребителят може да добави нов файл в масива
            array = add_new(array, &files_count);
        }
        else if(option==3)
        {
            // тази функция принтира данните за папка посочена от потребителя
            view_dir_info(array, files_count);
        }
        else if(option==4)
        {
            // тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
            exitProgramm(array, files_count);
        }
        else
        {
            printf("Incorrect input! Try again!\n");
        }
    }


    return 0;
}
