
#include "Chip8CPU.h"


void (*Chip8Table[OPCODE_HIGH_NIBBLE])() = 
{
	CLSRET, OP_1nnn, OP_2nnn, OP_3xkk, OP_4xkk, OP_5xy0, OP_6xkk, OP_7xkk,
	ARITHM, OP_9xy0, OP_Annn, OP_Bnnn, OP_Cxkk, OP_Dxyn, OP_NOP , FINSTR1
};

void (*Chip8TableClsRet[OPCODE_CLS_RET])() =
{
	OP_00E0, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_00EE, OP_ILLG
};

void(*Chip8TableArithmetic[OPCODE_ARITHMETIC])() =
{
	OP_8xy0, OP_8xy1, OP_8xy2, OP_8xy3, OP_8xy4, OP_8xy5, OP_8xy6, OP_8xy7,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_8xyE, OP_ILLG
};

void(*Chip8TableKeybCheck[OPCODE_KEYB_CHECK])() =
{
	OP_ILLG, OP_ExA1, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_Ex9E, OP_ILLG
};

// Livello 1 di scelta, possiamo discriminare le istruzioni
// per l'ultimo nibble, ad eccezione di Fx15, Fx55 e Fx65
// per i quali verrà implementato un secondo livello di scelta
// per le F Instructions (l'alternativa sarebbe stata un array
// di 255 puntatori a funzione, confusionario).
void(*Chip8TableFInstructionsLevel_1[OPCODE_F_INSTRUCTIONS])() =
{
	OP_ILLG, OP_ILLG, OP_ILLG, OP_Fx33, OP_ILLG, FINSTR2, OP_ILLG, OP_Fx07,
	OP_Fx18, OP_Fx29, OP_Fx0A, OP_ILLG, OP_ILLG, OP_ILLG, OP_Fx1E, OP_ILLG
};

// Livello 2 di scelta per le istruzioni Fx15, Fx55 e Fx65. 
void(*Chip8TableFInstructionsLevel_2[OPCODE_F_INSTRUCTIONS])() =
{
	OP_ILLG, OP_Fx15, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG
};

void ARITHM()
{
	Chip8TableArithmetic[(opcode & 0x000F)]();
}

void CLSRET()
{
	Chip8TableClsRet[(opcode & 0x000F)]();
}

void KEYINST() 
{
	Chip8TableKeybCheck[(opcode & 0x000F)]();
}

void FINSTR1()
{
	Chip8TableFInstructionsLevel_1[(opcode & 0x000F)]();
}

void FINSTR2()
{
	Chip8TableFInstructionsLevel_2[(opcode & 0x00F0 >> 4)]();
}

void OP_NOP()
{
	printf("Unimplemented opcode: 0x%X\n", opcode);
}

void OP_ILLG()
{
	printf("Illegal opcode: 0x%X\n", opcode);
}

void OP_00E0()
{
	for (int i = 0; i < (64 * 32); i++) 
	{
		gfx[i] = 0x0;
	}
		
	drawReadyFlag = true;
	pc += 2;
}

void OP_00EE()
{
	pc = stack[sp];
	sp--;
	pc += 2;
}

void OP_1nnn()
{

}

void OP_2nnn()
{

}

void OP_3xkk()
{

}

void OP_4xkk()
{

}

void OP_5xy0()
{

}

void OP_6xkk()
{

}

void OP_7xkk()
{

}

void OP_8xy0()
{

}

void OP_8xy1()
{

}

void OP_8xy2()
{

}

void OP_8xy3()
{

}

void OP_8xy4()
{

}

void OP_8xy5()
{

}

void OP_8xy6()
{

}

void OP_8xy7()
{

}

void OP_8xyE()
{

}

void OP_9xy0()
{

}

void OP_Annn()
{

}

void OP_Bnnn()
{

}

void OP_Cxkk()
{

}

void OP_Dxyn()
{

}

void OP_ExA1()
{

}

void OP_Ex9E()
{

}

void OP_Fx07()
{

}

void OP_Fx0A()
{

}

void OP_Fx15()
{

}

void OP_Fx18()
{

}

void OP_Fx1E()
{

}

void OP_Fx29()
{

}

void OP_Fx33()
{

}

void OP_Fx55()
{

}

void OP_Fx65()
{

}