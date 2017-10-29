void chip8::initialize(){
	//initializing registers and memory
	pc = 0x200; //pc starts at position 512 where the game is loaded
	opcode = 0; //clear current opcode
	I = 0;	//clear index register
	sp = 0; //clear stack pointer

	//clear display
	for (int i = 0; i < 64 * 32; ++i)
		gfx[i] = 0;

	//clear stack and registers
	for (int i = 0; i < 16; ++i){
		V[i] = 0;
		stack[i] = 0;
	}

	//clear memory
	for (int i = 0; i < 4096; ++i)
	{
		memory[i] = 0;
	}

	//Load fontset
	for (int i = 0; i < 80; ++i)
	{
		memory[i] = chip8_fontset[i];
	}

	//Reset timers
	delay_timer = 0;
	sound_timer = 0;
}

void chip8::emulateCycle(){
	//Fetch Opcode
	opcode = memory[pc] << 8 | memory[pc + 1];//joins 2 bytes of memory into opcode
	//Decode Opcode
	

	//Update timers
	if(delay_timer > 0){
    	--delay_timer;
	}
 
  	if(sound_timer > 0)
  	{
    	if(sound_timer == 1){
    		printf("BEEP!\n");
    	}
    	--sound_timer;
  	} 
}