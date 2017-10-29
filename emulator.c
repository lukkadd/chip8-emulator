#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

chip8 myChip8;

//alocating essential memory, registers and utils
unsigned char memory[4096]; //4K memory
unsigned char V[16]; //16 registers with 8bits each

unsigned short I; //Index register 2bytes
unsigned short pc; //Program counter 2bytes

unsigned char gfx[64 * 32];//graphics (pixel matrix of 1s and 0s)

unsigned char delay_timer;//count down to 0
unsigned char sound_timer;//!!

unsigned short stack[16];//stack used in subroutines
unsigned short sp;//stack pointer

unsigned char key[16];//array to store key states( chip 8 had 16 keys )
					  //1 if pressed, 0 if not

unsigned short opcode;//opcode 2bytes

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

int main(int argc, char const *argv[])
{
	
	//external graphics stuff I/O
	//setupGraphics();
	//setupInput();

	//chip8 intialization stuff
	myChip8.initialize();
	myChip8.loadGame("game");

	//Emulation loop
	while(1){
		//Emulate 1 cycle
		myChip8.emulateCycle();

		//update the screen based on draw flag
		if(myChip8.drawFlag){
			drawGraphics();
		}

		//Register key state
		myChip8.setKeys();
	}

	return 0;
}