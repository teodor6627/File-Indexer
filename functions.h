#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// структурата на един елемент/запис
typedef struct NODE {
    char path[100];
    char name[30];
    int file_size;
    int create_day;
    int create_month;
    int create_year;
    int modified_day;
    int modified_month;
    int modified_year;
    int hidden;
    int read_only;
    int system_file;
    int executable;
} NODE;

// прототипите на функциите, съдържащи се в functions.c
NODE* create_array(int * files_count);
NODE * add_new(NODE* array, int * files_count);
void find_file(NODE * array, int files_count);
void print_file_info(NODE file);
void view_dir_info(NODE * array, int files_count);
void exitProgramm(NODE* array, int files_count);

#endif // FUNCTIONS_H_INCLUDED
