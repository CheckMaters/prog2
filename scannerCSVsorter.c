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
#include "scannerCSVsorter.h"
#include "tokenizer.h"
#include <sys/wait.h>
#include <pthread.h>
#define TRUE				1
#define FALSE				0

char* directory_Char; // char directory_Char[3000];
char* output_Place; //was char output_Place[100];
char* sort_By_This_Value;
DIR * directory;
DIR * output_place;
int return_Val_For_Main;
int parents_PID;
int total_threads=1;

/*
void* thread_function(void* arg) {
	
	total_threads += 1;
	
	int compare = scan_Directory(directory, sort_By_This_Value, directory_Char, output_Place);
	
	printf("%d", compare);	
	
	pthread_exit(0);
}

*/

typedef struct tid_struct{
	
	unsigned long long int tid;
	struct tid_struct* next;
	
}tidstruct;

tidstruct * head;
//head = malloc(sizeof(tidstruct));


int main(int argc, char* argv[]) {
	//checking if the input argument is correct or Not
return_Val_For_Main = -1;
parents_PID = getpid();
head = NULL;

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
			
			directory_Char = ".";
			output_Place = ".";
			
			/*
			this will create a directory and also
			a struct that keeps all the information
			about directory.
			*/

			directory = opendir(directory_Char);

			if(directory == NULL) {
				fprintf(stderr, "Error! Unable to open current directory.\n");
				return -1;		//returning -1 because it's an error
			}

			sort_By_This_Value = argv[2];
			printf("Initial PID: %d\n", parents_PID);
	
			
			scan_Directory(directory_Char);
			//sending directory char for output path too, because output directory is not specified
			closedir(directory);


			
			return 0;
	}
	

	if(argc == 5) {

			if(strcmp("-c", argv[1]) == 0) {
				if(strcmp("-d", argv[3]) == 0) {
					//DIR * directory;
					directory = opendir(argv[4]);

					if(directory == NULL) {
						fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
						return -1;		//returning -1 because it's an error
					}

					sort_By_This_Value = argv[2];
					output_Place = argv[4];
					printf("Initial PID: %d\nPIDS of all child Processes: \n", parents_PID);
				

					scan_Directory(argv[4]);
					closedir(directory);

					
					return 0;

				}
				else if(strcmp("-o", argv[3]) == 0){
					//DIR * directory;
					directory = opendir("./");
					if(directory == NULL) {
						fprintf(stderr, "ERROR! Unable to open the current directory.\n");
						return -1;		//returning -1 because it's an error
					}
					DIR * output_Dir;
					output_Dir = opendir(argv[4]);
					if(output_Dir == NULL){
						fprintf(stderr, "ERROR! Given output directory is pointing to NULL\n");
						return -1;
					}
					else {
						closedir(output_Dir);
					}
					output_Place = argv[4];

					directory_Char = ".";
					sort_By_This_Value = argv[2];
					printf("Initial PID: %d\n", parents_PID);
					scan_Directory(directory_Char);
					closedir(directory);
					
					return 0;

				}
				else {
					fprintf(stderr, "Parameters are not correctly formated.\n");
					return -1;				//returning -1 because it's an error
				}
			}

			if(strcmp("-c", argv[3]) == 0){
				if(strcmp("-d", argv[1]) == 0) {
					//DIR * directory;
					directory = opendir(argv[2]);

					if(directory == NULL) {
						fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
						return -1;		//returning -1 because it's an error
					}

					sort_By_This_Value = argv[4];
					output_Place = argv[2];
	
					printf("Initial PID: %d\n", parents_PID);

					scan_Directory(argv[2]);
					closedir(directory);
					
					return 0;

				}
				else if(strcmp("-o", argv[1]) == 0){
					//DIR * directory;
					directory = opendir("./");
					if(directory == NULL) {
						fprintf(stderr, "ERROR! Unable to open the Current Directory.\n");
						return -1;		//returning -1 because it's an error
					}
					//DIR * output_place;
					output_place = opendir(argv[2]);
					if(output_place == NULL){
						fprintf(stderr, "ERROR! Given output directory is pointing to NULL.\n");
						return -1;
					}
					else {
						closedir(output_place);
					}
					directory_Char = ".";
					sort_By_This_Value = argv[4];
					printf("Initial PID: %d\n", parents_PID);
					scan_Directory(directory_Char);
					closedir(directory);
					
					return 0;
				}
				else {
					fprintf(stderr, "Parameters are not correctly formated.\n");
					return -1;				//returning -1 because it's an error
				}
			}

			else {
				fprintf(stderr, "Parameters are not correctly formated.\n");
				return -1;				//returning -1 because it's an error	
			}


	}


	if(argc == 7) {
			if(strcmp("-c", argv[1]) == 0){
				if(strcmp("-d", argv[3])==0 && strcmp("-o", argv[5]) == 0){

						//DIR * directory;
						directory = opendir(argv[4]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[2];

						char print_Here[strlen(argv[6] + 1)];  // CHECK THIS ONE NOT SURE IF IT HAS TO BE GLOBAL VARIABLE!!!!!
						strcpy(print_Here, argv[6]);

						output_place = opendir(print_Here); //Was a P instead of p before

						if(output_place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\n", parents_PID);


						scan_Directory(argv[4]);
						closedir(directory);
						
						return 0;

				}
				else if(strcmp("-o", argv[3])==0 && strcmp("-d", argv[5])==0){

						//DIR * directory;
						directory = opendir(argv[6]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[2];

						char print_Here[strlen(argv[4] + 1)]; //NOT SURE AGAIN!!!!!!!!!!!!!!!!!!!
						strcpy(print_Here, argv[4]);

						output_place = opendir(print_Here);
						if(output_place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\n", parents_PID);


						scan_Directory(argv[6]);
						closedir(directory);
						
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}
			}
			else if(strcmp("-c", argv[3])==0){
				if(strcmp("-d", argv[1])==0 && strcmp("-o", argv[5]) == 0){

						//DIR * directory;
						directory = opendir(argv[2]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[4];

						char print_Here[strlen(argv[6] + 1)];  //Not sure!!!!!!!!!!!
						strcpy(print_Here, argv[6]);

						output_place = opendir(print_Here);
						if(output_place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\n", parents_PID);


						scan_Directory(argv[2]);
						closedir(directory);
						
						return 0;

				}
				else if(strcmp("-o", argv[1])==0 && strcmp("-d", argv[5])==0){

						//DIR * directory;
						directory = opendir(argv[6]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[4];

						char print_Here[strlen(argv[2] + 1)];
						strcpy(print_Here, argv[2]);

						output_place = opendir(print_Here);
						if(output_place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\n", parents_PID);


						scan_Directory(argv[6]);
						closedir(directory);
						
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}

			}
			else if(strcmp("-c", argv[5])==0){
				if(strcmp("-d", argv[1])==0 && strcmp("-o", argv[3]) == 0){

						//DIR * directory;
						directory = opendir(argv[2]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[6];

						char print_Here[strlen(argv[4] + 1)];  // Dont know!!!!!
						strcpy(print_Here, argv[4]);

						output_place = opendir(print_Here);
						if(output_place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\n", parents_PID);


						scan_Directory(argv[2]);
						closedir(directory);
						
						return 0;

				}
				else if(strcmp("-o", argv[1])==0 && strcmp("-d", argv[3])==0){

						//DIR * directory;
						directory = opendir(argv[4]);

						if(directory == NULL) {
							fprintf(stderr, "ERROR! Given directory is pointing to NULL.\n");
							return -1;		//returning -1 because it's an error
						}

						sort_By_This_Value = argv[6];

						char print_Here[strlen(argv[2] + 1)]; //???????????????????????????
						strcpy(print_Here, argv[2]);

						output_place = opendir(print_Here);
						if(output_Place == NULL){
							fprintf(stderr, "Error! Given output directory is pointing to NULL.\n");
							return -1;
						}
						else {
							closedir(output_place);
						}

						printf("Initial PID: %d\nPIDS of all child Processes: ", parents_PID);


						scan_Directory(argv[4]);
						closedir(directory);
						
						return 0;

				}
				else {
					fprintf(stderr, "Error! Parameters are not correctly formated.\n");
					return -1;
				}

			}
			else {
				fprintf(stderr, "Parameters are not correctly formated\n");
				return -1;  			//returning -1 because it's an error
			}

	}
	else {
		fprintf(stderr, "Error! Parameters are not correctly formated.\n");
		return -1;
	}

//main method ends here
}	

	


/*
sort_The_List is the function that
is going to sort the stdin movie_List
file in alphabetical boreds. The column
that is going to be sorted is represented
by sort_By_This_Value.
*/
int sort_The_List(char* sort_By_This_Value, FILE* file, char * output_Dir, char * file_Name) {

	// Buffer for reading from stdin
	BUFFER read_File;																	// Buffer is created to read the stdin File
	BUFFER header_Of_File;																// For holding the header line


	FUNCTION_POINTER_CMPDATA pFuncCompare = compare;
	//Initializing Buffer to NULL and then will add data to it
	read_File.data = NULL;
	read_File.length_Of_Data = 0;

	int output_Result = 1;			//setting the output result to 1 in the beginning

	sorting_Column_Info column_Info;						//this will hold info regarding the column's type and index no.
	column_Info.index = -1;
	column_Info.index_Type_SIF = INDEX_TYPE_INTEGER;
					/*
					the type of column to sort is set to integer First
					and will be changed according later in the function
					if necessary
					*/



	// To hold movie list array
	movie_Record movie_List;

	//Intializing movie_Record named movie_List
	movie_List.pRecArray = (one_Movie_Values**) malloc (1024 * sizeof(one_Movie_Values*));
	movie_List.iCapacity = 1024;
	movie_List.iSize = 0;
	//int no_Use = 0;
		// Read the header and get the index for the sorting key
		if (getline(&(read_File.data), &(read_File.length_Of_Data), file) > 0 ) {
			delete_Newline_Char_At_The_End(&read_File);						// this will delete the new line character from the end of the string line

			header_Of_File.data = (char*)malloc (sizeof(char) * read_File.length_Of_Data);
			header_Of_File.length_Of_Data = read_File.length_Of_Data;





			strcpy(header_Of_File.data, read_File.data);			// copy of header line before tokenizing
			//head_Of_File keeps record of the first line that is that name of all the columns

			if (get_Column_Index_To_Sort_List(sort_By_This_Value, &column_Info, read_File.data)) {
							fprintf(stderr, "Error! Unable to parse the input column name\n");
						}
						else {
				// Read data line by line. Creates record and put them into array
				while (getline(&(read_File.data), &(read_File.length_Of_Data), file) > 0) {
					delete_Newline_Char_At_The_End(&read_File);

					one_Movie_Values* pRecord = make_Movie_Value_List(read_File.data, &column_Info);
					if (pRecord) {
						add_One_Movie_To_The_List(&movie_List, pRecord);
					}
					else {
						fprintf(stderr, "Error! Unable to create movie list!\n");
					}
		}
				/*
				merge sort will sort the array of movie list based
				on the index type and column name entered in the
				command prompt
				*/
				mergeSort((void**)movie_List.pRecArray, 0, movie_List.iSize - 1, &column_Info, pFuncCompare);
				// Output sorted records to file
			//	printf("sorted\n");

				print_The_List(&header_Of_File, &movie_List, output_Dir, file_Name, sort_By_This_Value);
				 output_Result = 0;
		}
	}
		else {
			fprintf(stderr, "Error! Unable to read file provided within directory. Please check file or directory\n");
		}

	freeBuffer(&header_Of_File);
	freeBuffer(&read_File);
	if (movie_List.pRecArray != NULL) {
		clearMovieList(&movie_List);
	}


	return output_Result;
}





//this checks if the given char string is directory or not
int is_Directory(const char * name) {
	DIR * temp_dir = opendir(name);
	if (temp_dir != NULL){
		closedir(temp_dir);
		return 0;	//returns 0 if it's directory, else -1
	}
	return -1;
}


//this checks if the given char string is CSV file or not
int is_CSV_File (const char * name, char * column) {

//printf("CHECKING THIS FILE : %s with this column %s\n\n", name, column);
	char test_Name[strlen(column) + 4];
	//char * test_Name = (char *) malloc ((strlen(column) + 5)* sizeof(char));
	strncpy(test_Name, column, strlen(column));
	strcat(test_Name, ".csv");

//printf("this is what we are checking : %s\n\n", test_Name);

	if((strlen(name) > (strlen(column) + 4)) && !(strcmp(name + strlen(name) - (strlen(column) + 4), test_Name))){
	//	free(test_Name);
		fprintf(stderr, "Error! This file is already sorted by the sorted\n");
		return -1;		//returning -1 because this file is already sorted
	}

	if(strlen(name) > 4 && !(strcmp(name + strlen(name) - 4, ".csv"))){
		//free(test_Name);
		return 0;			//returns 0 if it's csv file, else -1
	}

	fprintf(stderr, "Error! This isn't a CSV file!\n");
	//free(test_Name);
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
//int scan_Directory(DIR * directory, char * sorting_Column, char * path, char * output_Directory){

void * scan_Directory(void * thepath){
	printf("%shello\n",(char*)thepath);
	directory = opendir((char*)thepath);

	/*
	if(directory == NULL){
		fprintf(stderr, "Error! Unable to open directory. NULL pointer\n");
		return -1;			//returning -1 because it is an error
	}
	*/

	//setting this value to an unusal value so that if later program breaks, we can check if this value changes or not
	//int return_Value = -500;
	
	struct dirent * directory_Info;
	char current_dir_path[strlen((char*)thepath) + 1];
	strcpy(current_dir_path, (char*)thepath);
	
	while ((directory_Info = readdir(directory))!= NULL){
		//printf("%s\n",directory_Char);
		//Thread id
		printf("%s d name outside loop\n",directory_Info->d_name);		
		pthread_t tid;
		
		pthread_attr_t attr;
		pthread_create(&tid, &attr, scan_Directory, (char*) thepath); 

		tidstruct * name;
		name = malloc(sizeof(tidstruct));	
		name->tid = pthread_self();
		if (head == NULL){
			head = name;
		} else {
			name->next = head;
			head = name;
		}
		
		if((strcmp(directory_Info->d_name, ".") == 0) || (strcmp(directory_Info->d_name, "..") == 0)){
			printf("%sthe d_name\n",directory_Info->d_name);			
			//pthread_exit(0);
			continue;	
		}
		printf("%ssdfasdfsdf\n",directory_Char);
		thepath = strcat(thepath, "/");
		thepath = strcat(thepath, directory_Info->d_name);
		//checks if the current file that file pointer points to is a directory or not
		int return_Value = is_Directory(thepath);

		/*
		if return value is zero, it means this is directory
		and will perform recurssion from this point on that
		sub-directory
		*/

		pthread_t tid2;
		pthread_attr_t attr2;
                pthread_create(&tid2, &attr2, scan_Directory((void*)thepath), NULL);

                tidstruct * name2;
		name2 =  malloc(sizeof(tidstruct));
            	name->tid = pthread_self();

                if (head == NULL){
	                head = name2;
                } else {
                        name2->next = head;
                        head = name2;
                }

		if(return_Value == 0) {
			//**************this means it is directory, perform recurssion*****************
		
			strcpy(current_dir_path, thepath);	//changing the current path for child process as it is going to be at sub directory level
			directory = opendir(thepath);	//changing directory to sub directory for child process
			pthread_t tid2;
		
			pthread_attr_t attr2;
			pthread_create(&tid2, &attr2, scan_Directory((void*)thepath), NULL);
			
			tidstruct * name2;
			name2 =  malloc(sizeof(tidstruct));	
			name->tid = pthread_self();
			
			if (head == NULL){
				head = name2;
			} else {
				name2->next = head;
				head = name2;
			}
			
		} else {
			
			int return_Value = is_CSV_File(thepath, sort_By_This_Value);
			if(return_Value == 0){
				//************this means it is CSV file, perform sorting******************
				
				

				FILE * file = fopen(thepath, "r");
				return_Value = sort_The_List(sort_By_This_Value, file, output_Place, directory_Info->d_name);
				fclose(file);	
				
			} else {
				//printf("%s is not a csv file or directory\n", path);
				strcpy(thepath, current_dir_path);
				pthread_exit(0); //continuing to the next loop because read value isn't directory or CSV file
			}
		}

	}
		



		// if the read value is not directory, check if it's CSV file or not

	strcpy(thepath,current_dir_path);	//changing directory/file1 to directory, because we are at same level but just looping to next file
	
	//printf("%d",return_Value);
	pthread_exit(0);
}


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
void print_The_List(BUFFER* pHeader, movie_Record* pRecordArray, char * path, char * file_Name, char * column) {



	char * output_File = (char * ) calloc ((strlen(path) + strlen(column) + 9 + strlen(file_Name)) , sizeof(char));
	if (strcmp(path + strlen(path) - 4, ".csv") == 0){
		strncpy(output_File, path, strlen(path) - strlen(file_Name));

	}
	 else if(strcmp (path + strlen(path) -1, "/") != 0){
		strcat(path, "/");
		strcpy(output_File, path);

	}

printf("\n\nOUTPUT path : %s\n\n", path);

	//printf("Directory : %s\n\n\n", output_File);
	char * file_Name_Without_CSV = (char * ) malloc ( (strlen(file_Name)-3)  * sizeof(char) );
	remove_CSV(file_Name, file_Name_Without_CSV);
//printf("Path with out csv : %s\n", new_Path);
	strcat(output_File, file_Name_Without_CSV);
	//strcat(output_File, file_Name);
	strcat(output_File, "-sorted-");
	strcat(output_File, column);
	strcat(output_File, ".csv");

	FILE * file = fopen(output_File, "w");
	if(file == NULL ){
		fprintf(stderr, "Unable to open the output file.\n\n");
	}

	fprintf(file, "%s\n", pHeader->data); // Print header line

	//print all records
	int xyz;
	for (xyz = 0; xyz < pRecordArray->iSize; xyz++) {
		*((*(pRecordArray->pRecArray + xyz))->sorting_Key_Term) = (*(pRecordArray->pRecArray + xyz))->chHold;		// Put back the char set to '\0' for sorting key
		fprintf(file, "%s\n", (*(pRecordArray->pRecArray + xyz))->recordData);					// Print Records in a loop
	}
	free(output_File);
	free(file_Name_Without_CSV);
	return;
}
