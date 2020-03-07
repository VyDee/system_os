#include "io.h"
#include "mem_man.h"
#include "frame_buffer.h"
#include "string.h"
#include "segments.h"
#include "interrupts.h"

int main() 
{
    
    segments_install_gdt();
	interrupts_install_idt();

    fb_clear();
    // char* a = get_mem(11);
    // strcpy(a,"hello world",11);
    // a[11] = '!';
    // fb_write_string(0, a ,12);
    clearAllMemory();

    
    return 0;
}