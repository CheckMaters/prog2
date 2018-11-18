#ifndef RECORD_H
#define RECORD_H

// Data for one movie record
// It holds one line in the csv file, and its sorting key, which could be long, float or string.
typedef struct one_Movie_Values {
	char			chHold;						// Hold the char for *sorting_Key_Term
	long 			long_Integer_Value;							// integer
	float			floating_Value;						// floating point number
	char* 		sorting_Key;						// Pointer to sorting key in recordData
	char*		sorting_Key_Term;
	char 			recordData[1];
    char            printingLine[1];
} one_Movie_Values;


typedef struct header_Struct {
    char * column_Name;
    int index;
}header_Struct;

int compare(void* pData1, void* pData2, void* pHint);
one_Movie_Values* make_Movie_Value_List(char* buffer, sorting_Column_Info* pcolumn_Info, header_Struct * struct_Pointer_Header, int no_Of_Columns_In_Header);



#endif
