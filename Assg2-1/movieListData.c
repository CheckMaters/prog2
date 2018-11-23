#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "generalFunctions.h"
#include "columnsorter.h"
#include "movieListData.h"
#include "hashTable.h"
#include "tokenizer.h"
#define TRUE				1
#define FALSE				0


/*
This function creates a list of movie
where each pointer is movie with list of
values attached to it.
one_Movie_Values pointer is point to a specific
movie with linked list of values attached to it

This function also reads the type of the input value
of each values attached to that movie.
*/
one_Movie_Values* make_Movie_Value_List(char* movie_Line, sorting_Column_Info* column_Information, header_Struct ** struct_Pointer_Header, int no_Of_Columns_In_Header) {

		one_Movie_Values * temp_Pointer_To_Movie = (one_Movie_Values*)malloc(sizeof(one_Movie_Values) + strlen(movie_Line));
		strcpy(temp_Pointer_To_Movie->recordData, movie_Line);						//copying the line from the file to temporary pointer
	
        // Find sorting key
	   if (temp_Pointer_To_Movie != NULL) {
           
           
         //checking if the no. of columns in this movie is equal to the number of columns in the header line  
           Tokenizer check_No_Of_Col_Tok;
           char * check_No_Of_Col_Word;
           initialize_Tokenizer(&check_No_Of_Col_Tok, movie_Line, ',', '\"');
           check_No_Of_Col_Word = getNextToken(&check_No_Of_Col_Tok);
           int no_Of_Col_In_Movie = 0;

           while(check_No_Of_Col_Word != NULL) {	
               // Key and token are not equal. Continue loop
               no_Of_Col_In_Movie++;
               check_No_Of_Col_Word = getNextToken(&check_No_Of_Col_Tok);
		 	   
		   }
           
printf("\n\nThis is the number of columns in header line - %d\n", no_Of_Columns_In_Header); 
printf("This is the number of columns in MOVIE LINE - %d\n\n\n", no_Of_Col_In_Movie);
           //this means one of the movie in the file has more/less columns than the header line
           if(no_Of_Col_In_Movie != no_Of_Columns_In_Header){
               fprintf(stderr,"Error! Number of columns in header and Number of columns in a movie don't match.\n");
               return NULL;
           }
           
           
           
           
           
		  Tokenizer temp_Word;
		  initialize_Tokenizer(&temp_Word, movie_Line, ',', '\"');

		  char* bufferStart = movie_Line;				 // Pointer movie_Line will move along the string. Remember the start here.
           char* temp_Word_Token;
           
           temp_Word_Token = getNextToken(&temp_Word);
           int index = 0;
		//
		  while(column_Information->index > index) {														// Go to (column_Information->index)th field, which is the sorting column word
			// Key and token are not equal. Continue loop
                temp_Word_Token = getNextToken(&temp_Word);
                index++;
		  }

           
		  int offset;
		  int length;																						// Length of the column word
		  if (temp_Word_Token == NULL) {
              offset = strlen(temp_Pointer_To_Movie->recordData);
              length = 0;
		  }
		  else {
              offset = temp_Word_Token - bufferStart;
              length = strlen(temp_Word_Token);
		  }
		
           
		  temp_Pointer_To_Movie->sorting_Key = temp_Pointer_To_Movie->recordData + offset;
		  temp_Pointer_To_Movie->sorting_Key_Term = temp_Pointer_To_Movie->recordData + offset + length;
		  temp_Pointer_To_Movie->chHold = *temp_Pointer_To_Movie->sorting_Key_Term;									// Remember the char at  temp_Pointer_To_Movie->sorting_Key_Term (to be reset later)
		  *temp_Pointer_To_Movie->sorting_Key_Term = '\0';															// Set temp_Pointer_To_Movie->sorting_Key_Term to null. Now temp_Pointer_To_Movie->pSKey is a proper string
		
           
		  temp_Pointer_To_Movie->long_Integer_Value = 0L;																			// Trying to change into long
		  temp_Pointer_To_Movie->floating_Value = 0.0f;																		// Trying to change into float
		  char	cTemp;
		
           
           if (length > 0) {
                    char* pDot = strchr(temp_Pointer_To_Movie->sorting_Key, '.');

			     if (column_Information->index_Type_SIF == INDEX_TYPE_INTEGER) {
                        if (!pDot && sscanf(temp_Pointer_To_Movie->sorting_Key, "%ld%c", &(temp_Pointer_To_Movie->long_Integer_Value), &cTemp) == 1) {				// integer
                                temp_Pointer_To_Movie->floating_Value = temp_Pointer_To_Movie->long_Integer_Value;
                        }
                        else if (pDot && sscanf(temp_Pointer_To_Movie->sorting_Key, "%f%c", &(temp_Pointer_To_Movie->floating_Value), &cTemp) == 1) {			// float
                                column_Information->index_Type_SIF = INDEX_TYPE_FLOAT;
                        }
                        else {
                     column_Information->index_Type_SIF = INDEX_TYPE_STRING;
                        }
                 }
                 else if (column_Information->index_Type_SIF == INDEX_TYPE_FLOAT) {
                        if (!pDot && sscanf(temp_Pointer_To_Movie->sorting_Key, "%ld%c", &(temp_Pointer_To_Movie->long_Integer_Value), &cTemp) == 1) {
                                temp_Pointer_To_Movie->floating_Value = temp_Pointer_To_Movie->long_Integer_Value;
                        }
                        else if (pDot && sscanf(temp_Pointer_To_Movie->sorting_Key, "%f%c", &(temp_Pointer_To_Movie->floating_Value), &cTemp) == 1) {

                        }
				        else {
                                column_Information->index_Type_SIF = INDEX_TYPE_STRING;
				        }
                 }
                else {

                }
           }
        
           
           
        //this array pointer will keep all the column values of a movie   
        char ** list_Of_Given_Column = (char **) malloc (sizeof(char *) * no_Of_Col_In_Movie);
        char ** column_Value_Array = (char **) malloc (sizeof(char *) * 28);
        int temp_Loop = 0;
        while (temp_Loop < 28){
            *(column_Value_Array + temp_Loop) = NULL;
            temp_Loop++;
        }
           
           if(list_Of_Given_Column == NULL || column_Value_Array == NULL){
               fprintf(stderr, "Error! Unable to allocate memory.\n");
               return NULL;
           }
        
        Tokenizer temp_Word_Two;
        initialize_Tokenizer(&temp_Word_Two, movie_Line, ',', '\"');
        char * temp_Word_Two_Token;

//this populatest the array with all the column values of movies
        int temp_Count = 0;
        while (temp_Word_Two_Token != NULL) {
            temp_Word_Two_Token = getNextToken(&temp_Word_Two);
            *(list_Of_Given_Column + temp_Count) = (char *) malloc (sizeof(char) * strlen(temp_Word_Two_Token));
            strcpy(*(list_Of_Given_Column + temp_Count), temp_Word_Two_Token);
            *(column_Value_Array + (*(struct_Pointer_Header + temp_Count))->index) = (char *) malloc (sizeof(char) * strlen(*(list_Of_Given_Column + temp_Count)));
            strcpy(*(column_Value_Array + (*(struct_Pointer_Header + temp_Count))->index), *(list_Of_Given_Column + temp_Count));
            temp_Count++;
        }
            if(*(list_Of_Given_Column + 0) == NULL){
                temp_Pointer_To_Movie->printing_Line = (char *) malloc (sizeof(char) * 4);
                temp_Pointer_To_Movie->printing_Line = "null";
            }
        else {
            temp_Pointer_To_Movie->printing_Line = (char *) malloc (sizeof(char) * strlen(*(list_Of_Given_Column + 0)));
            strcat(temp_Pointer_To_Movie->printing_Line, *(list_Of_Given_Column + 0));
        }
        int temp_p = 1;
        while (temp_p < 27){
            if(*(list_Of_Given_Column + temp_p) == NULL){
                temp_Pointer_To_Movie->printing_Line = realloc(temp_Pointer_To_Movie->printing_Line, 4);
                strcat(temp_Pointer_To_Movie->printing_Line, "null");
                temp_p++;
            }
            else {
                temp_Pointer_To_Movie->printing_Line = realloc(temp_Pointer_To_Movie->printing_Line, strlen(*(list_Of_Given_Column + temp_p)));
                strcat(temp_Pointer_To_Movie->printing_Line, *(list_Of_Given_Column + temp_p));
                temp_p++;
            }
        }
        if(*(list_Of_Given_Column + 27) == NULL){
                temp_Pointer_To_Movie->printing_Line = realloc(temp_Pointer_To_Movie->printing_Line, 4);
                strcat(temp_Pointer_To_Movie->printing_Line, "null");
            }
        else {
            temp_Pointer_To_Movie->printing_Line = realloc(temp_Pointer_To_Movie->printing_Line, strlen(*(list_Of_Given_Column + 27)));
            strcat(temp_Pointer_To_Movie->printing_Line, *(list_Of_Given_Column + 27));
        }
	}
    
    printf("This is a line - %s\n", temp_Pointer_To_Movie->printing_Line);
    
	return temp_Pointer_To_Movie;
}



