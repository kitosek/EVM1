#ifndef simplcomp_h
#define simplcomp_h

#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define SIZE 100

#define OVERFLOW 1
#define ZERO_ERR 2
#define OUT_OF_MEM 3
#define FREQ_ERR 4
#define COMMAND_ERROR 5

struct wimsize {
unsigned short ws_row;
unsigned short ws_col;
unsigned short ws_xpixel;
unsigned short ws_ypixel;
}ws;
enum colors { Dark, Red, Green, Yellow, Blue, Black, Cyan, White, Standart = 9};

int memory[SIZE];
int flags;
int  value;

void errorHandler(int errorNum);
int sc_memoryInit();
int sc_memorySet(int adress, int value);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);

int mt_clrscr ();
int mt_gotoXY (int x, int y);
int mt_getscreensize ();
int mt_setfgcolor (enum colors C);
int mt_setbgcolor (enum colors C);
void MemoryPrint();
void FlagPrint();
void KeysPrint();
#endif

