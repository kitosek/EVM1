#include "SimpleComputer.h"

void print(int i, int n)
{
	for(; i < n; i++)
		printf("%x ", memory[i]);
}


int main(){

	int command = 0x21;
	int  operand = 0x7F;
	char *fileSave = "memSave";
	char *fileLoad = fileSave;
	sc_regInit();
	sc_memoryInit();
	printf("\n\nMemory: ");
	print(0, SIZE);
	printf("\n\n");

	printf("Memory swap (0 and 6 positions)\n");
	sc_memorySet(0, 6);
	sc_regGet(OUT_OF_MEM, &value);
	printf("OUT_OF_MEM: %d\n", value);
	sc_memorySet(6, 0);
	printf("Memory: "); print(0, 8);

	sc_memoryGet(0, &value);
	printf("\n\nmemGet value (0 pos): %d\n\n", value);

	sc_memorySave(fileSave);
	printf("Memory has been saved in file %s.\n", fileSave);
	sc_memoryLoad(fileLoad);
	printf("Memory has been loaded from file %s.\n\n", fileLoad);


	printf("Set OVERFLOW to 1.\n");
	sc_regSet(OVERFLOW , 1);
	sc_regGet(OVERFLOW , (int *)&value);
	printf("OVERFLOW FLAG: %d\n", value);
	printf("Set OVERFLOW to 0.\n");
	sc_regSet(OVERFLOW , 0);
	sc_regGet(OVERFLOW , (int *)&value);
	printf("OVERFLOW FLAG: %d\n\n", value);
	
	sc_commandEncode(command, operand, &value);
	printf("Encode Command: %x and Operand: %x in value: %d\n", command, operand, value);
	sc_commandDecode(value, &command, &operand);
	sc_regGet(COMMAND_ERROR, &value);
	printf("COMMAND_ERROR: %d\n", value);
	if(value != 1)  printf("Decode Comand: %x Operand: %x\n", command, operand);
	return 0;
}
