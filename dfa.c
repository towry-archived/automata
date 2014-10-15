/* automata
 *
 * Copyright 2014 Towry Wang (http://towry.me)
 * See License and Copyright notice in automata/main.c 
 */

#include "dfa.h"
#include "table.h"

static int current;

int dfa(const char *buf, table_t *t)
{
	int len = sizeof(buf);
	int i = 0;
	char c;

	current = t->state_start;

	while ( i < len) {
		c = buf[i++];
		if (c == ' ') continue;
		if (accept(c, t) != 0) {
			return -1;
		}
	}

	if (current == t->state_end[0])
		return 0;
	else
		return -1;
}


int accept(const char c, table_t *t)
{
	int i = 0;
	transition_t *ts;

	for (; i < t->num; i++) {
		ts = t->trans_ary[i];
		// printf("%d:%c:%d|%c:%d\n", ts->state, ts->lexme, ts->state_next, c, current);
		if (ts->state == current && c == ts->lexme) {
			/* set current state */
			current = ts->state_next;
			return 0;
		}
	}

	return -1;
}
