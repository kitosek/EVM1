#include "SimpleComputer.h"
int main ()
{
	mt_clrscr ();
	MemoryPrint();
	FlagPrint();
	KeysPrint();
	mt_gotoXY (11,6);
	mt_getscreensize ();
	mt_setbgcolor (Red);
	mt_setfgcolor (Blue);
	mt_gotoXY (20,0);
}
