#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hash_Struct {
    char * column_Name;
    char  * column_Value;
    int index;
    struct hash_Struct * next;
} hash_Struct;

void * create_Hash_Table (hash_Struct * hash_Table);


#endif