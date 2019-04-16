#include "SimpleComputer.h"

int sc_memoryInit()
{
	
	for(int i = 0; i < SIZE; i++)
	{
		memory[i]=0;
	}
	return 0;
}

int sc_memorySet(int address, int value)
{
	if(address < 0 || address >= SIZE)
	{
		sc_regSet(OUT_OF_MEM, 1);
		errorHandler(1);
	}
	else
	{
		memory[address] = value;
	}
	return 0;
}

int sc_memoryGet(int address, int *value)
{
	if(address < 0 || address >= SIZE)
	{
		sc_regSet(OUT_OF_MEM, 1);
		errorHandler(1);
	}
	else
	{
		*value = memory[address];
	}
	return 0;
}

int sc_memorySave(char *filename)
{
	FILE *file = fopen(filename, "wb");
	if(!file)
	{
		errorHandler(2);
	}
	else
	{
		fwrite(memory, sizeof(int), SIZE, file);
	}
	fclose(file);
	return 0;
}

int sc_memoryLoad(char *filename)
{
	FILE *file = fopen(filename, "rb");
	if(!file)
	{
		errorHandler(3);
	}
	else
	{
		fread(memory, sizeof(int), SIZE, file);
	}
	fclose(file);
	return 0;
}

int sc_regInit()
{
	flags = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{
    if ((reg >= 0) && (reg <= 6))
    {
		if (value == 0)
		{
			flags &= (~(1 << (reg - 1)));
			return 0;
		}
		else if (value == 1)
		{
			flags |= (1 << (reg - 1));
			return 0;
		}
		else
		{
			errorHandler(4);
		}
	}
	else
	{
		errorHandler(5);
	}
	return 0;
}

int sc_regGet(int reg, int *value)
{
    if ((reg >= 0x01) && (reg <= 0x10))
    {
		*value = flags >> (reg - 1) & 0x1;
    }
    else
    {
		errorHandler(5);
	}
        return 0;
}

int sc_commandEncode(int command, int operand, int *value)
{
    if ( command<=0xa || command>=0x4c|| operand < 0 || operand > 127 )
    {
	sc_regSet(COMMAND_ERROR, 1);
        errorHandler(6);
    }
    int temp = 0x00;
    temp |= command;
    temp <<= 7;
    temp |= operand;
    *value = temp;
    return 0;
}

int sc_commandDecode(int value, int *command, int *operand)
{
    if (value >> 14 != 0x0)
    {
        sc_regSet(COMMAND_ERROR, 1);
        errorHandler(6);
    }
	/*else if (!(command == 0xa) || !(command == 0xb) || !(command == 0x15) || !(command == 0x1e) || operand < 0 || operand > 127 || !(command == 0x1f) || !(command == 0x20) || !(command == 0x21))
    {
	sc_regSet(COMMAND_ERROR, 1);
        errorHandler(6);
    }*/
	else if ( ((!(*command>=0x10 && *command<=0x11)) && (!(*command>=0x20 && *command<=0x21 )) && (!(*command>=0x30 && *command<=0x33 )) && (!(*command>=0x40 && *command<=0x43 )) && (!(*command>=0x51 && *command<=0x76 ))) || *operand < 0 || *operand > 127 )
	{
		printf("%d",*command);
		sc_regSet(COMMAND_ERROR, 1);
        errorHandler(6);
	}
	else
	{

		*operand = (int) (value & 0x7F);
   		*command = (int) (value >> 7);

	}
    return 0;
}

void errorHandler(int errorNum)
{
	printf("An error has been caught (code: %d):\n", errorNum);
	switch(errorNum)
	{
		case 1:
			printf("Out of memory.\n\n");
			break;
			
		case 2:
			printf("Cannot save RAM\n\n");
			break;
			
		case 3:
			printf("Cannot load a RAM\n\n");
			break;
			
		case 4:
			printf("Wrong value.\n\n");
			break;
			
		case 5:
			printf("Wrong register.\n\n");
			break;
			
		case 6:
			printf("Wrong command/operand\n\n");
			break;
			
		}
}

