
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
	pc = (opcode & 0x0FFF);
}

void OP_2nnn()
{
	stack[sp] = pc;
	sp++;
	pc += (opcode & 0x0FFF);
}

void OP_3xkk()
{
	pc += (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) ? 4 : 2;
}

void OP_4xkk()
{
	pc += (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) ? 4 : 2;
}

void OP_5xy0()
{
	pc += (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) ? 4 : 2;
}

void OP_6xkk()
{
	V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
	pc += 2;
}

void OP_7xkk()
{
	V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
	pc += 2;
}

void OP_8xy0()
{
	V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy1()
{
	V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy2()
{
	V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy3()
{
	V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy4()
{
	V[0xF] = (V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4] > 0xFF) ? 1 : 0;
	V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy5()
{
	V[0xF] = (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) ? 1 : 0;
	V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void OP_8xy6()
{
	V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x0001;
	V[(opcode & 0x0F00) >> 8] >>= 1;
	pc += 2;
}

void OP_8xy7()
{
	V[0xF] = (V[(opcode & 0x00F0) >> 8] > V[(opcode & 0x0F00) >> 4]) ? 1 : 0;
	V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void OP_8xyE()
{
	V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
	V[(opcode & 0x0F00) >> 8] <<= 1;
	pc += 2;
}

void OP_9xy0()
{
	pc += (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) ? 4 : 2;
}

void OP_Annn()
{
	I = (opcode & 0x0FFF);
	pc += 2;
}

void OP_Bnnn()
{
	pc = (opcode & 0x0FFF) + V[0];
}

void OP_Cxkk()
{
	V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
	pc += 2;
}

void OP_Dxyn()
{
	// TODO
	pc += 2;
}

void OP_ExA1()
{
	pc += (key[V[(opcode & 0x0F00) >> 8]] == 0) ? 4 : 2;
}

void OP_Ex9E()
{
	pc += (key[V[(opcode & 0x0F00) >> 8]] != 0) ? 4 : 2;
}

void OP_Fx07()
{
	V[(opcode & 0x0F00) >> 8] = delay_timer;
	pc += 2;
}

void OP_Fx0A()
{
	bool isKeyPressed = false;

	for (int i = 0; i < 16; i++) {
		if (key[i] != 0) {
			V[(opcode & 0x0F00) >> 8] = i;
			isKeyPressed = true;
			break; // Interrompo il for al primo tasto trovato
		}
	}

	if (!isKeyPressed)
		return; // Perché così ripeto il cycle

	pc += 2;
}

void OP_Fx15()
{
	delay_timer = V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void OP_Fx18()
{
	sound_timer = V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void OP_Fx1E()
{
	V[0xF] = (I + V[(opcode & 0x0F00) >> 8] > 0xFFF) ? 1 : 0;
	I += V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void OP_Fx29()
{
	// Moltiplico per 0x5 per raggiungere il carattere corrispondente
	I = V[(opcode & 0x0F00) >> 8] * 0x5; 
	pc += 2;
}

void OP_Fx33()
{
	memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
	memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
	memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
	pc += 2;
}

void OP_Fx55()
{
	for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
		memory[I + i] = V[i];
	}

	pc += 2;
}

void OP_Fx65()
{
	for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
		V[i] = memory[I + i];
	}

	pc += 2;
}