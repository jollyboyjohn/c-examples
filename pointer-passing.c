#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Element definition for the array
struct object {
	int number;
	char string[256];
};

// Declarations of functions
int add_data (struct object **data, int count);
void print_data (struct object *data, int count);

// The main body of the program
void main() {
	// Define an empty pointer to the array and a counter for the elements
	struct object *ptr = NULL;
	int count = 0;

	// Add some data to the array, using a pointer-to-a-pointer
	count = add_data(&ptr, count);
	count = add_data(&ptr, count);

	// Print the data directly using the pointer
	print_data(ptr, count);
}

// This function adds data to the array
int add_data (struct object **data, int count) {
	// Define a temporary pointer to work with
	struct object *temp = NULL;

	// Initialise temp or increase the memory, using data as the basis
 	if (count == 0) {
		temp = malloc(sizeof(struct object));
	} else {
		temp = realloc(*data, (count+2 * sizeof(struct object)));
	}

	// Some sample data - you need to use strcpy() for strings
	temp[count].number = count * 10;
	strcpy(temp[count].string, "next string");

	if (temp != NULL) {
		// If the temporary pointer is defined, copy temp to data
		*data = temp;
	} else {
		// Otherwise, kill the program
		free(data);
		printf("Error allocating memory!\n");
		exit(1);
	}
	// Increment and then return the count of elements in the array
	return ++count;
}

// Print out the array	
void print_data (struct object *data, int count) {
	int i;
	for (i=0; i < count; i++)
		printf("Line: %d, %s\n", data[i].number, data[i].string);
}
