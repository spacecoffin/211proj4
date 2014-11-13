#include <ctype.h>

/* OLD Function prototypes */
int insert(char *word, char *Table[], int n);	// replaced by ht_insert
void print(char *Table[], int n);		// replaced by ht_print
void empty(char *Table[], int n);		// replaced by ht_empty

// NEW Func prototypes
unsigned int hash(const char *str);
int ht_insert(Node **Table, const char *word);
void ht_print(Node **Table);

int main(int argc, char *argv[])
{
	int table_size;		// table size, a command-line argument
	int n;			// current number of strings in table
	int i;			// loop variable
	
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

