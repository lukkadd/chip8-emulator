#include <iostream>
#include <chip8.hpp>

using namespace std;

Chip8 myChip8;

int main(int argc, char *argv[]){

    myChip8.init();

    myChip8.loadProgram(argv[1]);

    myChip8.emulateCycle();

    return 0;
}