/* automata
 *
 * Copyright 2014 Towry Wang (http://towry.me)
 * See License and Copyright notice in automata/main.c 
 */

#ifndef _DFA_H
#define _DFA_H

#include "table.h"

int dfa(const char *, table_t *);
int accept(const char, table_t *);
#endif
