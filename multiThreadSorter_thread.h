#ifndef SORTER_H
#define SORTER_H
/*
Define structures and function prototypes for your sorter
*/

void print_The_List( movie_Record* pRecordArray, char * path, char * column); //helps to print out the result
/*
this will use the word provided in the parameter and will sort
the input file alphabetically based on that column
*/
int sort_The_List(char* sort_By_This_Value, FILE * file, char * output_Dir);


void * void_Of_Sort_The_List (void * arg);


//this checks if the given char string is CSV file or not
int is_CSV_File (const char * name, char * column);




/*
this function will go through the directory
finding .csv files. It will recurse through
the same function if it detects sub-diretories
within provided directory.
*/
void * scan_Directory (void * arg);


/*
this function calls is_Directory
and is_CSV_file to check if the file_Name
is direcory, CSV file, sorted CSV file or 
some other kind of file. Created this because
thread needs void * funtion while pthread_create
*/
void * is_DIR_CSV (void * file_Name);


//this function checks if the given char string is directory or not
int is_Directory (const char * name);


//this function will remove the .csv from the end of the char pointer
void remove_CSV (char * path, char * new_Path);


//Suggestion: define a struct that mirrors a record (row) of the data set

//Suggestion: prototype a mergesort function

#endif
