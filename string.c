#include "string.h"
#include "frame_buffer.h"
#include "mem_man.h"

void strcpy (char* des,char* src, int length)
{
    for (int i = 0; i < length; i++)
    {
        des[i] = src[i];
    }
    des[length] = '\0';
}

void strcpyAtPos (char* des,char* src,int startpos, int endpos)
{
    int i = 0;
    while (startpos != endpos)
    {
        des[i] = src[startpos];
        startpos++;
        i++;
    }
        
    des[i+1] = '\0';
    
}

int strlen(char* src)
{
    int count = 0;
    while (src[count] != '\0')
    {
        count++;
    }
    return count;
}

void strcat (char* dest, char* appendString)
{
    int startNewStringAt = strlen(dest);
    for (int i = 0; i < strlen(appendString); i++)
    {
        dest[startNewStringAt] = appendString[i];
        startNewStringAt++;
    }
    dest[startNewStringAt]='\0';
}

void strshorten(char* src, int shortAmount)
{
    if(strlen(src) >= shortAmount)
    {
        src[strlen(src)-shortAmount] = '\0';
    }
}

int count_char(char* src, char searchChar)
{
    int count = 0;
    for (int i = 0; i < strlen(src); i++)
    {
        if (src[i] == searchChar)
        {
            count ++;
        }
    }
    return count;
}

// hello world 2020

// void strtok(char** destArray,char* src)
// {
//     int countSpace = count_char(src, ' ') +1;
//     char* s = get_mem(countSpace+1);
//     for (int i = 0; i < countSpace; i++)
//     {
//         s[i] = '?';
//     }
//     s[countSpace] = '\0';

//     fb_clear();
//     fb_write_string(0, s, strlen(s));

// }

void strtok(char** destArray,char* src)
{  
    int srclen = strlen(src);
    int pos = 0;
    int copyStartPos = 0;
    int countMem = 0;
    for (int i = 0; i <= srclen; i++)
    {
        if(src[i] != ' ')
        {
            countMem ++;
        }
        else
        {
            destArray[pos]= get_mem(countMem + 1);
            strcpyAtPos(destArray[pos],src,copyStartPos,i);
            countMem = 0;
            copyStartPos = i + 1;
            pos ++;
        }
    }
    destArray[pos]= get_mem(countMem + 1);
    strcpyAtPos(destArray[pos],src,copyStartPos,srclen);
}

