#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <iostream>


#define OPCODE_HIGH_NIBBLE 16
#define OPCODE_CLS_RET 16
#define OPCODE_ARITHMETIC 16
#define OPCODE_KEYB_CHECK 16
#define OPCODE_F_INSTRUCTIONS 16

// Documentazione: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

// Mappa sistema:
// 0x000 - 0x1FF - Interprete Chip 8
// 0x200 - 0xFFF - ROM e RAM


void cycle(); // Emulazione di un ciclo di CPU
void fetch_decode();
void execute();
void loadROM(); // Caricamento ROM in memoria

/* "The graphics system: The chip 8 has one instruction that draws sprite to the screen.
Drawing is done in XOR mode and if a pixel is turned off as a result of drawing, the VF register is set.
This is used for collision detection.
The graphics of the Chip 8 are black and white and the screen has a total of 2048 pixels (64 x 32).
This can easily be implemented using an array that hold the pixel state (1 or 0)" */
extern unsigned char gfx[64 * 32];

// Keypad (da 0x0 a 0xF)
extern unsigned char key[16];

// Flag che, se settato a true, permette alla CPU di disegnare la grafica
// e in caso contrario di proseguire con i cycle
extern bool drawReadyFlag;



// Ci sono 35 opcode, tutti da due byte
extern unsigned short opcode;
// 4K di memoria
extern unsigned char memory[4096];

// REGISTRI:
// 15 registri general purpose da 8-bit 
// che vanno da V0 a VE (esadecimale)
extern unsigned char V[16];
// Registro index (16-bit: da 0x000 a 0xFFFF)
extern unsigned short I;
// Program counter (12-bit: da 0x000 a 0xFFF)
extern unsigned short pc;

// L'interprete prevede istruzioni che saltano da un pezzo di
// codice ad un altro: serve uno stack per tenere traccia di
// dove si è arrivati nel momento di un salto, per poterci ritornare
extern unsigned short stack[16]; // 16 livelli di stack
extern unsigned short sp; // stack pointer

// Questi timer contano a 60Hz verso il basso quando
// sono settati ad un valore maggiore di zero
extern unsigned short delay_timer;
extern unsigned short sound_timer; // Quando arriva a zero, viene emesso un suono dal buzzer

// Funzione di inizializzazione
void init();



/*----------------------------------------------------------------*/
/*------------------------ TABELLA OPCODE ------------------------*/
/*----------------------------------------------------------------*/


// Tabella principale contenente gli OPCODE raggruppati 
// per il primo nibble (primi 4 bit a sinistra)
extern void(*Chip8Table[OPCODE_HIGH_NIBBLE]) ();

// Tabella per le operazioni CLS (0x00E0) e RET (0x00EE)
extern void(*Chip8TableClsRet[OPCODE_CLS_RET]) ();

// Tabella per le operazioni aritmetiche a 0x8000
// Nota: le operazioni dalla 8xx9 alla 8xxD, e la 8xxF
// sono illegali
extern void(*Chip8TableArithmetic[OPCODE_ARITHMETIC]) ();

// Tabella per le operazioni SKP (0xEx9E) e SKNP (ExA1)
extern void(*Chip8TableKeybCheck[OPCODE_KEYB_CHECK]) ();

// Tabella per le operazioni con il primo nibble uguale a F (primo livello)
extern void(*Chip8TableFInstructionsLevel_1[OPCODE_F_INSTRUCTIONS]) ();

// Tabella per le operazioni con il primo nibble uguale a F (secondo livello)
extern void(*Chip8TableFInstructionsLevel_2[OPCODE_F_INSTRUCTIONS]) ();


/*----------------------------------------------------------------*/
/*---------------------------- OPCODE ----------------------------*/
/*----------------------------------------------------------------*/

// OPERAZIONI
void OP_NOP();
void OP_ILLG();

void CLSRET();
void OP_00E0();
void OP_00EE();

void OP_1nnn();
void OP_2nnn();
void OP_3xkk();
void OP_4xkk();
void OP_5xy0();
void OP_6xkk();
void OP_7xkk();

void ARITHM();
void OP_8xy0();
void OP_8xy1();
void OP_8xy2();
void OP_8xy3();
void OP_8xy4();
void OP_8xy5();
void OP_8xy6();
void OP_8xy7();
void OP_8xyE();

void OP_Annn();
void OP_Bnnn();
void OP_Cxkk();
void OP_Dxyn();

void KEYINST();
void OP_ExA1();
void OP_Ex9E();

void FINSTR1();
void FINSTR2();
void OP_Fx07();
void OP_Fx0A();
void OP_Fx15();
void OP_Fx18();
void OP_Fx1E();
void OP_Fx29();
void OP_Fx33();
void OP_Fx55();
void OP_Fx65();