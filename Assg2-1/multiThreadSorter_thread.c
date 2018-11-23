#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "generalFunctions.h"
#include "columnsorter.h"
#include "movieListData.h"
#include "movieValueList.h"
#include "mergesort.h"
#include "multiThreadSorter_thread.h"
#include "tokenizer.h"
#include "hashTable.h"
#include <sys/wait.h>
#include <pthread.h>
#define TRUE				1
#define FALSE				0



char * sorting_Directory_Char;              //this will store the input directory name if provided
char * sort_By_This_Value;       //this will store the input sorting column name must be provided
char * output_Place_Char;            //this will store the output directory name if provided
DIR * output_Place_Dir;             //output directory to check if the provided directory opens or not
DIR * sorting_Directory_Dir;                    //sorting directory to check if the provided directory opens or not
pthread_mutex_t data_Mutex = PTHREAD_MUTEX_INITIALIZER;

/*
        movie list is the main
        record struct pointer 
        pointer array, that is 
        goint to store all the
        movies in struct (i.e,
        each struct is a movie)
        and later we will do 
        merge sort on that 
        pointer pointer array.
*/
movie_Record movie_List;            //main record to store all the movies in a list
    
int total_Threads;                  //this will count the total number of threads spawned 
sorting_Column_Info column_Info;						//this will hold info regarding the column's type and index no.
FUNCTION_POINTER_CMPDATA pFuncCompare = compare;











