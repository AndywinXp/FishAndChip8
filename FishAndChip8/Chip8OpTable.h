#ifndef CHIP8OPTABLE_H
#define CHIP8OPTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#define OPCODE_HIGH_NIBBLE 16
#define OPCODE_CLS_RET 16
#define OPCODE_ARITHMETIC 16
#define OPCODE_KEYB_CHECK 16
#define OPCODE_F_INSTRUCTIONS 16

// TODO: Ma quasi quasi una classe apposta non serve, non è indispensabile,
// mi dà solo casini

class Chip8OpTable {

public:
	Chip8OpTable();
	~Chip8OpTable();

	// Tabella principale contenente gli OPCODE raggruppati 
	// per il primo nibble (primi 4 bit a sinistra)
	void(*Chip8Table[OPCODE_HIGH_NIBBLE]) (unsigned short op);

private:
	// Tabella per le operazioni CLS (0x00E0) e RET (0x00EE)
	void(*Chip8TableClsRet[OPCODE_CLS_RET]) (unsigned short op);

	// Tabella per le operazioni aritmetiche a 0x8000
	// Nota: le operazioni dalla 8xx9 alla 8xxD, e la 8xxF
	// sono illegali
	void(*Chip8TableArithmetic[OPCODE_ARITHMETIC]) (unsigned short op);

	// Tabella per le operazioni SKP (0xEx9E) e SKNP (ExA1)
	void(*Chip8TableKeybCheck[OPCODE_KEYB_CHECK]) (unsigned short op);

	// Tabella per le operazioni con il primo nibble uguale a F
	void(*Chip8TableFInstructions[OPCODE_F_INSTRUCTIONS]) (unsigned short op);

};

// OPERAZIONI
void OP_NOP(unsigned short op);
void OP_ILLG(unsigned short op);

void CLSRET(unsigned short op);
void OP_000E(unsigned short op);
void OP_00EE(unsigned short op);

void ARITHM(unsigned short op);
void OP_8xy0(unsigned short op);
void OP_8xy1(unsigned short op);
void OP_8xy2(unsigned short op);
void OP_8xy3(unsigned short op);
void OP_8xy4(unsigned short op);
void OP_8xy5(unsigned short op);
void OP_8xy6(unsigned short op);
void OP_8xy7(unsigned short op);
void OP_8xyE(unsigned short op);


#endif