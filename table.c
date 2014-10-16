/* automata
 *
 * Copyright 2014 Towry Wang (http://towry.me)
 * See License and Copyright notice in automata/main.c 
 */

#include "table.h"
#include <assert.h>
#include <string.h>

#define next (cur < len ? input[cur+1] : '\0')

/* forward declaration */
static void table_add_transition(table_t *, transition_t *);
static void table_trans_resize(table_t *, size_t);
static transition_t* transition_new();

/* global variables */
static char ts_state;
static char ts_lexme;
static char ts_state_next;

void table_init(table_t *t)
{
	t->len = 10;
	t->num = 0;
	t->trans_ary = xcalloc(t->len, transition_t*);
	t->state_start = 0;
}

void table_destroy(table_t *t)
{
	int i;
	for (i = 0; i < t->num; i++) {
		xfree(t->trans_ary[i]);
	}
	xfree(t->trans_ary);
}

void table_construct(table_t *t, const char *input)
{
	assert(t != NULL);
	int after_state = 0;
	int len;
	int cur = 0;
	char c;

	transition_t* ts;

	len = strlen(input);
	while (cur < len) {
		c = input[cur];
		switch (c) {
			case ' ':
				break;
			case '{':
				ts_lexme = next;
				break;
			case ':':
				if (after_state && next != '{') {
					ts_state_next = next;
					ts = transition_new();
					table_add_transition(t, ts);
				}
				break;
			case ',':
				if (after_state) {
					ts_lexme = next;
				}
				break;
			case '}':
				if (after_state) {
					after_state = 0;
				}
				break;
			default:
				if (! after_state && next == ':') {
					after_state = 1;
					ts_state = c;
				}
				break;
		}
		cur++;
	}
}

static transition_t* transition_new()
{
	transition_t* ts;
	ts = xmalloc(transition_t);
	assert(ts != NULL);
	ts->state = ts_state - '0';
	ts->lexme = ts_lexme;
	ts->state_next = ts_state_next - '0';
	
	return ts;
}

static void table_add_transition(table_t *t, transition_t *ts)
{
	if (t->num == t->len) {
		table_trans_resize(t, 10);
	}

	t->trans_ary[t->num++] = ts;
}

static void table_trans_resize(table_t *t, size_t n)
{
	assert(n >= 0);
	realloc(t->trans_ary, sizeof(transition_t*) * (t->len + n));
}

#ifdef TEST_TABLE_INIT

int main()
{
	table_t table;
	table_init(&table);

	assert(table.len == 10);

	return(0);
}
#endif /* TEST_TABLE_INIT */
