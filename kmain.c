#include "io.h"
#include "mem_man.h"
#include "frame_buffer.h"
#include "string.h"
#include "segments.h"
#include "interrupts.h"

char* test;

int main() 
{
    clearAllMemory();
    segments_install_gdt();
	interrupts_install_idt();

    interrupt_prompt_string = get_mem(7);
    strcpy(interrupt_prompt_string, "Fish> ",6);
    //strcpy(interrupt_prompt_string,(char*) 50,strlen(interrupt_prompt_string) + 5);

    interrupt_input = get_mem(80*25);
    strcpy(interrupt_input,"\0",1);

    interrupt_output = get_mem(80*25);
    strcpy(interrupt_output,"\0",1);

    fb_clear();
    //fb_write_string(0,interrupt_prompt_string,strlen(interrupt_prompt_string));
    //fb_write_int(0,(int) &interrupt_input);
    fb_write_string(0,interrupt_prompt_string, strlen(interrupt_prompt_string));
    return 0;
}