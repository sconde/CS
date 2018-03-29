/* 
 * main.c
 *
 * Define the kernel entrypoint and calls initialization routines.
 * From James Molloy kernel dev tutorial.
 */
#include "types.h"
#include "multiboot.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "paging.h"
#include "kheap.h"
#include "initrd.h"
#include "monitor.h"
#include "kassert.h"

extern uint32_t placement_address;

uint32_t initial_esp;



int kmain(struct multiboot *mboot_ptr, uint32_t initial_stack)
{
    initial_esp = initial_stack;

	/*
	 * Test IDT
	 */
	init_gdt();
	init_idt();


    /*
     * initrd
     */
    // Find the location of our initrd.
    KASSERT(mboot_ptr->mods_count > 0);
    uint32_t initrd_location = *((uint32_t *)mboot_ptr->mods_addr);
    uint32_t initrd_end      = *(uint32_t *)(mboot_ptr->mods_addr+4);
    
    // Do not trample our module with placement address.
    placement_address = initrd_end;

    //uint32_t a = kmalloc(8);     
    initialise_paging(); 

    monitor_write("\n\n");
    // Initialise the initial ramdisk, and set it as the filesystem root.
    fs_root = initialize_initrd(initrd_location);

    // list the contents of /                                                   
    int i = 0;     
    struct dirent *node = 0;    
    while ((node = readdir_fs(fs_root, i)) != 0)  
    {     
        monitor_write("Found file ");           
        monitor_write(node->name);      
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);        
       
        if ((fsnode->flags&0x7) == FS_DIRECTORY)     
        {     
            monitor_write("\n\t(directory)\n");   
        }    
        else 
        {     
            monitor_write("\n\t contents: \"");   
            char buf[256];    
            uint32_t sz = read_fs(fsnode, 0, 256, (uint8_t *)buf);     
            int j;    
            for (j = 0; j < sz; j++)       
                monitor_put(buf[j]);   
            monitor_write("\"\n");    
        }     
        i++;                                                                    
    }
    
    // All initialization calls go in here.
	return 0x12345677;
}
