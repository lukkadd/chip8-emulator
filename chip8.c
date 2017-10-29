void chip8::initialize(){
	//initializing registers and memory
	pc = 0x200; //pc starts at position 512 where the game is loaded
	opcode = 0; //clear current opcode
	I = 0;	//clear index register
	sp = 0; //clear stack pointer
}