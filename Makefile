/**
don't change the contents of this file.
This is the makefile for my Assignment 4 project
once you have compiled the program using make the executable will be named "Assign_4"
**/
warnings_BAD: *.c
	gcc -Werror -Wall -g -std=gnu99 -o Assignment_4 *.c -lrt -lpthread

warnings_OK: *.c
	gcc -Wall -g -std=gnu99 -o Assignment_4 *.c -lrt -lpthread

clean: *.c
	rm Assign_4