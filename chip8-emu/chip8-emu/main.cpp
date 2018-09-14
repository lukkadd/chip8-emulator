#include <iostream>
#include "chip8.hpp"
#include "graphics.hpp"

using namespace std;

Chip8 myChip8;
int main(int argc, char *argv[]) {

	myChip8.init();

	//load program
	myChip8.loadProgram("test.ch8");

	myChip8.display[300] = 1;

	myChip8.gfx.render(myChip8.display);

	//while(1){
	// Emulate one cycle
	myChip8.emulateCycle();

	// If the draw flag is set, update the screen
	//if (myChip8.drawFlag) {
	//	gfx.render(myChip8.display);
	//}

	// Store key press state (Press and Release)
	//myChip8.setKeys();
	//}



	cin.get();
	return 0;
}