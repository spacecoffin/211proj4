//
//  scratch.c
//  211proj4
//
//  Created by spacecoffin on 11/16/14.
//  Copyright (c) 2014 spacecoffin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _list_t_ {
	char *string;
	struct _list_t_ *next;
} list_t;

typedef struct _hash_table_t_ {
	int size;       /* the size of the table */
	list_t **table; /* the table elements */
} hash_table_t;

hash_table_t *create_hash_table(int size)
{
	hash_table_t *new_table;
	int i;
	
	if (size<1) return NULL; /* invalid size for table */
	
	/* Attempt to allocate memory for the table structure */
	if ((new_table = malloc(sizeof(hash_table_t))) == NULL) {
		return NULL;
	}
	
	/* Attempt to allocate memory for the table itself */
	if ((new_table->table = malloc(sizeof(list_t *) * size)) == NULL) {
		return NULL;
	}
	
	/* Initialize the elements of the table */
	for(i=0; i<size; i++) new_table->table[i] = NULL;
	
	/* Set the table's size */
	new_table->size = size;
	
	return new_table;
}

int main(void)
{
	hash_table_t *my_hash_table;
	int size_of_table = 12;
	my_hash_table = create_hash_table(size_of_table); // how the fuck is this valid?
	
	return 0;
}