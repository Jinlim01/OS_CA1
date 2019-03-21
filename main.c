#include <stdio.h>
#include "lib/functions.h"

int main(){
	unsigned char * physicalAdd = malloc(sizeof(char)*MAIN_MEMORY);
	initialize(physicalAdd);
	get_input(physicalAdd);
	free(physicalAdd);
	return 0;
}
