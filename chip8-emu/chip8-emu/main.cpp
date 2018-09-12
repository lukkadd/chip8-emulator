#include <iostream>
#include "chip8.hpp"
#include "graphics.hpp"

using namespace std;

Chip8 myChip8;
Graphics gfx;
int main(int argc, char *argv[]) {

	myChip8.init();

	//myChip8.loadProgram(argv[1]);

	//myChip8.emulateCycle();

	//myChip8.display[2047] = 1;

	gfx.render(myChip8.display);

	cin.get();
	return 0;
}