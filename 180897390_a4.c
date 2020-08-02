/**
Robert Goss
180897390
github username: robertg6
-------------------
CP386 Assignment 4
-------------------

The motivation of this project is to write a program that 
implements multiple threads implementing the bankers algorithm. 
This algorithm concerns itself with different bankers manipulating 
resources, and the program using deadlock avoidance to avoid deadlock
 :) (;
 ;) (:
**/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

#define MAX_INPUT_SIZE 256
#define FILE_NAME "sample4_in.txt"

int count_of_customers; //the amount of customers BRO
int count_of_resources; //just read it, the name is obvious
int **upper_bound; // this is like similar to the word maximum
int **alloc; //this is like allocated but not
int **things_we_need; //i really need an A in this class, thats what things we need ;-)
int *things_we_have; //not much tbh
int *order_of_sequence; //as the name implies its the order of the sequence

int OKAY; //this is a stand-in for the word safe

void *running_of_threads(void *t);
int *get_the_saftey_order();
int **Reading_of_File(char *fileName);
void double_util(int **information, int m, int n);
void single_util(int *information, int m);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Not enough input parameters!\n");
        return -1;
    }
    count_of_resources = argc - 1;

    // Initialize things_we_have so that we know what we have yo
    things_we_have = malloc(sizeof(int) * count_of_resources);
    for (int i = 1; i < argc; i++)
    {
        things_we_have[i - 1] = atoi(argv[i]);
    }

    // Initialize upper_bound array by reading file and assigning values so that we know what the upper bound will need to be 
    upper_bound = Reading_of_File(FILE_NAME);

    // Initialize alloc array and things_we_need array
    alloc = malloc(sizeof(int *) * count_of_customers);
    things_we_need = malloc(sizeof(int *) * count_of_customers);
    for (int i = 0; i < count_of_customers; i++)
    {
        alloc[i] = malloc(sizeof(int) * count_of_resources);
        things_we_need[i] = malloc(sizeof(int) * count_of_resources);
    }

    // Initialize OKAY as 0 since no resources are allocated
    OKAY = 0;


    //begining of the main program
    char *userCommand = malloc(sizeof(char) * MAX_INPUT_SIZE);

    printf("Number of Customers: %d\n", count_of_customers);
    printf("Currently avaliable resources: ");
    single_util(things_we_have, count_of_resources);
    printf("max resources from file:\n");
    double_util(upper_bound, count_of_customers, count_of_resources);

    // Loop to continue running until "exit" is inputted
    while (1)
    {
        printf("Enter Command: ");
        fgets(userCommand, MAX_INPUT_SIZE, stdin);
        // Replace new line character with end of line character
        if (strlen(userCommand) > 0 && userCommand[strlen(userCommand) - 1] == '\n')
        {
            userCommand[strlen(userCommand) - 1] = '\0';
        }
        /**
         * This
         * Models
         * User
		 * Input
         * */
        if (strstr(userCommand, "RQ"))
        {
            // Split up the string to fill the allo array, also hopefully you having a good day
            int count = 0;
            int *inputArray = malloc(sizeof(int) * (count_of_resources + 1));
            char *token = NULL;
            token = strtok(userCommand, " ");
            while (token != NULL)
            {
                if (count > 0)
                {
                    inputArray[count - 1] = atoi(token);
                }
                token = strtok(NULL, " ");
                count++;
            }

            int customerToAllocate = inputArray[0];
            // Insert the vaues into the alloc array, also hope you dont have to much marking left :(
            if (customerToAllocate < count_of_customers && count == count_of_resources + 2)
            {
                for (int i = 0; i < count_of_resources; i++)
                {
                    alloc[customerToAllocate][i] = inputArray[i + 1];
                    things_we_need[customerToAllocate][i] = upper_bound[customerToAllocate][i] - alloc[customerToAllocate][i];
                    // Things_we_need cant be allowed to be negative, just like you attitude, stay positive ;-)
                    if (things_we_need[customerToAllocate][i] < 0)
                    {
                        things_we_need[customerToAllocate][i] = 0;
                    }
                }
            }
            else
            {
                if (customerToAllocate >= count_of_customers)
                {
                    printf("Thread out of bounds, please try again.\n");
                }
                else
                {
                    printf("Incorrect parameter count, please try again.\n");
                }
            }
            free(inputArray);
            // Determine if request would be satisfied or denied with safety algorithm
            order_of_sequence = get_the_saftey_order();
            printf("Request satisfied.\n");
            if (order_of_sequence[0] == -1)
            {
                OKAY = 0;
                printf("Warning: Unsafe state, please fix before running.\n");
            }
            else
            {
                OKAY = 1;
                printf("Info: State is now OKAY.\n");
            }
        }
        else if (strstr(userCommand, "RL"))
        {
            // Split tokens by space to remove from alloc array
            int count = 0;
            int *inputArray = malloc(sizeof(int) * (count_of_resources + 1));
            char *token = NULL;
            token = strtok(userCommand, " ");
            while (token != NULL)
            {
                if (count > 0)
                {
                    inputArray[count - 1] = atoi(token);
                }
                token = strtok(NULL, " ");
                count++;
            }

            int customerToAllocate = inputArray[0];
            // Remove from alloc array
            if (customerToAllocate < count_of_customers && count == count_of_resources + 2)
            {
                for (int i = 0; i < count_of_resources; i++)
                {
                    if (inputArray[i + 1] <= alloc[customerToAllocate][i])
                    {
                        alloc[customerToAllocate][i] -= inputArray[i + 1];
                        things_we_need[customerToAllocate][i] = upper_bound[customerToAllocate][i] - alloc[customerToAllocate][i];
                    }
                    else
                    {
                        printf("You cannot release more resources than allocated.\n");
                        break;
                    }
                }
            }
            else
            {
                if (customerToAllocate >= count_of_customers)
                {
                    printf("Thread out of bounds, please try again.\n");
                }
                else
                {
                    printf("Incorrect parameter count, please try again.\n");
                }
            }
            free(inputArray);
            // Determine if request would be satisfied or denied with safety algorithm
            order_of_sequence = get_the_saftey_order();
            printf("Request satisfied.\n");
            if (order_of_sequence[0] == -1)
            {
                OKAY = 0;
                printf("Warning: Unsafe state, please fix before running.\n");
            }
            else
            {
                OKAY = 1;
                printf("Info: State is now OKAY.\n");
            }
        }
        else if (strstr(userCommand, "*"))
        {
            printf("things_we_have Resources:\n");
            single_util(things_we_have, count_of_resources);
            printf("Maxmium Resources:\n");
            double_util(upper_bound, count_of_customers, count_of_resources);
            printf("Allocated Resources:\n");
            double_util(alloc, count_of_customers, count_of_resources);
            printf("things_we_need Resources:\n");
            double_util(things_we_need, count_of_customers, count_of_resources);
        }
        else if (strstr(userCommand, "Run"))
        {
            order_of_sequence = get_the_saftey_order();
            if (OKAY == 1)
            {
                for (int i = 0; i < count_of_customers; i++)
                {
                    int threadToRun = order_of_sequence[i];
                    pthread_t tid;
                    pthread_attr_t attr;
                    pthread_attr_init(&attr);
                    pthread_create(&tid, &attr, running_of_threads, (void *)&threadToRun);
                    pthread_join(tid, NULL);
                }
            }
            else
            {
                printf("Warning: Unsafe state, please fix before running.\n");
            }
        }
        else if (strstr(userCommand, "exit"))
        {
            free(upper_bound);
            free(alloc);
            free(things_we_need);
            free(things_we_have);
            free(order_of_sequence);
            return 0;
        }
        else
        {
            printf("\"%s\" is not a valid input, enter one of [\"RQ\",\"RL\",\"*\",\"Run\",\"exit\"].\n", userCommand);
        }
    }
    return 0;
}

