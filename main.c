/* automata
 *
 * Copyright 2014 Towry Wang (http://towry.me)
 * Distributed under MIT License
 * http://towry.mit-license.org/
 */

#include "table.h"
#include "dfa.h"

int main()
{
	table_t table;
	table_init(&table);

	const char *table_str = "0:{0:1,1:0},1:{0:2,1:3},2:{0:2,1:3},3:{1:0,0:1}";
	int state_end[2] = {2, 3};
	table.state_end = state_end;
	table_construct(&table, table_str);

	const char *input = "011111";
	int rec = dfa(input, &table);
	if (rec == 0) {
		printf("accepted: %s\n", input);
	} else {
		printf("rejected: %s\n", input);
	}

	const char*another_input = "0100";
	rec = dfa(another_input, &table);
	if (rec == 0) {
		printf("accepted: %s\n", another_input);
	} else {
		printf("rejected: %s\n", another_input);
	}

	table_destroy(&table);

	return(0);
}
