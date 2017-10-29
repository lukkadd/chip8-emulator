#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char const *argv[])
{
	
	//external graphics stuff I/O
	setupGraphics();
	setupInput();

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