int compare(void* pData1, void* pData2, void* pHint) {
	one_Movie_Values* pRecord1 = (one_Movie_Values*)pData1;
	one_Movie_Values* pRecord2 = (one_Movie_Values*)pData2;

	int end_Result;			//return result, will change accordingly

	sorting_Column_Info* column_Information = (sorting_Column_Info*)pHint;
	int index_Type_SIF = column_Information->index_Type_SIF;

	int len1 = strlen(pRecord1->sorting_Key);
	int len2 = strlen(pRecord2->sorting_Key);
	if (len1 == 0 && len2 > 0) {
		end_Result = -1;
	}
	else if (len1 > 0 && len2 == 0) {
		end_Result = 1;
	}
	else if (len1 == 0 && len2 == 0) {
		end_Result = 0;
	}
	else {
		long 	ldelta;
		float fdelta;
		switch(index_Type_SIF) {
			case INDEX_TYPE_INTEGER:
				ldelta = pRecord1->long_Integer_Value - pRecord2->long_Integer_Value;
				if (ldelta == 0L) {
					end_Result = 0;
				}
				else if (ldelta > 0L) {
					end_Result = 1;
				}
				else {
					end_Result = -1;
				}
				break;

			case INDEX_TYPE_FLOAT :
				fdelta = pRecord1->floating_Value - pRecord2->floating_Value;
				if (fdelta == 0.0) {
					end_Result = 0;
				}
				else if (fdelta > 0.0) {
					end_Result = 1;
				}
				else {
					end_Result = -1;
				}
				break;

		   default :
				end_Result = strcicmp(pRecord1->sorting_Key, pRecord2->sorting_Key);
				break;
		}
	}
	return end_Result;
}
