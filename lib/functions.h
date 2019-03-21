#ifndef functions_h
#define functions_h

#define MAIN_MEMORY 65536
#define MAX_BYTES 20480
#define MIN_BYTES 2048
#define DISK_MEMORY_SIZE 512
#define PAGE_SIZE 256
#define OFFSET_BITS 8

//typedef enum{
//	true,
//	false
//} bool;

void *initialize(unsigned char *physicalAdd);
void get_input(unsigned char *physicalAdd);

#endif
