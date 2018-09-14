#include "chip8.hpp"
#include "graphics.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void Chip8::init() {
	pc = 0x200; //program counter is set to program beginning
	opcode = 0; //clear opcode
	I = 0; //clear index register
	sp = 0; //clear stack pointer

	for (int i = 0; i < NUMBER_OF_REGISTERS; i++) V[i] = 0; // clear registers
	for (int i = 0; i < DISPLAY_SIZE; i++) display[i] = 0;//clear display
	for (int i = 0; i < STACK_SIZE; i++) stack[i] = 0;//clear stack
	for (int i = 0; i < MEM_SIZE; i++) memory[i] = 0;//clear memory
	for (int i = 0; i < KEYPAD_SIZE; i++) keypad[i] = 0;//clear memory

	for (int i = 0; i < 80; ++i) memory[i] = chip8_fontset[i];//load fontset

															  //reset timers
	delay_timer = 0;
	sound_timer = 0;

	//initialize graphics
	gfx.init();
}

void Chip8::loadProgram(const char *path) {

	streampos size;

	fstream file(path, ios::in | ios::binary | ios::ate);

	if (file.is_open()) {

		size = file.tellg();

		if (size > (0xFFF - 0x200)) {
			printf("Program file is too big... exiting");
			exit(-2);
		}

		file.seekg(0, ios::beg);

		file.read(memory + 0x200, size);

		file.close();

	}
	else {
		printf("Could not open program... exiting");
		exit(-3);
	}
}

void Chip8::emulateCycle() {

	//Fetch opcode
	opcode = memory[pc] << 8 | (memory[pc + 1] & 0xFF);
	//Decode opcode
	switch (opcode & 0xF000) {
	case 0x0000:
		switch (opcode & 0x000F) {

		case 0x0000:
			//0x00E0 - CLS
			gfx.clear();
			pc = pc + 2;
			break;

		case 0x000E:
			//RET
			break;

		default:
			//Sys addr
			break;
		}
		break;

	case 0x1000:
		//JMP addr
		pc = opcode & 0x0FFF;
		break;

	case 0x2000:
		//CALL addr
		break;

	case 0x3000:
		//3xkk - SE Vx, byte
		//skip next instruction if Vx == byte
		if (V[(opcode & 0x0F00) >> 8] == opcode & 0x00FF) {
			pc = pc + 4;
		}
		else {
			pc = pc + 2;
		}
		break;

	case 0x4000:
		//4xkk - SNE Vx,byte
		//skip next instruction if Vx != byte
		if (V[(opcode & 0x0F00) >> 8] != opcode & 0x00FF) {
			pc = pc + 4;
		}
		else {
			pc = pc + 2;
		}
		break;

	case 0x5000:
		//5xy0 - SE Vx,Vy
		//skip next instruction if Vx == Vy
		if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
			pc = pc + 4;
		}
		else {
			pc = pc + 2;
		}
		break;

	case 0x6000:
		//6xkk - LD Vx,kk
		// Vx = kk
		V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
		pc = pc + 2;
		break;

	case 0x7000:
		//7xkk - ADD Vx,byte
		//Vx = Vx + kk
		V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
		pc = pc + 2;
		break;

	case 0x8000:
		switch (opcode & 0x000F) {
		case 0x0000:
			//8xy0 - LD Vx,Vy
			//Vx = Vy
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
			pc = pc + 2;
			break;
		case 0x0001:
			//8xy1 - OR Vx,Vy
			//Vx = Vx or Vy
			V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
			pc = pc + 2;
			break;
		case 0x0002:
			//8xy2 - AND Vx,Vy
			//Vx = Vx AND Vy
			V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
			pc = pc + 2;
			break;
		case 0x0003:
			//8xy3 - XOR Vx,Vy
			//Vx = Vx XOR Vy
			V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
			pc = pc + 2;
			break;
		case 0x0004:
			//8xy4 - ADD Vx, Vy
			//Vx = Vx + Vy, VF = carry.
			break;
		case 0x0005:
			//8xy5 - SUB Vx, Vy
			//Vx = Vx - Vy, VF = NOT borrow.
			break;
		case 0x0006:
			//8xy6 - SHR Vx {,Vy}
			//If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0.
			//Then Vx is divided by 2.
			break;
		case 0x0007:
			// 8xy7 - SUBN Vx, Vy
			// Vx = Vy - Vx, set VF = NOT borrow.
			// If Vy > Vx, then VF is set to 1, otherwise 0.
			// Then Vx is subtracted from Vy, and the results stored in Vx.
			break;
		case 0x000E:
			//8xyE - SHL Vx {, Vy}
			//Vx = Vx SHL 1.
			//If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0.
			//Then Vx is multiplied by 2.
			break;
		default:
			printf("unindentified opcode.");
			break;
		}
		break;

	case 0x9000:
		//9xy0 - SNE Vx, Vy
		//Skip next instruction if Vx != Vy.
		if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
			pc = pc + 4;
		}else {
			pc = pc + 2;
		}
		break;

	case 0xA000:
		//Annn - LD  I, addr
		//I = nnn
		I = opcode & 0x0FFF;
		pc = pc + 2;
		break;

	case 0xB000:
		//Bnnn JMP V0, addr
		// pc = addr + V0
		pc = (opcode & 0x0FFF) + V[0];
		break;

	case 0xC000:
		//Cxkk - RND Vx,byte
		//Vx = random() AND byte
		break;

	case 0xD000:
		//Dxyn - DRW Vx, Vy, nibble
		break;

	case 0xE000:

		break;
	}

	//Update timers
	if (delay_timer > 0) {
		--delay_timer;
	}

	if (sound_timer > 0) {
		if (sound_timer == 1)
			printf("BEEP!\n");
		--sound_timer;
	}
}