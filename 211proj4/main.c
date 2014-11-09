/*
 File concordance.c
 Solution to CS 211 Assignment 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Function prototypes */
char *lowercase(char *str);
int insert(char *word, char *Table[], int n);
void print(char *Table[], int n);
void empty(char *Table[], int n);

int main(int argc, char *argv[])
{
	int table_size;		// table size, a command-line argument
	int n;			// current number of strings in yable
	int i;			// loop variable
	char *line = NULL;  	// line buffer argument to getline()
	size_t length = 0;  	// buffer size argument to getline()
	char *token;			// token returned by strtok()
	char *delim = " .,;:!\"?\n";	// delimiter characters for strtok()
	char *word;			// token word in lower-case
	
	/* Table size is a command-line argument, in argv[1] */
	if (argc <= 1) {
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	}
	table_size = atoi(argv[1]);
	
	/* String table is a 1D array of pointers to strings */
	char *Table[table_size];
	
	/* Initialize all pointers of string table to NULL */
	for (i = 0; i < table_size; i++)
		Table[i] = NULL;
	
	/* Initialize current number of strings in table to 0 */
	n = 0;
	
	// Parse lines of input text; extract and insert words into string table
	while (1) {
		if (getline(&line, &length, stdin) == -1)// read next line
			break;			// exit loop when no more lines
		token = strtok(line, delim);	// extract next token from line
		while (token != NULL) {
			// store in word a copy of the token in lower-case
			if ( (word = lowercase(token)) == NULL) {
				// can't allocate space for word; empty table,
				// and exit program
				printf("ERROR: Could not allocate string\n");
				empty(Table, n);
				return 1;
			}
			if (n >= table_size) {	// table is full; print table,
						// empty table, and exit program
				printf("ERROR: Table is full\n");
				print(Table, n);
				empty(Table, n);
				return 1;
			}
			n = insert(word, Table, n); // insert word into table
			token = strtok(NULL, delim);	// extract next token
		}
	}
	free(line);			// free line buffer
	print(Table, n);		// print table
	empty(Table, n);		// empty table
	return 0;
}

/* Convert string str to lower-case */
char *lowercase(char *str)
{
	char *word, *ptr;
	
	if ( (word = strdup(str)) !=  NULL) {
		for (ptr = word; *ptr != '\0'; ptr++)
			*ptr = tolower(*ptr);
	}
	return word;
}

/* Insert the string word into Table; maintain strings in sorted order */
/* Return value is n+1 if insert succeeds */
int insert(char *word, char *Table[], int n)
{
	int i, low, high, mid;
	
	/* Search if word is already in Table using binary search */
	low = 0;
	high = n-1;
	while (low <= high) {
		mid = low + (high - low)/2;
		if (strcmp(word, Table[mid]) == 0) {	// word is in Table[mid]
			free(word);	// free heap space occupied by word
			return n;
		}
		else if (strcmp(word, Table[mid]) > 0) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	
	/* word is not in Table; insert at Table[low] */
	for (i = n-1; i >= low; i--)		// shift strings from Table[i]
						// to Table[n-1] "down"
		Table[i+1] = Table[i];
	Table[low] = word;			// insert word into Table[i]
	return n+1;
}

/* Print all n strings currently in Table */
void print(char *Table[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) {
		if (Table[i] != NULL)
			printf("%d: %s\n", i+1, Table[i]);
		else
			printf("ERROR: missing string\n");
	}
	return;
}

/* Empty table by freeing all strings */
void empty(char *Table[], int n)
{
	int i;
	
	for (i = 0; i < n; i++) {
		if (Table[i] != NULL) {
			free(Table[i]);
			Table[i] = NULL;
		}
	}
	return;
}
