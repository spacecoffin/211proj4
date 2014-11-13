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
Node **ht_create(void);

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
}

/*
 * Create a heap-allocated hash table with htsize buckets, initially empty, and
 * return a pointer to it. If the table cannot be allocated, issue an error
 * message on stderr and terminate program.
 */
Node **ht_create(void)
{
	Node **ht = (Node **) malloc(htsize * sizeof(Node *));
	memset( *ht, 0, sizeof( ht ));	// initialize to all 0s
	return ht;
}