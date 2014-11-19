/* OLD Function prototypes */
void print(char *Table[], int n);		// replaced by ht_print
void empty(char *Table[], int n);		// replaced by ht_empty

// NEW Func prototypes

void ht_print(Node **Table);

int main(int argc, char *argv[])
{
	int n;			// current number of strings in table
	int i;			// loop variable
		
	/* Initialize current number of strings in table to 0 */
	n = 0;
	
	print(Table, n);		// print table
	empty(Table, n);		// empty table
	return 0;
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

