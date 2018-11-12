#pragma once

// Documentazione: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

// Mappa sistema:
// 0x000 - 0x1FF - Interprete Chip 8
// 0x200 - 0xFFF - ROM e RAM

class Chip8CPU {
	public:
		Chip8CPU();
		~Chip8CPU();

		/* "The graphics system: The chip 8 has one instruction that draws sprite to the screen. 
		Drawing is done in XOR mode and if a pixel is turned off as a result of drawing, the VF register is set.
		This is used for collision detection.
		The graphics of the Chip 8 are black and white and the screen has a total of 2048 pixels (64 x 32). 
		This can easily be implemented using an array that hold the pixel state (1 or 0)" */
		unsigned char gfx[64 * 32];

		// Keypad (da 0x0 a 0xF)
		unsigned char key[16];

		// Flag che, se settato a true, permette alla CPU di disegnare la grafica
		// e in caso contrario di proseguire con i cycle
		bool drawReadyFlag;

	private:
		// Ci sono 35 opcode, tutti da due byte
		unsigned short opcode;
		// 4K di memoria
		unsigned char memory[4096];
	
		// REGISTRI:
		// 15 registri general purpose da 8-bit 
		// che vanno da V0 a VE (esadecimale)
		unsigned char V[16];
		// Registro index (12-bit: da 0x000 a 0xFFF)
		unsigned short I;
		// Program counter (12-bit: da 0x000 a 0xFFF)
		unsigned short pc;

		// L'interprete prevede istruzioni che saltano da un pezzo di
		// codice ad un altro: serve uno stack per tenere traccia di
		// dove si è arrivati nel momento di un salto, per poterci ritornare
		unsigned short stack[16]; // 16 livelli di stack
		unsigned short sp; // stack pointer

		// Questi timer contano a 60Hz verso il basso quando
		// sono settati ad un valore maggiore di zero
		unsigned short delay_timer;
		unsigned short sound_timer; // Quando arriva a zero, viene emesso un suono dal buzzer

		// Funzione di inizializzazione
		void init();
};