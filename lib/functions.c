#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>

void get_input(unsigned char *physicalAdd){
		unsigned int input;
		while(1){
				printf("Please input hexadecimal: ");
				scanf("%04x", &input);
				//getting offset
				unsigned int offset_mask = 0x00FF;
				unsigned int offset = input & offset_mask;
				//getting vpn
				unsigned int vpn = input >> OFFSET_BITS;
				//physical frame number, getting address from page table
				unsigned int pfn = physicalAdd[vpn];
				//shows the content
				unsigned int address = pfn << OFFSET_BITS;
				address |= offset;
		 		printf("address: %x\n", address);
		 		unsigned char content = physicalAdd[address];
		 		printf("content: %c\n", content);
		}
}

void *initialize(unsigned char *physicalAdd){
    srand(time(NULL));
    //number of data needed to fill
    int  number = (rand() % (MAX_BYTES - MIN_BYTES)) + MIN_BYTES; 
    FILE *outputMemory, *outputPageTable;
    char phy_memory[] = "./data/physical_memory.txt";
    char page_table[] = "./data/page_table.txt";
    outputMemory = fopen(phy_memory, "w");
    outputPageTable = fopen(page_table, "w");

    fprintf(outputMemory, "Address\t|\tFrame\t|\tContent\n");
		fprintf(outputPageTable, "Page\t|\tFrame\t|\tPresent\n");

    //generate random frame number to start off
    int data_frame_number = (rand() %(256-2-number/256))+2;
    // a = address
    int a = 0;
		int frame_number = 0;
		//use to save frame number with data (incremented)
		int f=data_frame_number;
		//index of page table
		int entry_index = 0;
		for(int i = 0; i <= MAIN_MEMORY; ++i){
        //when address reaches 256, frame number +1
        if(a==PAGE_SIZE){
            frame_number++;
            //initialize address to 0
            a=0;
        }
        char content = (rand() % (216 - 33)) + 33;
        if(i>=data_frame_number*PAGE_SIZE && i<data_frame_number*PAGE_SIZE + number){
            fprintf(outputMemory, "0x%04x\t\t\t%d\t\t\t\t%c\n", i, frame_number, content);
            physicalAdd[i] = content;

            if(frame_number != f){
							physicalAdd[entry_index] = frame_number-1;
							physicalAdd[entry_index + PAGE_SIZE] = 0x01;
							f=frame_number;
							fprintf(outputPageTable, "0x%02x\t\t0x%02x\t\tTRUE\n", entry_index, physicalAdd[entry_index]);
							entry_index++;
            }
        }else{
						fprintf(outputMemory, "0x%02x\t\t\t%d\n", i, frame_number);
        }
        a++;
    }
    for(int i = entry_index; i < 256; i++){
			physicalAdd[entry_index]=' ';
			fprintf(outputPageTable, "0x%02x\t\t\t\t\t\tFALSE\n", entry_index);
			physicalAdd[entry_index + PAGE_SIZE] = 0x00;
			entry_index++;
    }

    fclose(outputMemory);
		return physicalAdd;

}
