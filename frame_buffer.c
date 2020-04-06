#include "frame_buffer.h"
#include "io.h"
#include "string.h"
#include "mem_man.h"
/**
 * For the framebuffer,
 *
 * example 0x4128
 * 41: ascii of character
 * 2: foreground color
 * 8: background color
 * hence it is defined as follows.
 *
 * @TODO split them into separate header file.
 */

/* framebuffer mm io */
char* fb = (char *) 0x000B8000;
char* dataSpaceStart = (char*) 0x00300000;

/**
 * display character c on the position i with color fg and bg.
 *
 * @param i the position, 0 for the first line, first col. 16 for the second line.
 * @param c the displayed character
 * @param fg foreground color
 * @param bg background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4 | (bg & 0x0F));
}

/**
 * move the cursor to the given position
 *
 * @param short pos: 16 bit totally
 *      - first 8 bit: the row
 *      - last 8 bit: the colomn
 */
void fb_move_cursor(unsigned short pos) 
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}


void fb_write_string(int offset, char* s, int length)
{
    int i;
    for(i = 0; i < length; i = i + 1)
    {
        fb_write_cell(offset + i*2, s[i], FB_BLACK, FB_GREEN);
    }
}

void fb_clear()
{
    for(int i = 0; i < 80*25; i++)
    {
        fb_write_cell(i*2, ' ', FB_BLACK, FB_BLACK);
    }
}