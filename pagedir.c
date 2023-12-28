#include "pagedir.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
bool pagedir_init(const char *pageDirectory) {
	// Fill in with your implementation
	char *first_file = "First_file.crawler";
	//char *dir = strcat(first_file, ".crawler");
	//char *crawer_file[500];
	
	// Check if the directory already exists
    struct stat st;
    if (stat(pageDirectory, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
		//fopenf(pageDirectory,
		 //char doc_id_str[100];
                //sprintf(doc_id_str, "%d",documentID);//Conver doc ID to string

                char path[500];  // Adjust the size as needed
                snprintf(path, sizeof(path), "%s/%s", pageDirectory, first_file);               
		FILE *crawler = fopen(path, "a"); 
	
		//fprintf(stderr,"In pagesavedir\n");

		//fprintf(stderr,"After opening directory");
/*              FILE *fp = fopen(pageDirectory, "a");
                fprintf(stderr,"After opening directory");
                char doc_id_str[100];
                sprintf(doc_id_str, "%d",documentID);//Conver doc ID to string*/
               /// FILE *web = fopen(path, "a");
                //fprintf(stderr,"After opening path\n");
                //if(web == NULL){
                  //      perror("Error creating crawler file");
                        //return;
                //}
            // Directory exists
           // fprintf(stderr, "Directory already exists\n");
            return true;
        } else {
            // Not a directory
            //fprintf(stderr, "Error: %s is not a directory\n", pageDirectory);
            return false;
        }
    }


	///fprintf(stderr,"This is pageDirectory: %s\n",pageDirectory);
	if (mkdir(pageDirectory, 0777) == 0) {
		 //char path[500];  // Adjust the size as needed
                ///snprintf(path, sizeof(path), "%s/%s", pageDirectory, dir);
                //fprintf(stderr,"In pagesavedir\n");

/*              FILE *fp = fopen(pageDirectory, "a");
                fprintf(stderr,"After opening directory");
                char doc_id_str[100];
                sprintf(doc_id_str, "%d",documentID);//Conver doc ID to string*/
                ///FILE *web = fopen(path, "a");
                //fprintf(stderr,"After opening path\n");
                //if(web == NULL){
                  //      perror("Error creating crawler file");
                        //return;
                //}
        	//fprintf(stderr, "Directory created successfully\n");
        	return true;
    	} else {
        	FILE *fp = fopen(pageDirectory,"a");
        	if(fp == NULL){
                	return false;
        	}
       		 fclose(fp);
        	return true;
        	//fprintf(stderr, "Error: Cannot create directory\n");
        	//return false;
    }
/*
	FILE *fp = fopen(pageDirectory,"a");
	if(fp == NULL){
		return false;
	}
	fclose(fp);
	return true; //Directory initialized successfully*/
}
/**
 * Saves a given webpage to a given page directory with a given document ID.
 */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
	// Fill in with your implementation
	//bool result = pagedir_init(pageDirectory);
	//if(result == true){
		 char doc_id_str[100];
                sprintf(doc_id_str, "%d",documentID);//Conver doc ID to string

		char path[500];  // Adjust the size as needed
        	snprintf(path, sizeof(path), "%s/%s", pageDirectory, doc_id_str);
		//fprintf(stderr,"In pagesavedir\n");

/*		FILE *fp = fopen(pageDirectory, "a");
		fprintf(stderr,"After opening directory");
		char doc_id_str[100];
                sprintf(doc_id_str, "%d",documentID);//Conver doc ID to string*/
		FILE *web = fopen(path, "a");
		//fprintf(stderr,"After opening path\n");
		if(web == NULL){
			perror("Error creating file");
			return;
		}
		//fprintf(stderr,"Before writing to web\n");
//		if (page == NULL || page->url == NULL || page->html == NULL) {
  //  fprintf(stderr, "Error: NULL pointer in pagedir_save\n");
    //return;
//}


		fprintf(web,"%s\n", page->url);
		fprintf(web,"%d\n", page->depth);
		fprintf(web, "%s", page->html);
		//fprintf(web,"After writing to web\n");
		//fprintf(fp, web);

		fclose(web);
		//fclose(fp);
	//}
}