void *running_of_threads(void *t)
{
    int *the_threads_id = (int *)t;
    printf("--> Customer: %d\n", *the_threads_id);
    printf("    Allocated Resouces: ");
    for (int i = 0; i < count_of_resources; i++)
    {
        printf("%d ", alloc[*the_threads_id][i]);
    }
    printf("\n");
    printf("    things_we_needed Resources: ");
    for (int i = 0; i < count_of_resources; i++)
    {
        printf("%d ", things_we_need[*the_threads_id][i]);
    }
    printf("\n");
    printf("    things_we_have Resources: ");
    for (int i = 0; i < count_of_resources; i++)
    {
        printf("%d ", things_we_have[i]);
    }
    printf("\n");
    printf("    Thread has started...\n");
    sleep(1);
    printf("    Thread has finished...\n");
    sleep(1);
    printf("    Thread is releasing resources...\n");
    sleep(1);
    printf("    New things_we_have Resources: ");
    for (int i = 0; i < count_of_resources; i++)
    {
        things_we_have[i] += alloc[*the_threads_id][i];
        printf("%d ", things_we_have[i]);
    }
    printf("\n\n");
    sleep(1);

    pthread_exit(NULL);
}

int *get_the_saftey_order()
{
    // Safety order_of_sequence we will be returning, all -1 if unsafe
    int *order_of_sequence = malloc(sizeof(int) * count_of_customers);
    int *work = malloc(sizeof(int) * count_of_resources);
    int *finished = malloc(sizeof(int) * count_of_customers);

    // Initialize work to what we have things_we_have
    for (int i = 0; i < count_of_resources; i++)
    {
        work[i] = things_we_have[i];
    }

    // Primary safety algorithm
    int count = 0;
    while (count < count_of_customers)
    {
        int isSafe = 0;
        for (int i = 0; i < count_of_customers; i++)
        {
            if (finished[i] == 0)
            {
                int safeIteration = 1;
                for (int j = 0; j < count_of_resources; j++)
                {
                    if (things_we_need[i][j] > work[j])
                    {
                        safeIteration = 0;
                        break;
                    }
                }
                if (safeIteration == 1)
                {
                    order_of_sequence[count] = i;
                    finished[i] = 1;
                    count++;
                    isSafe = 1;
                    for (int j = 0; j < count_of_resources; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                }
            }
        }
        // Set safety order_of_sequence to -1 and return if no OKAY order_of_sequence found
        if (isSafe == 0)
        {
            for (int k = 0; k < count_of_customers; k++)
            {
                order_of_sequence[k] = -1;
            }
            free(work);
            free(finished);
            return order_of_sequence;
        }
    }
    free(work);
    free(finished);
    return order_of_sequence;
}

void double_util(int **information, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", information[i][j]);
            if (j < n - 1)
                printf(" ");
        }
        printf("\n");
    }
}

