/*
	This is a basic sample in C to:
	1) Process a CSV file using getline and str* functions
	2) Add the data to a memory allocated data structure
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMALLSTR 32
#define LARGESTR 255

struct object {
	char attra[SMALLSTR];
	char attrb[SMALLSTR];
	char attrc[LARGESTR];
};

int main(void) {
	FILE *fh;
	int objn = 0, i = 0;
	char *val, *fielda, *fieldb, *fieldz;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	struct object *temp;
	struct object *data = (struct object*) malloc(sizeof(struct object));
	
	// Open the file for reading
	fh = fopen("testfile.txt", "r");
	if (fh == NULL)
		exit(-1);
	
	// For each line...
	while ((read = getline(&line, &len, fh)) != -1) {
		// The variable fieldz will initially hold the whole line
		fieldz = line;

		// Extract the first field from fieldz...
		val = strsep(&fieldz, ",");
		if (strlen(val) > 0) {
			// If it's a valid string, chomp the newline and save it
			val[strcspn(val, "\n")] = 0;
			fielda = strdup(val);
		} else {
			// If it's null, jump to the next line
			printf("WARN: Line %d is bad. Skipping...\n", i+1);
			continue;
		}

		// Extract the second field...
		val = strsep(&fieldz, ",");
		if (strlen(val) > 0) {
			val[strcspn(val, "\n")] = 0;
			fieldb = strdup(val);
		} else {
			printf("WARN: Line %d is bad. Skipping...\n", i+1);
			continue;
		}

		// Extract the last field...
		if (fieldz != NULL) 
			fieldz[strcspn(fieldz, "\n")] = 0;
		else {
			printf("WARN: Line %d is bad. Skipping...\n", i);
			continue;
		}
		
		// Copy the fields to the datastructure
		strncpy(data[objn].attra, fielda, SMALLSTR);
		strncpy(data[objn].attrb, fieldb, SMALLSTR);
		strncpy(data[objn].attrc, fieldz, LARGESTR);
		objn++;

		// Resize the array of structs in memory
		temp = realloc(data, (objn+2) * sizeof(struct object));
		if (temp != NULL)
			data = temp;
		else {
			free(data);
			printf("Error allocating memory!\n");
			exit(-1);
		}
	}
	fclose(fh);
	if (line)
		free(line);

	// print out the data structure
	for (i=0; i<objn; i++)
		printf("Object %d: %s\n", i, data[i].attra);
	free(data);
	
	exit(0);
}
