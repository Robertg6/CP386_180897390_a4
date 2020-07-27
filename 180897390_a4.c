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


//definition of global variables

int **avail; //the avaliable resources
int **max; //the maximum deamand for each customer
int **current_allocated; //the currently allocated resources
int customer_count; //the current count of customers in the system
int resource_count; //the amaount of resources

//end of definition of global variables

void* run_thread(void *t) //this is a function to run each thread in the program
int **read_File(char *file_name) // this is a function that will be used to read the file along with other set up
void single_util(int *d, int a) //this is a utility function that wil be used to output the single pointer data
void double_utility(int *d, int a, int b)// this is a utility function that can be used to output the double pointer data

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
	fclose(input);
	//end of this chunk
	
	char *com = NULL;
    char *Copy = (char *)malloc((strlen(Contents) + 1) * sizeof(char));
    strcpy(Copy, Contents);
    com = strtok(Copy, "\r\n");
	 while (com != NULL)
    {
        customer_count++;
        com = strtok(NULL, "\r\n");
    }
    strcpy(Copy, Contents);
    char *lines[customer_count];
    int i = 0;
    command = strtok(fileCopy, "\r\n");
	
	
	while (com != NULL)
    {
        lines[i] = malloc(sizeof(com) * sizeof(char));
        strcpy(lines[i], com);
        i++;
        com = strtok(NULL, "\r\n");
    }
	
	
	
	
	
	int **large = malloc(sizeof(int *) * customer_count);
    for (int j = 0; j < customer_count; j++)
    {
        int *seb = malloc(sizeof(int) * resource_count);
        char *tok = NULL;
        int s = 0;
        tok = strtok(lines[j], ",");
        while (tok != NULL)
        {
            seb[s] = atoi(tok);
            s++;
            tok = strtok(NULL, ",");
        }
        large[j] = tem;
    }
    return large;
	
	
	
}


void* single_utility(int *d, int a){
	//This function isdesign so astoprint the value of the single pointer to make my life easier ;-)
	for(int v = 0; v < a; v++){
		printf("%d", d[v]);
		if(v < a-1){
			printf(" ");
		}
		printf("\n");
	}
}

void* run_thread(void *t){}


void* double_utility(int **d, int a, int b){
	// a utility function that is used to print the data within a double pointer, this is mainly for output and nothing else bro ;-) 
	for (int v = 0; v < a; v++)
    {
        for (int co = 0; co < b; co++)
        {
            printf("%d", d[v][co]);
            if (co < a - 1)
                printf(" ");
        }
        printf("\n");
    }
	
}



















//;-) 
//;-) //;-) 
//;-) //;-) //;-) 
//;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-) //;-) //;-) 
//;-) //;-) //;-) //;-) //;-)
//;-) //;-) //;-) //;-) 
//;-) //;-) //;-) 
//;-) //;-) 
//;-) 