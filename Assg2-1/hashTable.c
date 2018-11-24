#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

void ** create_Hash_Table (hash_Struct ** hash_Table){

    hash_Struct * temp1 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //(hash_Table + 27)->column_Name = (char *) malloc (sizeof(char) * strlen("color"));
    strcpy(temp1->column_Name, "color");
    temp1->index = 0;
    temp1->column_Value = NULL;
    *(hash_Table + 0) = temp1;
    
    
    hash_Struct * temp2 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //(hash_Table + 15)->column_Name = (char *) malloc (sizeof(char) * strlen("gross"));
    strcpy(temp2->column_Name, "gross");
    temp2->index = 8;
    temp2->column_Value = NULL;
    temp2->next = NULL;
    *(hash_Table + 2) = temp2;
    
    
        hash_Struct * ptr1 = (hash_Struct*) malloc (sizeof(hash_Struct));
        //ptr1->column_Name = (char *) malloc (sizeof(char) * strlen("content_rating"));
        strcpy(ptr1->column_Name, "content_rating");
        ptr1->index = 21;
        ptr1->column_Value = NULL;
        
        temp2->next = ptr1;
    
    
        hash_Struct * ptr2 = (hash_Struct*) malloc (sizeof(hash_Struct));
        //ptr2->column_Name = (char *) malloc (sizeof(char) * strlen("imdb_score"));
        strcpy(ptr2->column_Name, "imdb_score");
        ptr2->index = 25;
        ptr2->column_Value = NULL;
        ptr2->next = NULL;
        
        ptr1->next = ptr7;
    
    
    hash_Struct * temp3 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp3->column_Name = (char *)malloc (sizeof(char) * strlen("director_facebook_likes"));
    strcpy(temp3->column_Name, "director_facebook_likes");
    temp3->index = 4;
    temp3->column_Value = NULL;
    temp3->next = NULL;
    *(hash_Table + 3) = temp3;
    
    
    hash_Struct * temp4 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //temp4->column_Name = (char *) malloc (sizeof(char) * strlen("facenumber_in_poster"));
    strcpy(temp4->column_Name, "facenumber_in_poster");
    temp4->index = 15;
    temp4->column_Value = NULL;
    temp4->next = NULL;
    *(hash_Table + 4) = temp9;
    
    
    hash_Struct * temp5 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp5->column_Name = (char *) malloc (sizeof(char) * strlen("num_voted_users"));
    strcpy(temp5->column_Name, "num_voted_users");
    temp5->index = 12;
    temp5->column_Value = NULL;
    temp5->next = NULL;
    *(hash_Table + 5) = temp5;
    
    
    hash_Struct * temp6 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //temp6->column_Name = (char *) malloc (sizeof(char) * strlen("actor_1_facebook_likes"));
    strcpy(temp6->column_Name, "actor_1_facebook_likes");
    temp6->index = 7;
    temp6->column_Value = NULL;
    *(hash_Table + 7) = temp6; 
    
    
    
            hash_Struct * ptr3 = (hash_Struct*) malloc (sizeof(hash_Struct));
            //ptr5->column_Name = (char *) malloc (sizeof(char) * strlen("actor_2_facebook_likes"));
            strcpy(ptr3->column_Name, "actor_2_facebook_likes");
            ptr3->index = 24;
            ptr3->column_Value = NULL;
            ptr3->next = NULL;
        
            temp6->next = ptr3;
    
    
    hash_Struct * temp7 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp7->column_Name = (char *) malloc (sizeof(char) * strlen("actor_1_name"));
    strcpy(temp7->column_Name, "actor_1_name");
    temp7->index = 10;
    temp7->column_Value = NULL;
    temp7->next = NULL;
    *(hash_Table + 8) = temp7;
    
    
    hash_Struct * temp8 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //temp8->column_Name = (char *) malloc (sizeof(char) * strlen("movie_imdb_link"));
    strcpy(temp8->column_Name, "movie_imdb_link");
    temp8->index = 17;
    temp8->column_Value = NULL;
    temp8->next = NULL;
    *(hash_Table + 11) = temp6;
    
    
    hash_Struct * temp9 = (hash_Struct *) malloc (sizeof(hash_Struct));
    strcpy(temp9->column_Name, "director_name");
    temp9->index = 1;
    temp9->column_Value = NULL;
    *(hash_Table + 13) = temp1;
    
    
            hash_Struct * ptr4 = (hash_Struct*) malloc (sizeof(hash_Struct));
            //ptr4->column_Name = (char *) malloc (sizeof(char) * strlen("language"));
            strcpy(ptr4->column_Name, "language");
            ptr4->index = 19;
            ptr4->column_Value = NULL;
        
            temp9->next = ptr4;
            
    
            hash_Struct * ptr5 = (hash_Struct *) malloc (sizeof(hash_Struct));
            //ptr5->column_Name = (char *) malloc (sizeof(char) * strlen("aspect_ratio"));
            strcpy(ptr5->column_Name, "aspect_ratio");
            ptr5->index = 26;
            ptr5->column_Value = NULL;
            ptr5->next = NULL;
            
            ptr4->next = ptr5;
    
    hash_Struct * temp10 = (hash_Struct *) malloc (sizeof(hash_Struct));
    // temp10->column_Name = (char *) malloc (sizeof(char) * strlen("budget"));
    strcpy(temp10->column_Name, "budget");
    temp10->index = 22;
    temp10->column_Value = NULL;
    temp10->next = NULL;
    *(hash_Table + 17) = temp10;
    
    
    
    hash_Struct * temp11 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp11->column_Name = (char *) malloc (sizeof(char) * strlen("actor_3_name"));
    strcpy(temp11->column_Name, "actor_3_name");
    temp11->index = 14;
    temp11->column_Value = NULL;
    temp11->next = NULL;
    *(hash_Table + 19) = temp11;
    
    
    hash_Struct * temp12 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //temp12->column_Name = (char *) malloc (sizeof(char) * strlen("movie_title"));
    strcpy(temp12->column_Name, "movie_title");
    temp12->index = 11;
    temp12->column_Value = NULL;
    *(hash_Table + 21) = temp12;
    
            
            hash_Struct * ptr6 = (hash_Struct *) malloc (sizeof(hash_Struct));
            //ptr6->column_Name = (char *) malloc (sizeof(char) * strlen("cast_total_facebook_likes"));
            strcpy(ptr6->column_Name, "cast_total_facebook_likes");
            ptr6->index = 13;
            ptr6->column_Value = NULL;
        
            temp12->next = ptr6;
    
    
    hash_Struct * temp13 = (hash_Struct *) malloc (sizeof(hash_Struct));
    strcpy(temp13->column_Name, "duration");
    temp13->index = 3;
    temp13->column_Value = NULL;
    *(hash_Table + 22) = temp13;
    
            hash_Struct * ptr7 = (hash_Struct *) malloc (sizeof(hash_Struct));
            strcpy(ptr7->column_Name, "actor_2_name");
            ptr7->index = 6;
            ptr7->column_Value = NULL;
            ptr7->next = NULL;
            
            temp13->next = ptr7;
    
    
    
    hash_Struct * temp14 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp14->column_Name = (char *) malloc (sizeof(char) * strlen("title_year"));
    strcpy(temp14->column_Name, "title_year");
    temp14->index = 23;
    temp14->column_Value = NULL;
    temp14->next = NULL;
    *(hash_Table + 24) = temp14;
    
    
    hash_Struct * temp15 = (hash_Struct *) malloc (sizeof(hash_Struct));
    //temp15->column_Name = (char *) malloc (sizeof(char) * strlen("plot_keywords"));
    strcpy(temp15->column_Name, "plot_keywords");
    temp15->index = 16;
    temp15->column_Value = NULL;
    temp15->next = NULL;
    *(hash_Table + 25) = temp13;
    
    
    hash_Struct * temp16 = (hash_Struct*) malloc (sizeof(hash_Struct));
    //temp16->column_Name = (char *) malloc (sizeof(char) * strlen("movie_facebook_likes"));
    strcpy(temp16->column_Name, "movie_facebook_likes");
    temp16->index = 27;
    temp16->column_Value = NULL;
    temp16->next = NULL;
    *(hash_Table + 26) = temp16;
    
    
    hash_Struct * temp17 = (hash_Struct *) malloc (sizeof(hash_Struct));
    strcpy(temp17->column_Name, "actor_3_facebook_likes");
    temp17->index = 5;
    temp17->column_Value = NULL;
    *(hash_Table + 27) = temp17;
    
            hash_Struct * ptr8 = (hash_Struct*) malloc (sizeof(hash_Struct));
            //ptr8->column_Name = (char *) malloc (sizeof(char) * strlen("num_user_for_reviews"));
            strcpy(ptr8->column_Name, "num_user_for_reviews");
            ptr8->index = 18;
            ptr8->column_Value = NULL;
    
            temp17->next = ptr8;
            
        
             hash_Struct * ptr9 = (hash_Struct *) malloc (sizeof(hash_Struct));
            //ptr9->column_Name = (char *) malloc (sizeof(char) * strlen("num_critic_for_reviews"));
            strcpy(ptr9->column_Name, "num_critic_for_reviews");
            ptr9->index = 2;
            ptr9->column_Value = NULL;
            ptr9->next = NULL;
        
            ptr8->next = ptr9;
            
    
    
        
    
    
    *(hash_Table + 1) = NULL;
    *(hash_Table + 6) = NULL;
    *(hash_Table + 9) = NULL;
    *(hash_Table + 10) = NULL;
    *(hash_Table + 12) = NULL;
    *(hash_Table + 14) = NULL;
    *(hash_Table + 15) = NULL;
    *(hash_Table + 16) = NULL;
    *(hash_Table + 18) = NULL;
    *(hash_Table + 20) = NULL;
    *(hash_Table + 23) = NULL;
    
    return hash_Table;
}