void single_util(int *information, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%d", information[i]);
        if (i < m - 1)
            printf(" ");
    }
    printf("\n");
}

int **Reading_of_File(char *fileName)
{
    FILE *in = fopen(fileName, "r");
    if (!in)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return NULL;
    }

    struct stat st;
    fstat(fileno(in), &st);
    char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
    fileContent[0] = '\0';
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            strncat(fileContent, line, strlen(line));
        }
    }
    fclose(in);
    char *command = NULL;
    char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
    strcpy(fileCopy, fileContent);
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        count_of_customers++;
        command = strtok(NULL, "\r\n");
    }
    strcpy(fileCopy, fileContent);
    char *lines[count_of_customers];
    int q = 0;
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        lines[q] = malloc(sizeof(command) * sizeof(char));
        strcpy(lines[q], command);
        q++;
        command = strtok(NULL, "\r\n");
    }
    int **max = malloc(sizeof(int *) * count_of_customers);
    for (int j = 0; j < count_of_customers; j++)
    {
        int *temp = malloc(sizeof(int) * count_of_resources);
        char *token = NULL;
        int k = 0;
        token = strtok(lines[j], ",");
        while (token != NULL)
        {
            temp[k] = atoi(token);
            k++;
            token = strtok(NULL, ",");
        }
        max[j] = temp; 
    }
    return max;
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
//This is a project by Robert Goss, do not steal
