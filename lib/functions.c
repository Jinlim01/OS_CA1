#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>

//reference from lecture note on moodle
void get_input(unsigned char *physicalAdd, unsigned char *diskMemory){
		unsigned int input;
		while(1){
				printf("Please input hexadecimal: ");
				scanf("%04x", &input);
				printf("\n\tAddress translated: 0x%04x\n\n", input);
				//getting offset
				unsigned int offset_mask = 0x00FF;
				unsigned int offset = input & offset_mask;
				//getting vpn
				unsigned int vpn = input >> OFFSET_BITS;
				//physical frame number, getting address from page table
				unsigned int pfn = physicalAdd[vpn];

				printf("\tGetting offset from address input:\n");
				printf("\t\t-offset : 0x%x\n", offset);
				printf("\n\tVirtual Page Number");
				printf("\n\t\t-VPN is 0x%x\n", vpn);
				printf("\n\tPhysical Frame Number");
				printf("\n\t\t-PFN is 0x%x\n", pfn);

				if(physicalAdd[vpn+256]==0){
					swap(physicalAdd, diskMemory, pfn, vpn);
				}else{
					//shows the content
					unsigned int address = pfn << OFFSET_BITS;
					address |= offset;
					unsigned char content = physicalAdd[address];
					printf("\n\tPhysical Memory Address");
					printf("\n\t\t-Address: 0x%x\n", address);
					printf("\n\tData Stored");
					printf("\n\t\t-Data: %c\n", content);
					printf("\n--------------------------------------------------------------------------------------\n");
				}
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
		for(int i = 0; i < MAIN_MEMORY; ++i){
		   //when address reaches 256, frame number +1
        if(a==PAGE_SIZE){
            frame_number++;
            //initialize address to 0
            a=0;
        }
        char content = (rand() % (216 - 33)) + 33;
        if(i >= data_frame_number*PAGE_SIZE && i < data_frame_number*PAGE_SIZE + number){
  					//fprintf(outputMemory, "0x%04x\t\t\t%d\t\t\t\t%c\n", i, frame_number, content);
            physicalAdd[i] = content;
            if(frame_number != f){
							physicalAdd[entry_index] = frame_number-1;
							physicalAdd[entry_index + PAGE_SIZE] = 1;
							f = frame_number;
							fprintf(outputPageTable, "0x%02x\t\t0x%02x\t\tTRUE\n", entry_index, physicalAdd[entry_index]);
							entry_index++;
            }
        }else{
        		physicalAdd[i] = ' ';
						//fprintf(outputMemory, "0x%02x\t\t\t%d\n", i, frame_number);
        }
        a++;
    }

		//Output page table file
		for(int i=entry_index; i<256;i++){
			physicalAdd[i] = ' ';
			physicalAdd[i + PAGE_SIZE] = 0;
			fprintf(outputPageTable, "0x%02x\t\t\t\t\t\tFALSE\n",i);
		}

		//Assign page table into physcial_memory.txt
		frame_number=0;
		a=0; 
		for(int i = 0; i < MAIN_MEMORY; ++i){
       //when address reaches 256, frame number +1
       if(a==PAGE_SIZE){
           frame_number++;
           //initialize address to 0
           a=0;
        }
			if(i < 512){
				fprintf(outputMemory, "0x%04x\t\t\t%d\t\t\t\t0x%04x\n", i, frame_number, physicalAdd[i]);
			}else{
				fprintf(outputMemory, "0x%04x\t\t\t%d\t\t\t\t%c\n", i, frame_number, physicalAdd[i]);
			}
		a++;
    }

    fclose(outputMemory);
    fclose(outputPageTable);
}

//Assign Disk Memory
void assignDiskMemory(unsigned char *diskMemory, unsigned char *physicalAdd){
	FILE *outputDiskMemory;
	char disk_memory[] = "./data/disk_memory.txt";
	outputDiskMemory = fopen(disk_memory, "w");
	fprintf(outputDiskMemory, "Address\t|\tFrame\t|\tContent\n");

	for(int i = 0; i < DISK_MEMORY_SIZE; i++){
		char content = (rand() % (216 - 33)) + 33;
		diskMemory[i] = content;
		fprintf(outputDiskMemory, "0x%03x\t\t0x%02x\t\t%c\n", i,(int) i/256,diskMemory[i]);
	}

	int  assigned=0;
	for(int x = 0; x < 256 && assigned == 0; x++){
		if(physicalAdd[x]== ' '){
			printf("\nPage number that mapped to the disk: %x\n", x);
			physicalAdd[x]=0x00;
			physicalAdd[x+1]=0x01;
			physicalAdd[x+PAGE_SIZE]=0;
			physicalAdd[x+1+PAGE_SIZE]=0;
			assigned=1;
		}
	}
	printf("\n");
	fclose(outputDiskMemory);
}

//Swapping
void swap(unsigned char *physicalAdd, unsigned char *diskMemory, unsigned char pfn, unsigned char vpn){
	unsigned int available_memory=512;
	for(int i = 512; i < MAIN_MEMORY ; i++){
		if(physicalAdd[i] == ' '){
			available_memory = i;
			i=MAIN_MEMORY;
		}else{
			i=i+256;
		}
	}

	int x = pfn * 256 ;
	for(int i=available_memory; i< available_memory+256;i++){
		physicalAdd[i] = diskMemory[x];
		x++;
	}
	physicalAdd[vpn] = (int)available_memory/256;
	physicalAdd[vpn + 256] = 0x01;

	printf("\n\n--------------------------------------------------------------------------------------\n");
	printf("\nPerform Swapping...........");
	printf("\n\n--------------------------------------------------------------------------------------\n");
}
