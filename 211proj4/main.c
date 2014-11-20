/*
 * Reed Rosenberg
 * CS 211 Assignment 4
 */

#include <stdio.h>		// for IO functions
#include <stdlib.h>		// for Dynamic Memory Allocation
#include <string.h>		// for string functions
#include <ctype.h>		// for character functions
#include <assert.h>		// for assert for debugging & error catching

// Global variables & macro definitions
#define HASH_MULTIPLIER 65599
int htsize;			// size (in buckets) of hash table

// Type definition for a Node (component of a linked list)
struct NodeType {
	char *word;		// a string representing the word
	int count;		// the # of times that word appears in the text
	struct NodeType *next;	// pointer to next node in list (if it exists)
};
typedef struct NodeType Node;	// define Node to be synonymous with NodeType

// Function prototypes
Node **ht_create(void);			// create hash table
char *lowercase(char *str);		// convert string to lower-case
unsigned int hash(const char *str);	// hashing function
int ht_insert(Node **Table, const char *word);	// insert new word to hash table
void ht_print(Node **Table);		// print hash table
void ht_destroy(Node **Table);		// free space allocated for hash table

int main(int argc, char *argv[])
{
	/* Hash table size is a command-line argument, in argv[1] */
	if (argc <= 1) {
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	} else if ( (htsize = atoi(argv[1])) < 1) {
		printf("ERROR: invalid hash table size (%s)\n", argv[1]);
		return 1;
	}
	//htsize = atoi(argv[1]);	// get value for global htsize from cmd line
	
	Node **Table;		// a pointer to the heap-allocated hash table
	Table = ht_create();	// create hash table
	
	// Variables for string tokenizing/line parsing
	char *line = NULL;		// line buffer argument to getline()
	size_t length = 0;		// buffer size argument to getline()
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
				// can't allocate space for word; destroy hash
				// table and exit program
				printf("ERROR: Could not allocate string\n");
				ht_destroy(Table);
				return 1;
			}
			ht_insert(Table, word);		// insert word to table
			token = strtok(NULL, delim);	// extract next token
		}
	}
	free(line);			// free line buffer
	
	ht_print(Table);		// print hash table
	ht_destroy(Table);	// free space allocated for hash table
	return 0;
}

/*
 * Create a heap-allocated hash table with htsize buckets, initially empty, and
 * return a pointer to it. If the table cannot be allocated, issue an error
 * message on stderr and terminate program.
 */
Node **ht_create(void)
{
	
	Node **Array;	// Create a 1D array of pointers to Nodes
	int i;		// For incrementing loop
	
	Array = (Node **) malloc(htsize * sizeof(Node *));
	
	assert(Array != NULL);	// Abort program if allocation fails
		
	for (i = 0; i < htsize; i++) {
		Array[i] = NULL;	// Initialize each pointer in the table
	}				// as a NULL pointer.
	
	return Array;			// Return a pointer to the hash table
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

/*
 * Insert word in lower-case into the hash table Table. If word is not in Table,
 * insert a new node for the word in the bucket to which it hashes to, and
 * initialize its count to 1. The node should be inserted at the end of the list
 * for the bucket. If word is already in Table, increment its count by 1. Return
 * 1 on success, else return 0.
 */
int ht_insert(Node **Table, const char *word)
{
	unsigned int hash_result = hash(word);
	Node *p, *prevp, *bucket = Table[hash_result];
	
	if ( Table[hash_result] != NULL) {
		// if bucket to hash word to is non-empty, search for word in it
		for (p = Table[hash_result]; p != NULL;
		     prevp = p, p = p->next) {
			// using strncmp to prevent buffer over/underflow
			// Note: the longest English word is 45 letters long
			if (strncmp(p->word, word, (sizeof(char) * 45)) == 0) {
				p->count++;	// word found, increment count
				return 1;	// return success & exit func
			}
		}	// word not found in bucket. create new node.
		
		Node *new = (Node *) malloc(sizeof(Node));
		if (new == NULL) {
			return 0;	// malloc for Node failed
		}
		if ( (new->word = strdup(word)) == NULL) {
			return 0;	// malloc for copied string failed
		}
		new->count = 1;
		new->next = NULL;
		if (prevp != NULL) {
			prevp->next = new;
		}
		return 1;
	} else if ( Table[hash_result] == NULL) {
		
	}
	
	Node *new = (Node *) malloc(sizeof(Node));
	if (new == NULL) {
		return 0;	// malloc for Node failed
	}
	if ( (new->word = strdup(word)) == NULL) {
		return 0;	// malloc for copied string failed
	}
	new->count = 1;
	new->next = NULL;
	p->next = new;
	return 1;	
}

/*
 * Print all words stored in the hash table Table. Specifically, iterate over
 * the buckets of the hash table and print the [word,count] tuples hashed to
 * each bucket.
 */
void ht_print(Node **Table)
{
	int i;
	Node *p;
	
	for (i = 0; i < htsize; i++) {
		printf("\nHT[%d]:", i);
		for (p = Table[i]; p!= NULL; p = p->next) {
			printf(" [%s, %i] ", p->word, p->count);
		}
	}
	printf("/n");
	return;
}

/*
 * Destroy the hash table Table by freeing all the space allocated to the table.
 */
void ht_destroy(Node **Table)
{
	int i;
	Node *p, *nextp;
	
	for (i = 0; i < htsize; i++) {
		for (p = Table[i]; p != NULL; p = nextp) {
			nextp = p->next;
			free(p->word);
			free(p);
		}
		free(Table[i]);
	}
	return;
}