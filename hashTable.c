#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"


//this function will create a hash table with known 28 column names
//in order to get the hash key divide the int value of char * with 28
void * create_Hash_Table (hash_Struct * hash_Table){
    (hash_Table + 0)->column_Name = (char *) malloc (sizeof(char) * strlen("director_name"));
    strcpy((hash_Table + 0)->column_Name, "director_name");
    (hash_Table + 0)->index = 1;
    (hash_Table + 0)->column_Value = NULL;
    
        hash_Struct * ptr1 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr1->column_Name = (char *)malloc (sizeof(char) * strlen("director_facebook_likes"));
        strcpy(ptr1->column_Name, "director_facebook_likes");
        ptr1->index = 4;
        ptr1->column_Value = NULL;
            
        hash_Table->next = ptr1;        //adding the chains to the hash table
        
            hash_Struct * ptr2 = (hash_Struct*) malloc (sizeof(hash_Struct));
            ptr2->column_Name = (char *) malloc (sizeof(char) * strlen("language"));
            strcpy(ptr2->column_Name, "language");
            ptr2->index = 19;
            ptr2->column_Value = NULL;
        
            ptr1->next = ptr2;
            
                hash_Struct * ptr3 = (hash_Struct*) malloc (sizeof(hash_Struct));
                ptr3->column_Name = (char *) malloc (sizeof(char) * strlen("title_year"));
                strcpy(ptr3->column_Name, "title_year");
                ptr3->index = 23;
                ptr3->column_Value = NULL;
                ptr3->next = NULL;
    
                ptr2->next = ptr3;
    
    (hash_Table + 1)->column_Name = (char *) malloc (sizeof(char) * strlen("actor_2_name"));
    strcpy((hash_Table + 1)->column_Name, "actor_2_name");
    (hash_Table + 1)->index = 6;
    (hash_Table + 1)->column_Value = NULL;
    
        hash_Struct * ptr4 = (hash_Struct *) malloc (sizeof(hash_Struct));
        ptr4->column_Name = (char *) malloc (sizeof(char) * strlen("movie_title"));
        strcpy(ptr4->column_Name, "movie_title");
        ptr4->index = 11;
        ptr4->column_Value = NULL;
        
        (hash_Table + 1)->next = ptr4;
            
            hash_Struct * ptr5 = (hash_Struct*) malloc (sizeof(hash_Struct));
            ptr5->column_Name = (char *) malloc (sizeof(char) * strlen("actor_2_facebook_likes"));
            strcpy(ptr5->column_Name, "actor_2_facebook_likes");
            ptr5->index = 24;
            ptr5->column_Value = NULL;
            ptr5->next = NULL;
        
            ptr4->next = ptr5;
    
    (hash_Table + 4)->column_Name = (char *) malloc (sizeof(char) * strlen("duration"));
    strcpy((hash_Table + 4)->column_Name, "duration");
    (hash_Table + 4)->index = 3;
    (hash_Table + 4)->column_Value = NULL;
    (hash_Table + 4)->next = NULL;
    
    (hash_Table + 9)->column_Name = (char *) malloc (sizeof(char) * strlen("actor_3_facebook_likes"));
    strcpy((hash_Table + 9)->column_Name, "actor_3_facebook_likes");
    (hash_Table + 9)->index = 5;
    (hash_Table + 9)->column_Value = NULL;
    
        hash_Struct * ptr6 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr6->column_Name = (char *) malloc (sizeof(char) * strlen("actor_3_name"));
        strcpy(ptr6->column_Name, "actor_3_name");
        ptr6->index = 14;
        ptr6->column_Value = NULL;
        ptr6->next = NULL;
        
        (hash_Table + 9)->next = ptr6;
    
    
    (hash_Table  + 11)->column_Name = (char *) malloc (sizeof(char) * strlen("cast_total_facebook_likes"));
    strcpy((hash_Table  + 11)->column_Name, "cast_total_facebook_likes");
    (hash_Table  + 11)->index = 13;
    (hash_Table  + 11)->column_Value = NULL;
            
        hash_Struct * ptr7 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr7->column_Name = (char *) malloc (sizeof(char) * strlen("content_rating"));
        strcpy(ptr7->column_Name, "content_rating");
        ptr7->index = 21;
        ptr7->column_Value = NULL;
        ptr7->next = NULL;
        
        (hash_Table + 11)->next = ptr7;
    
    (hash_Table + 13)->column_Name = (char *) malloc (sizeof(char) * strlen("movie_imdb_link"));
    strcpy((hash_Table + 13)->column_Name, "movie_imdb_link");
    (hash_Table + 13)->index = 17;
    (hash_Table + 13)->column_Value = NULL;
    (hash_Table + 13)->next = NULL;
    
    (hash_Table + 15)->column_Name = (char *) malloc (sizeof(char) * strlen("gross"));
    strcpy((hash_Table + 15)->column_Name, "gross");
    (hash_Table + 15)->index = 8;
    (hash_Table + 15)->column_Value = NULL;
    (hash_Table + 15)->next = NULL;
    
    (hash_Table + 17)->column_Name = (char *) malloc (sizeof(char) * strlen("aspect_ratio"));
    strcpy((hash_Table + 17)->column_Name, "aspect_ratio");
    (hash_Table + 17)->index = 26;
    (hash_Table + 17)->column_Value = NULL;
    (hash_Table + 17)->next = NULL;
    
    (hash_Table + 18)->column_Name = (char *) malloc (sizeof(char) * strlen("facenumber_in_poster"));
    strcpy((hash_Table + 18)->column_Name, "facenumber_in_poster");
    (hash_Table + 18)->index = 15;
    (hash_Table + 18)->column_Value = NULL;
        
        hash_Struct * ptr8 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr8->column_Name = (char *) malloc (sizeof(char) * strlen("num_user_for_reviews"));
        strcpy(ptr8->column_Name, "num_user_for_reviews");
        ptr8->index = 18;
        ptr8->column_Value = NULL;
        ptr8->next = NULL;
    
        (hash_Table + 18)->next = ptr8;
    
    
    (hash_Table + 21)->column_Name = (char *) malloc (sizeof(char) * strlen("actor_1_facebook_likes"));
    strcpy((hash_Table + 21)->column_Name, "actor_1_facebook_likes");
    (hash_Table + 21)->index = 7;
    (hash_Table + 21)->column_Value = NULL;
        
        hash_Struct * ptr9 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr9->column_Name = (char *) malloc (sizeof(char) * strlen("actor_1_name"));
        strcpy(ptr9->column_Name, "actor_1_name");
        ptr9->index = 10;
        ptr9->column_Value = NULL;
        ptr9->next = NULL;
    
        (hash_Table + 21)->next = ptr9;
    
    
    
    (hash_Table + 22)->column_Name = (char *) malloc (sizeof(char) * strlen("budget"));
    strcpy((hash_Table + 22)->column_Name, "budget");
    (hash_Table + 22)->index = 22;
    (hash_Table + 22)->column_Value = NULL;
    (hash_Table + 22)->next = NULL;
    
    
    (hash_Table + 23)->column_Name = (char *) malloc (sizeof(char) * strlen("genres"));
    strcpy((hash_Table + 23)->column_Name, "genres");
    (hash_Table + 23)->index = 9;
    (hash_Table + 23)->column_Value = NULL;
    (hash_Table + 23)->next = NULL;
    
    
    (hash_Table + 24)->column_Name = (char *) malloc (sizeof(char) * strlen("plot_keywords"));
    strcpy((hash_Table + 24)->column_Name, "plot_keywords");
    (hash_Table + 24)->index = 16;
    (hash_Table + 24)->column_Value = NULL;
    (hash_Table + 24)->next = NULL;
    
    
    (hash_Table + 25)->column_Name = (char *) malloc (sizeof(char) * strlen("imdb_score"));
    strcpy((hash_Table + 25)->column_Name, "imdb_score");
    (hash_Table + 25)->index = 25;
    (hash_Table + 25)->column_Value = NULL;
    
        hash_Struct * ptr10 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr10->column_Name = (char *) malloc (sizeof(char) * strlen("movie_facebook_likes"));
        strcpy(ptr10->column_Name, "movie_facebook_likes");
        ptr10->index = 27;
        ptr10->column_Value = NULL;
        ptr10->next = NULL;
        
        (hash_Table + 25)->next = ptr10;
    
    
    (hash_Table + 26)->column_Name = (char *) malloc (sizeof(char) * strlen("num_critic_for_reviews"));
    strcpy((hash_Table + 26)->column_Name, "num_critic_for_reviews");
    (hash_Table + 26)->index = 2;
    (hash_Table + 26)->column_Value = NULL;
    
        hash_Struct * ptr11 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr11->column_Name = (char *) malloc (sizeof(char) * strlen("num_voted_users"));
        strcpy(ptr11->column_Name, "num_voted_users");
        ptr11->index = 12;
        ptr11->column_Value = NULL;
        ptr11->next = NULL;
    
        (hash_Table + 26)->next = ptr11;
    
    
    (hash_Table + 27)->column_Name = (char *) malloc (sizeof(char) * strlen("color"));
    strcpy((hash_Table + 27)->column_Name, "color");
    (hash_Table + 27)->index = 0;
    (hash_Table + 27)->column_Value = NULL;
    
        hash_Struct * ptr12 = (hash_Struct*) malloc (sizeof(hash_Struct));
        ptr12->column_Name = (char *) malloc (sizeof(char) * strlen("country"));
        strcpy(ptr12->column_Name, "country");
        ptr12->index = 20;
        ptr12->column_Value = NULL;
        ptr12->next = NULL;
        
        (hash_Table + 27)->next = ptr12;
    
    
    (hash_Table + 2)->index = -1;
    (hash_Table + 3)->index = -1;
    (hash_Table + 5)->index = -1;
    (hash_Table + 6)->index = -1;
    (hash_Table + 7)->index = -1;
    (hash_Table + 8)->index = -1;
    (hash_Table + 10)->index = -1;
    (hash_Table + 12)->index = -1;
    (hash_Table + 14)->index = -1;
    (hash_Table + 16)->index = -1;
    (hash_Table + 19)->index = -1;
    (hash_Table + 20)->index = -1;
    
    
    
    return NULL;
}
