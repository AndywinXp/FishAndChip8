

#include "Chip8CPU.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void OP_DUM()
{
	printf("NO_OP\n");
}

void(*Dummy[2])() =
{
	OP_DUM, OP_DUM
};

int main() {
	printf("bubu %d\n", pc);
	init();
	Dummy[0+1]();
	printf("bubu %d\n", pc);
	getchar();
}