int main(int argc, char* argv[]) {
	
    sorting_Directory_Char = (char *) malloc (sizeof(char) * 100);
    output_Place_Char = (char *) malloc (sizeof(char) * 100);
    
    
    movie_List.pRecArray = (one_Movie_Values**) malloc (1024 * sizeof(one_Movie_Values*));
    movie_List.iCapacity = 1024;
    movie_List.iSize = 0;



//checking if the input argument is correct or Not
	if(argc == 3) {
			if (strcmp("-c", argv[1]) != 0) {
				fprintf(stderr, "Error! Parameters are not correctly formated.\n");
				return -1;    //returning -1 because it's an error
			}
			/*
			since there isn't any -d in the Parameter
			we are going to use the current working
			directory as input and output directory
			*/
            sorting_Directory_Char = ".";
            output_Place_Char = ".";
			/*
			this will create a directory and also
			a struct that keeps all the information
			about directory.
			*/
			sorting_Directory_Dir = opendir("./");

			if(sorting_Directory_Dir == NULL) {
				fprintf(stderr, "Error! Unable to open current directory.\n");
				return -1;		//returning -1 because it's an error
			}

			sort_By_This_Value = argv[2]; 
        
            pthread_t main_Thread;
            pthread_attr_t main_Attr;
            pthread_attr_init(&main_Attr);
            pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
            pthread_join(main_Thread, NULL);
        
            //scan_Directory(sorting_Directory_Char);
            mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
        
            if((*(movie_List.pRecArray + 0)) != NULL){
                print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
            }
            
            printf("Total Threads : %d.\n", total_Threads);
        
			
			closedir(sorting_Directory_Dir);
                if (movie_List.pRecArray != NULL) {
		              clearMovieList(&movie_List);
	            }
			return 0;
	}
	

	if(argc == 5) {

			if(strcmp("-c", argv[1]) == 0) {
				if(strcmp("-d", argv[3]) == 0) {
					sorting_Directory_Dir = opendir(argv[4]);

					if(sorting_Directory_Dir == NULL) {
						fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
						return -1;		//returning -1 because it's an error
					}
                    
                    strcpy(sorting_Directory_Char, argv[4]);
					sort_By_This_Value = argv[2];
					strcpy(output_Place_Char, argv[4]);
                    
//output_Place_Char = argv[4];
				    
                    
                    
                    pthread_t main_Thread;
                    pthread_attr_t main_Attr;
                    pthread_attr_init(&main_Attr);
                    pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                    pthread_join(main_Thread, NULL);
        

					//scan_Directory(sorting_Directory_Char);
                    mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                    
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					closedir(sorting_Directory_Dir);
                    
                    if (movie_List.pRecArray != NULL) {
		              clearMovieList(&movie_List);
	                   }
            printf("Total Threads : %d.\n", total_Threads);
                    
					return 0;

				}
				else if(strcmp("-o", argv[3]) == 0){
					sorting_Directory_Dir = opendir("./");
					if(sorting_Directory_Dir == NULL) {
						fprintf(stderr, "Error! Unable to open the current directory.\n");
						return -1;		//returning -1 because it's an error
					}
					output_Place_Dir = opendir(argv[4]);
					if(output_Place_Dir == NULL){
						fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
						return -1;
					}
					else {
						closedir(output_Place_Dir);
					}
                    
                    strcpy(output_Place_Char, argv[4]);
//char * output_Place = argv[4];
                    strcpy(sorting_Directory_Char, ".");
//char directory_Char[3000] = ".";
					sort_By_This_Value = argv[2];
				
                    
                    
                    
                    pthread_t main_Thread;
                    pthread_attr_t main_Attr;
                    pthread_attr_init(&main_Attr);
                    pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                    pthread_join(main_Thread, NULL);
        
                    
                    
                    //scan_Directory(sorting_Directory_Char);
                    mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                    
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                    
            printf("Total Threads : %d.\n", total_Threads);
                    
                    closedir(sorting_Directory_Dir);
                    
                    if (movie_List.pRecArray != NULL) {
		              clearMovieList(&movie_List);
	                }
					return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;				//returning -1 because it's an error
				}
			}

			if(strcmp("-c", argv[3]) == 0){
				if(strcmp("-d", argv[1]) == 0) {
					sorting_Directory_Dir = opendir(argv[2]);
					   if(sorting_Directory_Dir == NULL) {
						  fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
						  return -1;		//returning -1 because it's an error
					   }

					sort_By_This_Value = argv[4];
                    strcpy(output_Place_Char, argv[2]);
//char * output_Place = argv[2];
	                strcpy(sorting_Directory_Char, argv[2]);

                    
                    
                    pthread_t main_Thread;
                    pthread_attr_t main_Attr;
                    pthread_attr_init(&main_Attr);
                    pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                    pthread_join(main_Thread, NULL);
        
                    
                    
                    //scan_Directory(sorting_Directory_Char);
                    mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                    
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                    
                    
            printf("Total Threads : %d.\n", total_Threads);
                    
                    
					closedir(sorting_Directory_Dir);
				   
                    if (movie_List.pRecArray != NULL) {
		              clearMovieList(&movie_List);
	                }
					return 0;

				}
				else if(strcmp("-o", argv[1]) == 0){
					sorting_Directory_Dir = opendir("./");
					if(sorting_Directory_Dir == NULL) {
						fprintf(stderr, "Error! Unable to open the current directory.\n");
						return -1;		//returning -1 because it's an error
					}
					output_Place_Dir = opendir(argv[2]);
					if(output_Place_Dir == NULL){
						fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
						return -1;
					}
					else {
						closedir(output_Place_Dir);
					}
                    sorting_Directory_Char = ".";
					sort_By_This_Value = argv[4];
					
                    
                    pthread_t main_Thread;
                    pthread_attr_t main_Attr;
                    pthread_attr_init(&main_Attr);
                    pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                    pthread_join(main_Thread, NULL);
        
                    
                    
                    //scan_Directory(sorting_Directory_Char);
                    mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                   
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
            
            printf("Total Threads : %d.\n", total_Threads);
                    
                    
					closedir(sorting_Directory_Dir);
					
                    if (movie_List.pRecArray != NULL) {
		              clearMovieList(&movie_List);
	                }
					return 0;
				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;				//returning -1 because it's an error
				}
			}

			else {
				fprintf(stderr, "Error! Parameters are not correctly formated.\n");
				return -1;				//returning -1 because it's an error	
			}


	}


	if(argc == 7) {
			if(strcmp("-c", argv[1]) == 0){
				if(strcmp("-d", argv[3])==0 && strcmp("-o", argv[5]) == 0){

						sorting_Directory_Dir = opendir(argv[4]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[2];
						strcpy(output_Place_Char, argv[6]);
                        strcpy(sorting_Directory_Char, argv[4]);

						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}
                            
                    
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
        
                    
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                        
                    if((*(movie_List.pRecArray + 0))!= NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                
            printf("Total Threads : %d.\n", total_Threads);
                    
                    
						closedir(sorting_Directory_Dir);
                        
                        if (movie_List.pRecArray != NULL) {
		                      clearMovieList(&movie_List);
	                   }
						return 0;
				}
				else if(strcmp("-o", argv[3])==0 && strcmp("-d", argv[5])==0){

						
						sorting_Directory_Dir = opendir(argv[6]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[2];
						strcpy(output_Place_Char, argv[4]);
                        strcpy(sorting_Directory_Char, argv[6]);

						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL || sorting_Directory_Dir == NULL){
							fprintf(stderr, "Error! Given Output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}

                        
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
        
                        
                    
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                       
                    if((*(movie_List.pRecArray + 0))!= NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                
            printf("Total Threads : %d.\n", total_Threads);
                    
                    
                    
						closedir(sorting_Directory_Dir);
						
                        if (movie_List.pRecArray != NULL) {
                                clearMovieList(&movie_List);
	                       }
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}
			}
			else if(strcmp("-c", argv[3])==0){
				if(strcmp("-d", argv[1]) == 0 && strcmp("-o", argv[5]) == 0){

						sorting_Directory_Dir = opendir(argv[2]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[4];

						strcpy(output_Place_Char, argv[6]);
                        strcpy(sorting_Directory_Char, argv[2]);
                    
                        
						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}
                        
                    
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
                
                    
                    
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                       
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                  
            printf("Total Threads : %d.\n", total_Threads);
                    
                    
						closedir(sorting_Directory_Dir);
						
                        if (movie_List.pRecArray != NULL) {
                            clearMovieList(&movie_List);
                        }
						return 0;

				}
				else if(strcmp("-o", argv[1])==0 && strcmp("-d", argv[5])==0){

						sorting_Directory_Dir = opendir(argv[6]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[4];
						strcpy(output_Place_Char, argv[2]);
                        strcpy(sorting_Directory_Char, argv[6]);

						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}
                        
                    
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
                
                    
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                       
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
            printf("Total Threads : %d.\n", total_Threads);
                        
                    
						closedir(sorting_Directory_Dir);
						
                        if (movie_List.pRecArray != NULL) {
		                  clearMovieList(&movie_List);
                        }
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}

			}
			else if(strcmp("-c", argv[5])==0){
				if(strcmp("-d", argv[1])==0 && strcmp("-o", argv[3]) == 0){

						sorting_Directory_Dir = opendir(argv[2]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[6];

						strcpy(sorting_Directory_Char, argv[2]);
						strcpy(output_Place_Char, argv[4]);

						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}
                        
                    
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
        
                        
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                       
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
                 
            printf("Total Threads : %d.\n", total_Threads);
                    
						closedir(sorting_Directory_Dir);
                        
                        if (movie_List.pRecArray != NULL) {
                            clearMovieList(&movie_List);
                        }
						return 0;

				}
				else if(strcmp("-o", argv[1])==0 && strcmp("-d", argv[3])==0){

						sorting_Directory_Dir = opendir(argv[4]);

						if(sorting_Directory_Dir == NULL) {
							fprintf(stderr, "Error! Given sorting directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[6];

						strcpy(output_Place_Char, argv[2]);
                        strcpy(sorting_Directory_Char,argv[4]);

						output_Place_Dir = opendir(output_Place_Char);
						if(output_Place_Dir == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_Place_Dir);
						}

                        
                        pthread_t main_Thread;
                        pthread_attr_t main_Attr;
                        pthread_attr_init(&main_Attr);
                        pthread_create(&main_Thread, &main_Attr, scan_Directory, (void *)sorting_Directory_Char);
                        pthread_join(main_Thread, NULL);
        
                    
                        //scan_Directory(sorting_Directory_Char);
                        mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
                       
                    
                    if((*(movie_List.pRecArray + 0)) != NULL){
                            print_The_List( &movie_List, output_Place_Char, sort_By_This_Value);
                    }
                    
					
               
            printf("Total Threads : %d.\n", total_Threads);
                    
                        
						closedir(sorting_Directory_Dir);
                       
                        if (movie_List.pRecArray != NULL) {
		                      clearMovieList(&movie_List);
                        }
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}

			}
			else {
				fprintf(stderr, "Error! Parameters are not correctly formated.\n");
				return -1;  			//returning -1 because it's an error
			}

	}
	else {
		fprintf(stderr, "Error! Parameters are not correctly formated.\n");
		return -1;
	}

//main method ends here
}	

	


void* void_Of_Sort_The_List (void * arg){
    int * temp = (int *) malloc (sizeof(int));
    pthread_mutex_lock(&data_Mutex);
    total_Threads++;
    pthread_mutex_unlock(&data_Mutex);
    char * arg_Char = (char *)arg;
   // char * arg_Char = (char * ) malloc (sizeof(char) * (strlen((char *)arg));
    * temp = sort_The_List(sort_By_This_Value, arg_Char, output_Place_Char);
    pthread_exit(temp);
}





/*
sort_The_List is the function that
is going to sort the stdin movie_List
file in alphabetical boreds. The column
that is going to be sorted is represented
by sort_By_This_Value.
*/
int sort_The_List(char* sort_By_This_Value, char * file_Char, char * output_Dir) {

    
 printf("\n\nFile passed in sort_The_List - %s\n\n", file_Char);
    FILE * file = fopen(file_Char, "r");
	// Buffer for reading from stdin
	BUFFER read_File;																	// Buffer is created to read the stdin File
	BUFFER header_Of_File;																// For holding the header line

	//Initializing Buffer to NULL and then will add data to it
	read_File.data = NULL;
	read_File.length_Of_Data = 0;
	int output_Result = 1;			//setting the output result to 1 in the beginning

	//sorting_Column_Info column_Info;						//this will hold info regarding the column's type and index no.
	column_Info.index = -1;
	column_Info.index_Type_SIF = INDEX_TYPE_INTEGER;
					/*
					the type of column to sort is set to integer First
					and will be changed according later in the function
					if necessary
					*/
    
	/*
	movie_List.pRecArray = (one_Movie_Values**) malloc (1024 * sizeof(one_Movie_Values*));
	movie_List.iCapacity = 1024;
	movie_List.iSize = 0;
	//int no_Use = 0;
    */
    if(file == NULL){
        printf("File is not open\n\n\n");
        return -1;
    }else {
        printf("\n\n\nHey how are you\n\n\n");   
    }
     
		// Read the header and get the index for the sorting key
		if (getline(&(read_File.data), &(read_File.length_Of_Data), file) > 0 ) {
            
    printf("\n\nThe is get line - %s\n\n", read_File.data);        
             delete_Newline_Char_At_The_End(&read_File);						// this will delete the new line character from the end of the string line
			 header_Of_File.data = (char*)malloc (sizeof(char) * read_File.length_Of_Data);
			 header_Of_File.length_Of_Data = read_File.length_Of_Data;

			 strcpy(header_Of_File.data, read_File.data);			// copy of header line before tokenizing
			 //head_Of_File keeps record of the first line that is that name of all the columns
            
             
            
             int no_Of_Columns_In_Header = 0;
             Tokenizer token_Word;
             initialize_Tokenizer(&token_Word, header_Of_File.data, ',','\"');
             char * word;
             word = getNextToken(&token_Word);
             //this while loop counts the number of column in a header in given file
             while(word != NULL) {
                no_Of_Columns_In_Header++;
                word = getNextToken(&token_Word);
             }
            
            
printf("\n\nI am here - 1\n\n");    
printf("\n\nNo. of columns - %d\n\n", no_Of_Columns_In_Header);            
            /*
                This is the pointer to struct
                that keeps the column_Name
                and the index number of that column
                name
            */
            strcpy(header_Of_File.data, read_File.data);
            
printf("\n\nThis is the header  - %s\n\n", header_Of_File.data);
             header_Struct ** struct_Pointer_Header = (header_Struct **) malloc (sizeof(header_Struct*) * no_Of_Columns_In_Header);  //this is a struct pointer that will store the index and the column names from header line
             /****************************************/
             //This struct array will keep all the columns of the particular file in it,
             //so that it can be used to get the hash_Key for each column of the movies
             int temp_xyz_x = 0;
             Tokenizer token_Word_Two;
             initialize_Tokenizer (&token_Word_Two, header_Of_File.data, ',', '\"');
             char * word_Two;
             //stuffing the header struct pointer with column names
             while (temp_xyz_x < no_Of_Columns_In_Header) {
                word_Two = getNextToken(&token_Word_Two);
                 header_Struct * ptr = (header_Struct*)malloc(sizeof(header_Struct));
                ptr->column_Name = (char *) malloc (sizeof(char) * (strlen(word_Two) + 1));
                strcpy(ptr->column_Name, word_Two);
                *(struct_Pointer_Header + temp_xyz_x) = ptr;
                temp_xyz_x++;
             }
   
            
            /*
                This is the hash table that 
                is created by hash_Table.c,
                because we already have 28 
                columns and we can get the 
                key by (int)(column_Name)%28
                and use hash table to get the
                real index of that particular
                column_Name to store it into 
                struct_Pointer_Header
            */
            hash_Struct * hash_Table = (hash_Struct *) malloc (sizeof(hash_Table) * 28);
            create_Hash_Table(hash_Table);          
            //this will create hash_Table with 28 entries entered in their with index number
        
       
            /*
                this chunck of code will get hash_Key of 
                every column_Name and use that hash_Key to
                get the real column index from hash_Table 
                and put it in struct_Pointer_Header
            */
            
printf("\nI am here - 2\n");
            int hash_Key;
            temp_xyz_x--;
            while (temp_xyz_x >= 0){
                    hash_Key = ((long long)((*(struct_Pointer_Header + temp_xyz_x))->column_Name)) % 28;
printf("Hash Key - %d\n\n",hash_Key);
                    hash_Struct * ptr = (hash_Table + hash_Key);
                        while (ptr != NULL){
                                if(strcmp(ptr->column_Name, (*(struct_Pointer_Header + temp_xyz_x))->column_Name)==0){
                                        (*(struct_Pointer_Header + temp_xyz_x))->index = ptr->index;
                                        break;
                        }
                            ptr = ptr->next;  
                        }
printf("\n\nThis is the Column Name, and it's index - %s \t %d\n\n", (*(struct_Pointer_Header + temp_xyz_x))->column_Name,((*struct_Pointer_Header + temp_xyz_x))->index);
                    if(ptr == NULL){
                        fprintf(stderr, "Error! One of the column in this file isn't same as one of the 28 given columns.");
                        return -1;
                    }

            temp_xyz_x--;
            }
           
            
            
//this is where we start stuffing the record pointing to the structs containing info about each movie
			if (get_Column_Index_To_Sort_List(sort_By_This_Value, &column_Info, read_File.data)) {
							fprintf(stderr, "Error! Unable to parse the input column name.\n");
                            return -1;
            }
            else {
				// Read data line by line. Creates record and put them into array
				while (getline(&(read_File.data), &(read_File.length_Of_Data), file) > 0) {
					   delete_Newline_Char_At_The_End(&read_File);

                       one_Movie_Values* pRecord = make_Movie_Value_List(read_File.data, &column_Info, struct_Pointer_Header,no_Of_Columns_In_Header);
					       if (pRecord) {
						          add_One_Movie_To_The_List(&movie_List, pRecord);
					       }
                           else {
						          fprintf(stderr, "Error! Unable to create movie list!\n");
                                  return -1;
					       }  
                }
                
                
/****************************************/
    //clearing the hash_Table 
            int temp_s = 0;
                while (temp_s < 28){
                    if((hash_Table + temp_s) != NULL){
                    free(hash_Table + temp_s);
                    }
                temp_s++;
            }  
/****************************************/
				 output_Result = 0;
		}
	}
		else {
			fprintf(stderr, "Error! Unable to read file provided within directory. Please check file or directory\n");
            output_Result = -1;
		}

	freeBuffer(&header_Of_File);
	freeBuffer(&read_File);
	
	return output_Result;
}








void * is_DIR_CSV (void * file_Name){
	const char * check_This_File = (const char *)file_Name;
    pthread_mutex_lock(&data_Mutex);
    total_Threads++;
    pthread_mutex_unlock(&data_Mutex);
	int * temp = (int *) malloc (sizeof(int));
	* temp = is_Directory(check_This_File);
	if((*temp) == 0){
		pthread_exit(temp);			//returning 0 because it's a directory
	} else {
		* temp = is_CSV_File(check_This_File, sort_By_This_Value);
		if((* temp) == 0){
			*temp = 1;
			pthread_exit(temp);		//returning 1 because it's a CSV file
		} else {
			* temp = -1;
			pthread_exit(temp);	//returning -1 because it's not a directory and not a CSV file, it could be already sorted CSV file
		}
	}
}








//this checks if the given char string is directory or not
int is_Directory(const char * name) {
	DIR * temp_dir = opendir(name);
	if (temp_dir != NULL){
        if(strcmp("/.", name + (strlen(name) - 2)) == 0){
printf("\nSkipping this directory\n");
            return -1;
        }
        else if(strcmp ("/..", name + (strlen(name) - 3)) == 0){
printf("\nSkippint this directory\n");
            return -1;
        }
		closedir(temp_dir);
		return 0;	//returns 0 if it's directory, else -1
	}
	return -1;
}







//this checks if the given char string is CSV file or not
int is_CSV_File (const char * name, char * column) {
//printf("CHECKING THIS FILE : %s with this column %s\n\n", name, column);
	char test_Name[strlen(column) + 4];
	strncpy(test_Name, column, strlen(column));
	strcat(test_Name, ".csv");
    
    //first checks if it is sorted CSV or not
	if((strlen(name) > (strlen(column) + 4)) && !(strcmp(name + strlen(name) - (strlen(column) + 4), test_Name))){
		fprintf(stderr, "%s - This file is already sorted.\n", name);
		return -1;		//returning -1 because this file is already sorted
	}
    
    //checks if it is CSV or not
	if(strlen(name) > 4 && !(strcmp(name + strlen(name) - 4, ".csv"))){
		return 0;			//returns 0 if it's csv file, else -1
	}
	fprintf(stderr, "\n%s - This isn't a CSV file.\n", name);
	return -1;
}










/*
this function will scan through the directory
to find .csv files and possibly other
sub-directories if there's any.
It also performs sorting on finding
CSV file with sorting_Column, which is the
column user wants to sort file on.
*/
void * scan_Directory(void * arg){
	//setting this value to an unusal value so that if later program breaks, we can check if this value changes or not
    char * arg_Char = (char *)arg;
    char sorting_Directory_Char_Path[strlen(arg_Char) + 50];
    sorting_Directory_Char_Path[0] = '\0';
//char * sorting_Directory_Char_Path = (char *) malloc (sizeof(char) *(strlen(arg_Char) + 200));
    strcpy(sorting_Directory_Char_Path, arg_Char);
    DIR * directory = opendir(sorting_Directory_Char_Path);
	struct dirent * directory_Info;
	char current_Dir_Path[strlen(sorting_Directory_Char_Path) + 1];
	strcpy(current_Dir_Path, sorting_Directory_Char_Path);
    DIR * checker_Directory = opendir(sorting_Directory_Char_Path);
    int num_Of_Thread_In_Array = 0;
    
    
    //this will check the total number of files in a directory
    int num_Of_Files = 0;
    struct dirent * file_Checker_Dirent;
    while ((file_Checker_Dirent = readdir(checker_Directory)) != NULL){
        num_Of_Files++;
        
    }
    closedir(checker_Directory);
    pthread_t threads[num_Of_Files];
    pthread_t file_Checker_Thread;
   // int track_FCT = 0;
    
    printf("This is number of files - %d\n", num_Of_Files);
	while ((directory_Info = readdir(directory))!= NULL){
        int * return_Value_Of_Thread;
        /*
		concatenating path as each file within directory
		will have different path.
		e.g-> directory/file1
			directory/file2
			directory/subdirectory/file3
		*/
        strcat(sorting_Directory_Char_Path, "/");
        strcat(sorting_Directory_Char_Path, directory_Info->d_name);
        
        pthread_attr_t attr_FCT;
        pthread_attr_init(&attr_FCT);
        pthread_create(&file_Checker_Thread, &attr_FCT, is_DIR_CSV, (void *)sorting_Directory_Char_Path);
        pthread_join(file_Checker_Thread, (void **)(&return_Value_Of_Thread));
       // track_FCT++;
    
printf("This is the file name part one: %s\n", sorting_Directory_Char_Path);  
        if(*(return_Value_Of_Thread)==0){
            free(return_Value_Of_Thread);
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            //this is a sub-directory
            char *temp_Sorting_Directory_Char_Path = (char *) malloc (sizeof(char) *(strlen(sorting_Directory_Char_Path) + 1));
            strcpy(temp_Sorting_Directory_Char_Path, sorting_Directory_Char_Path);
            pthread_create(&threads[num_Of_Thread_In_Array], &attr, scan_Directory, (void *)temp_Sorting_Directory_Char_Path);
            num_Of_Thread_In_Array++;
            strcpy(sorting_Directory_Char_Path, current_Dir_Path);
        }
        else if(*(return_Value_Of_Thread) == 1){
            free(return_Value_Of_Thread);
            pthread_attr_t attr2;
            pthread_attr_init(&attr2);
printf("\n\nRight before creating thread - %s\n\n", sorting_Directory_Char_Path);
            char* temp2_Sorting_Directory_Char_Path = (char *) malloc (sizeof(char) * (strlen(sorting_Directory_Char_Path) + 1));
            strcpy(temp2_Sorting_Directory_Char_Path, sorting_Directory_Char_Path);
            pthread_create(&threads[num_Of_Thread_In_Array], &attr2, void_Of_Sort_The_List, (void *)temp2_Sorting_Directory_Char_Path);
            
            pthread_mutex_lock(&data_Mutex);
            total_Threads++;
            pthread_mutex_unlock(&data_Mutex);
            sorting_Directory_Char_Path[0] = '\0';
            num_Of_Thread_In_Array++;
            strcpy(sorting_Directory_Char_Path, current_Dir_Path);
        }
        else {
            free(return_Value_Of_Thread);
            sorting_Directory_Char_Path[0] = '\0';
            strcpy(sorting_Directory_Char_Path, current_Dir_Path);
        }
    }
   
    int i = 0;
    for ( i=0; i <num_Of_Thread_In_Array; i ++){
        pthread_join(threads[i], NULL);
    }
    
    closedir(directory);
   // free(sorting_Directory_Char_Path);
    pthread_exit(0);
}

	
/*
			
			//checks if the current file that file pointer points to is a directory or not
			return_Value = is_Directory(sorting_Directory_Char);
			/
			if return value is zero, it means this is directory
			and will perform recurssion from this point on that
			sub-directory
			/
			if(return_Value == 0) {
				
				PID = fork();
				int status_Three = 0;		// this is just got parents to wait until child returns


				if(PID == 0) {			//this means it's a child Process
					strcpy(current_dir_path, sorting_Directory_Char);	//changing the current path for child process as it is going to be at sub directory level
					directory = opendir(sorting_Directory_Char);	//changing directory to sub directory for child process
				}
				else if(PID > 0) {
					printf("%d," ,getpid());
					wait(&status_Three);	//parent waiting until child returns going through sub level directory;
					exit(0);
				}
			}
			else {
				return_Value = is_CSV_File(sorting_Directory_Char, sort_By_This_Value);
				if(return_Value == 0){
					
					PID = fork();
					int status_Two = 0;

					if(PID == 0) {
						FILE * file = fopen(sorting_Directory_Char, "r");
						return_Value = sort_The_List(sort_By_This_Value, file, output_Place_Char, directory_Info->d_name);
						fclose(file);
						printf("%d," ,getpid());


						return return_Value;
					}
					else if (PID > 0) {
						wait(&status_Two);	//parent waiting until child sorts the CSV file.
						exit(0);
					}
				}
				else {
				//	printf("%s is not a csv file or directory\n", path);
					strcpy(sorting_Directory_Char, current_dir_path);
					exit(0); //continuing to the next loop because read value isn't directory or CSV file
				}
			}

		// if the read value is not directory, check if it's CSV file or not
	strcpy(sorting_Directory_Char,current_dir_path);	//changing directory/file1 to directory, because we are at same level but just looping to next file
	}
    free(sorting_Directory_Char_Path);
	return return_Value;
}



*/









//this function will remove the .csv from the end of the char pointer
void remove_CSV (char * path, char * new_Path){
	if(strcmp(path + strlen(path) - 4, ".csv") == 0){
		strncpy(new_Path, path, strlen(path) - 4);
	return;
	}
	return;
}


/*
Writes the data from the movie_Record into stdout
*/
void print_The_List( movie_Record* pRecordArray, char * path, char * column) {


    char * file_Name = "AllFiles";
	char * output_File = (char * ) calloc ((strlen(path) + strlen(column) + 9 + strlen(file_Name)) , sizeof(char));
	/*
    if (strcmp(path + strlen(path) - 4, ".csv") == 0){
		strncpy(output_File, path, strlen(path) - strlen(file_Name));

	}
	 else 
     */
    if(strcmp (path + strlen(path) -1, "/") != 0){
		strcat(path, "/");
		strcpy(output_File, path);

	}

//printf("\n\nOUTPUT path : %s\n\n", path);

	//printf("Directory : %s\n\n\n", output_File);
	//char * file_Name_Without_CSV = (char * ) malloc ( (strlen(file_Name)-3)  * sizeof(char) );
	//remove_CSV(file_Name, file_Name_Without_CSV);
//printf("Path with out csv : %s\n", new_Path);
	//strcat(output_File, file_Name_Without_CSV);
	
    strcat(output_File, file_Name);
	strcat(output_File, "-sorted-");
	strcat(output_File, column);
	strcat(output_File, ".csv");

    
   
    if(((*(pRecordArray->pRecArray))->printing_Line) == NULL){
        return;
    }
    
    
	FILE * file = fopen(output_File, "w");
if(file == NULL ){
	fprintf(stderr, "Unable to open the output file.\n\n");
}

	//fprintf(file, "%s\n", pHeader->data);																										// Print header line

	//print all records
	int xyz;
	for (xyz = 0; xyz < pRecordArray->iSize; xyz++) {
		*((*(pRecordArray->pRecArray + xyz))->sorting_Key_Term) = (*(pRecordArray->pRecArray + xyz))->chHold;		// Put back the char set to '\0' for sorting key
		fprintf(file, "%s\n", (*(pRecordArray->pRecArray + xyz))->printing_Line);													// Print Records in a loop
	}
free(output_File);
free(file_Name);
	return;
}
