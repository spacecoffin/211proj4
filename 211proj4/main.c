/*
 * Reed Rosenberg
 * CS 211 Assignment 4
 */

#include <stdio.h>		// for IO functions
#include <stdlib.h>		// for Dynamic Memory Allocation
#include <string.h>		// for string functions
//#include <assert.h>		// for assert for debugging

// Global variables & macro definitions
#define HASH_MULTIPLIER 65599
int htsize;			// size (in buckets) of hash table

// Type definition for a Node
struct NodeType {
	char *word;		// a string representing the word
	int count;		// the # of times that word appears in the text
	struct NodeType *next;	// pointer to next node in list (if it exists)
};
typedef struct NodeType Node;	// define Node to be synonymous with NodeType

// Function prototypes
Node **ht_create(void);			// create hash table
char *lowercase(char *str);		// ensure lowercase tokenization
void ht_destroy(Node **Table);		// free allocated space for hash table

int main(int argc, char *argv[])
{
	/* Hash table size is a command-line argument, in argv[1] */
	if (argc <= 1) {
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	} // else if for extra arguments????
	htsize = atoi(argv[1]);
	
	Node **Table;		// a pointer to the heap-allocated hash table
	Table = ht_create();	// create hash table
	
	/*
	 * If the table cannot be allocated, issue an error message on stderr 
	 * and terminate program.
	 */
	if (Table == NULL) {
		fprintf(stderr, "ERROR: malloc failed\n");
		return 1;
	}
	
	// Variables for string tokenizing/line parsing
	char *line = NULL;  	// line buffer argument to getline()
	size_t length = 0;  	// buffer size argument to getline()
	char *token;			// token returned by strtok()
	char *delim = " .,;:!\"?\n";	// delimiter characters for strtok()
	char *word;			// token word in lower-case
	
	// Parse lines of input text; extract and insert words into string table
	while (1) {
		if (getline(&line, &length, stdin) == -1) {    // read next line
			break;			// exit loop when no more lines
		}
		token = strtok(line, delim);	// extract next token from line
		while (token != NULL) {
			// store in word a copy of the token in lower-case
			if ( (word = lowercase(token)) == NULL) {
				// can't allocate space for word; empty hash
				// table and exit program
				printf("ERROR: Could not allocate string\n");
				ht_empty(Table, n);
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


}

/*
 * Create a heap-allocated hash table with htsize buckets, initially empty, and
 * return a pointer to it. If the table cannot be allocated, issue an error
 * message on stderr and terminate program.
 */
Node **ht_create(void)
{
	// struct Node *hashtab[ARRAYSIZE];
	Node **ht = (Node **) malloc(htsize * sizeof(Node *));
	memset( *ht, 0, sizeof( ht ));	// initialize to all 0s
	return ht;
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

// CONVERT TO HT_DESTROY
/*
 * Destroy the hash table Table by freeing all the space allocated to the table.
 */

/* Empty table by freeing all strings */
//void empty(char *Table[], int n)
void ht_destroy(Node **Table)
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

/*
void list_free(List *list) {
	Node *p, *nextp;
	for (p = list->first; p != NULL; p = nextp) { nextp = p->next;
		free(p->key);
		free(p);
	}
	free(list);
	return;
}
*/