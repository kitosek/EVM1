

#include "SimpleComputer.h"



int mt_clrscr ()
{
	printf("\E[H\E[J");
	return 0;
}
int mt_gotoXY (int x, int y)
{
	printf("\E[%d;%dH",x,y );
	return 0;
}
int mt_getscreensize ()
{
	if (!ioctl(1, TIOCGWINSZ, &ws))
	{
	printf ("Получен размер экрана.\n");
	printf ("Число строк – %d\nЧисло столбцов – %d\n", ws.ws_row, ws.ws_col);
	return 0;
	} 
	else 
	{
		fprintf (stderr, "Ошибка получения размера экрана.\n");
		return -1;
	}
}
int mt_setfgcolor (enum colors C)
{
	printf("\E[3%dm example",C);
	return 0;
}
int mt_setbgcolor (enum colors C)
{
	printf("\E[4%dm",C);
	return 0;
}

void MemoryPrint()
{
	int j=0;
	int k=1;
	sc_memorySet(20,11);
	for (int i=1;i<=100;i++)
	{
	
		sc_memoryGet(i-1,&value);
		printf("+%-04x",value);
		j++;
		if (j==10)
		{
			mt_gotoXY (k+1, 1);
			j=0;
			k++;
		}
		
	}
	printf("\n");
}

void FlagPrint()
{
	mt_gotoXY (10,50);

	sc_regGet(OVERFLOW,&value);
	if (value==0) printf("O");
	sc_regGet(ZERO_ERR,&value);
	if (value==0) printf("Z ");
	sc_regGet(OUT_OF_MEM,&value);
	if (value==0) printf("OM ");
	sc_regGet(FREQ_ERR,&value);
	//if (value==0) printf("F ");
	sc_regGet(COMMAND_ERROR,&value);
	if (value==0) printf("C ");
	
}

void KeysPrint()
{
	mt_gotoXY (11,31);
	printf("l - load");
	mt_gotoXY (12,31);
	printf("s - save");
	mt_gotoXY (13,31);
	printf("r - run");
	mt_gotoXY (14,31);
	printf("t - step");
	mt_gotoXY (15,31);
	printf("i - reset");
	mt_gotoXY (16,31);
	printf("F5 - accumulator");
	mt_gotoXY (17,31);
	printf("F6 - instuctionCounter");
}
