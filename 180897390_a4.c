/**
Robert Goss
180897390
-------------------
CP386 Assignment 4
**/

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <string.h>

#include <pthread.h>

#include <sys/stat.h>

#include <semaphore.h>

#include <time.h>

void* run_thread(void *t) //this is a function to run each thread in the program
int **read_File(char *file_name) // this is a function that will be used to 


int main(int argc, char *argv[]){}

int **read_File(char *file_name){
	
	//this chunk checks if there is a valid input file
	FILE *input = fopen(file_name, "r");
    if (!input)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return NULL;
    }
	// end of this chunk
	
	
	//This chunk of code both stores info about the input file and gets each line and concatinates it to contents
	struct stat sa;
    fstat(fileno(input), &sa);
    char *Contents = (char *)malloc(((int)sa.st_size + 1) * sizeof(char)); //define a char that is the size of the inout file
    Contents[0] = '\0';
    while (!feof(input)) //walk through until end of file
    {
        char line[100];
        if (fgets(line, 100, input) != NULL)
        {
            strncat(Contents, line, strlen(line)); //concatinate from file to contents
        }
    }
	//end of this chunk
	
}

void* run_thread(void *t){}






















