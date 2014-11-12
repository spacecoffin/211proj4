/*
 * Reed Rosenberg
 * CS 211 Assignment 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* OLD Function prototypes */
char *lowercase(char *str);			// carries over
int insert(char *word, char *Table[], int n);	// replaced by ht_insert
void print(char *Table[], int n);		// replaced by ht_print
void empty(char *Table[], int n);		// replaced by ht_empty

// Global & macro definitions (suggested in assignment)
#define HASH_MULTIPLIER 65599
int htsize;			// size (in buckets) of hash table

// sample type definition for a node
struct NodeType {
	char *word;		// a string representing the word
	int count;		// the # of times that word appears in the text
	struct NodeType *next;	// pointer to next node in list (if it exists)
};
typedef struct NodeType Node;

Node **Table;

// NEW Func prototypes
unsigned int hash(const char *str);
Node **ht_create(void);
int ht_insert(Node **Table, const char *word);
void ht_print(Node **Table);
void ht_destroy(Node **Table);

int main(int argc, char *argv[])
{
	int table_size;		// table size, a command-line argument
	int n;			// current number of strings in table
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

// EXAMPLE HASH FUNCTION
/* Compute and return the bucket to which the string str hashes. */
// [[[[ You should use the hash function discussed in class ]]]
unsigned int hash(const char *str)
{
	int i;
	unsigned int h = 0U;
	for (i = 0; str[i] != '\0'; i++)
		h = h * HASH_MULTIPLIER + (unsigned char) str[i];
	return h % htsize;
}

// CHECK FOR USE WITH NEW FUNCTIONS
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

/*
 * Create a heap-allocated hash table with htsize buckets, initially empty, and
 * return a pointer to it. If the table cannot be allocated, issue an error
 * message on stderr and terminate program.
 */
Node **ht_create(void)
{
	return 0;
}

// CONVERT TO HT_INSERT
/*
 * insert word in lower-case into the hash table Table. If word is not in Table,
 * insert a new node for the word in the bucket to which it hashes to, and
 * initialize its count to 1. The node should be inserted at the end of the list
 * for the bucket. If word is already in Table, increment its count by 1. Return
 * 1 on success, else return 0.
 */
// int ht_insert(Node **Table, const char *word)

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

// CONVERT TO HT_PRINT
/*
 * Print all words stored in the hash table Table. Specifically, iterate over
 * the buckets of the hash table and print the [word,count] tuples hashed to
 * each bucket.
 */
// void ht_print(Node **Table)

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

// CONVERT TO HT_DESTROY
/*
 * destroy the hash table Table by freeing all the space allocated to the table.
 */
// void ht_destroy(Node **Table)

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
