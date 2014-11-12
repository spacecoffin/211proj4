//
//  hashtable.c
//  211proj4
//
//  Created by spacecoffin on 11/11/14.
//  Copyright (c) 2014 spacecoffin. All rights reserved.
//

#include <stdio.h>

// Type definition for a node
struct NodeType {
	char *word;		// a string representing the word
	int count;		// the # of times that word appears in the text
	struct NodeType *next;	// pointer to next node in list (if it exists)
};
typedef struct NodeType Node;

// Function prototypes
Node **ht_create(void);

int htsize;			// size (in buckets) of hash table

int main(int argc, char *argv[])
{
	/* Hash table size is a command-line argument, in argv[1] */
	if (argc <= 1) {
		printf("ERROR: Usage: %s table_size\n", argv[0]);
		return 1;
	}
	htsize = atoi(argv[1]);
}