#include "mem_man.h"
#include "frame_buffer.h"
#include "io.h"

/*char pointer*/
char* memStart = (char*) 0x00200000; //start at 2MB
char* memEnd = (char*) 0x107FFFF;
char* dataStart = (char*) 0x1080000;
char* dataEnd = (char*) 0x1F00000; // start at 31.99MB

void clearAllMemory()
{
    for (char* c = memStart; c <= (char*)0x1F00000; c++)
    {
        *c = 0;
    }
}

void free_mem(char* startAddress, int num)
{
    for (char* c = startAddress; c < (startAddress + num); c++)
    {
        *c = 0;
    }
}

void mark_mem(char* start, int num)
{
    for(char* c = start; c < (start+num); c++)
    {
        *c = 1;
    }
}

int mem_check (char* start, int num)
{
    for (char* c = start; c < (start + num); c++)
    {
        if(*c == 1)
        {
            return 0; //this base addess does not work
        }
    }
    return 1; // this base address will work
}

char* get_mem (int num)
{
    // char* c = (char*) 0x00300000;
    // c[0]= 'a';
    // fb_write_string(80*2*5, c ,5);

    int offset = (int)dataStart - (int)memStart;
    for (char* c = memStart; c <= memEnd; c++)
    {
        if(*c == 0)
        {
            if(mem_check(c,num))
            {
                mark_mem(c,num);
                return c + offset;
            }
        }
    }
    return (char*) 0xDEADBEEF;
}