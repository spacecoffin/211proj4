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

// Type definition for a Node (component of a linked list)
struct NodeType {
	char *word;		// a string representing the word
	int count;		// the # of times that word appears in the text
	struct NodeType *next;	// pointer to next node in list (if it exists)
};
typedef struct NodeType Node;	// define Node to be synonymous with NodeType

/*
// Type definition for a Linked List (component of a hash table)
struct ListType {
	Node *first;
};
typedef struct ListType List;
 */

// Function prototypes
Node **ht_create(void);			// create hash table
//List *list_create(void);		// create a linked list
char *lowercase(char *str);		// ensure lowercase tokenization
unsigned int hash(const char *str);	// hashing function
int ht_insert(Node **Table, const char *word);	// insert new word to hash table
void ht_destroy(Node **Table);		// free allocated space for hash table

int main(int argc, char *argv[])
{
	/* Hash table size is a command-line argument, in argv[1] */
	if (argc <= 1) {
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	} // else if for extra arguments????
	htsize = atoi(argv[1]);	// get value for global htsize from cmd line
	
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
				// can't allocate space for word; destroy hash
				// table and exit program
				printf("ERROR: Could not allocate string\n");
				ht_destroy(Table);
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
 * Create a heap-allocated linked list initialized as a null pointer and return
 * a pointer to it. If the list cannot be allocated, return NULL.
 
List *list_create(void)
{
	List *list = (List *) malloc(sizeof(List));
	
	if (list == 0) {
		return NULL;
	}
	
	list->first = NULL;
	return list;
}
 */


/*
 * Create a heap-allocated hash table with htsize buckets, initially empty, and
 * return a pointer to it. If the table cannot be allocated, issue an error
 * message on stderr and terminate program.
 */
Node **ht_create(void)
{
	// Create a 1D array of pointers to Nodes
	Node *Array;
	int i;		// for incrementing loop
	
	Array = (Node *) malloc(htsize * sizeof(Node *));
	
	if (Array == NULL) {
		return NULL;
	}
	
	for (i = 0; i < htsize; i++) {
		Array[i] = *(Node *) malloc(sizeof(Node *));
		//Array[i] = NULL;
	}
	
	/*
	// struct Node *hashtab[ARRAYSIZE];
	Node **ht = (Node *) malloc(htsize * sizeof(Node *));
	//(Node **) malloc(htsize * sizeof(Node *));
	//memset( *ht, 0, sizeof( ht ));	// initialize to all 0s
	return ht;
	 */
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

// EXAMPLE HASH FUNCTION
/* Compute and return the bucket to which the string str hashes. */
// [[[[ You should use the hash function discussed in class ]]]
unsigned int hash(const char *str)
{
	int i;
	unsigned int h = 0U;
	for (i = 0; str[i] != '\0'; i++)
		h = h * HASH_MULTIPLIER + (unsigned char) str[i]; // unsd int??
	return h % htsize;
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

/*
 * Destroy the hash table Table by freeing all the space allocated to the table.
 */
void ht_destroy(Node **Table)
{
	int i;
	Node *p, *nextp;
	
	for (i = 0; i < htsize; i++) {
		for (p = Table[i]->first; p != NULL; p = nextp) {
			nextp = p->next;
			free(p->word);
			free(p);
		}
		free(Table[i]);
		// Table[i] = NULL;
	}
	return;
}