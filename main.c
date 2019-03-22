#include <stdio.h>
#include <stdlib.h>
#include "lib/functions.h"

int main(){
	unsigned char *physicalAdd = malloc(sizeof(char) *MAIN_MEMORY);
	unsigned char *diskMemory = malloc(sizeof(char) *DISK_MEMORY_SIZE);
	initialize(physicalAdd);
	assignDiskMemory(diskMemory, physicalAdd);
	get_input(physicalAdd,diskMemory);
	free(physicalAdd);
	free(diskMemory);
	return 0;
}


