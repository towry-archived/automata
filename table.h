/* automata
 *
 * Copyright 2014 Towry Wang (http://towry.me)
 * See License and Copyright notice in automata/main.c file 
 */

#ifndef _TABLE_H
#define _TABLE_H

#include <stdio.h>
#include <stdlib.h>

#define xmalloc(type) (type*)malloc(sizeof(type))
#define xcalloc(n, type) (type*)calloc(n, sizeof(type))
#define xfree(p) free(p)

typedef struct table_s table_t;
typedef struct transition_s transition_t;

struct table_s 
{
	size_t len;
	int num;
	transition_t *(*trans_ary);
	int state_start;
	int *state_end;
};

struct transition_s 
{
	int state;
	char lexme;
	int state_next;
};

void table_init(table_t *);
void table_destroy(table_t *);
void table_construct(table_t *, const char *);
#endif
