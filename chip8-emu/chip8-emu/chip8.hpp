/**
* @<chip8.h>
* Author: Lucca Del Debbio
* Created on: 08/09/2018
* **/
#include "graphics.hpp"

#ifndef CHIP8_H_
#define CHIP8_H_

#define MEM_SIZE 4096
#define NUMBER_OF_REGISTERS 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16
#define DISPLAY_SIZE 32*64

class Chip8 {

	char memory[MEM_SIZE];
	unsigned char V[NUMBER_OF_REGISTERS];
	unsigned char sp;
	unsigned char delay_timer;
	unsigned char sound_timer;

	unsigned short pc;
	unsigned short I;
	unsigned short opcode;
	unsigned short stack[STACK_SIZE];

	bool keypad[KEYPAD_SIZE];

	unsigned char chip8_fontset[80] =
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

public:

	Graphics gfx;

	bool drawFlag;
	unsigned char display[DISPLAY_SIZE];
	void init();
	void loadProgram(char *path);
	void emulateCycle();
	void setKeys();

};


#endif /* CHIP8_H_ */