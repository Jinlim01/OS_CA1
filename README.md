# OS_CA1
Description:
This project created a platform for user to perform address translation with user input.

In my page table, it contains frame number and present bit.
 -Frame number is use to map and locate physical address.
 -Present bit is use to check the memory stored in disk(0 = FALSE) or physical memory(1 = TRUE)
 
# Complie
Start the project, run
	./dist/stimulate
	
#Authors
Yuan Jin Lim  

#Acknowledgments
1. Dkit Moodle 2018-2019 Lecture Note - Resource: Makefile Version 2 (Variables)
	https://2019-moodle.dkit.ie/pluginfile.php/562089/mod_resource/content/2/Makefile

2. Dkit Moodle 2018-2019 Lecture Note - C Exercise: Extract VPN and offset from 32bit virtual address (4KiB page size)
	https://2019-moodle.dkit.ie/pluginfile.php/567340/mod_resource/content/2/32bit-address-parts.c

3. Dkit Moodle 2018-2019 Lecture Note - C Exercise: Reconstruct 32bit physical address from PFN and offset (4KiB page size)
	https://2019-moodle.dkit.ie/pluginfile.php/567342/mod_resource/content/2/32bit-address-parts-reconstruct.c
	
