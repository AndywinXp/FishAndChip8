
#include "Chip8CPU.h"

unsigned char gfx[64 * 32];

unsigned char key[16];

bool drawReadyFlag;
bool soundReady;

unsigned short opcode;
unsigned char memory[4096];

// REGISTRI:
unsigned char V[16];
unsigned short I;

unsigned short pc;

unsigned short stack[16]; // 16 livelli di stack
unsigned short sp;
unsigned short delay_timer;
unsigned short sound_timer;

unsigned char charset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};



void cycle()
{
	// TODO:
	fetch_decode();
	execute();

	// In realtà dovrebbe scorrere a 60 Hz
	delay_timer -= (delay_timer > 0) ? 1 : 0;
	
	// soundReady è true se sound_timer è 1 (e nel mentre lo decrementa), altrimenti
	// fa un controllo (che farà comunque risultare soundReady = false) di sound_timer > 0,
	// e se lo è decrementa il timer, altrimenti non farà nulla.
	//
	// Chissà se funziona veramente tutto sto accrocchio per evitare di scrivere mille if

	soundReady = (sound_timer == 1) ? (sound_timer--) : ((sound_timer > 0) ? (sound_timer-- && false) : false);

	if (soundReady)
		printf("Sound playing\n");
}

void fetch_decode()
{
	// Fetch & Decode (16 bit, quindi si shifta a sinistra di 8 bit e si fa l'OR con altri 8 bit)
	opcode = memory[pc] << 8 | memory[pc + 1];
}

void execute()
{
	// Execute
	Chip8Table[(opcode & 0xF000) >> 12]();
}

void init()
{
	pc = 0x200; // Il program counter inizia a 0x200 ricordando dalla mappa che da qui inizia la ROM
	I = 0;
	sp = 0;
	opcode = 0;

	// Init grafico
	for (int i = 0; i < 64 * 32; i++) {
		gfx[i] = 0;
	}

	// Init stack, keypad e registri Vi
	for (int i = 0; i < 16; i++) {
		stack[i] = key[i] = V[i] = 0;
	}

	// Init memoria e inserimento font nello spazio dell'interprete
	for (int i = 0; i < 4096; i++) {
		memory[i] = 0;
	}

	for (int i = 0; i < 80; i++) {
		memory[i] = charset[i];
	}

	// Init timer
	delay_timer = 0;
	sound_timer = 0;

	drawReadyFlag = true;
	soundReady = false;
}

