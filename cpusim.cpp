// cpusim.cpp

#include "CPU.h"
#include "Instruction.h"
#include "CPUStat.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

// TODO: Comment Code


int main (int argc, char* argv[])
{
	/* This is the front end of your project. 
	You need to first read the instructions that are stored in a file and 
	load them into an Instruction memory. 
	*/

	/* Define your Instruction memory here. Each cell should store 1 byte. You can 
	define the memory either dynamically, or define it as a fixed size with size 4MB 
	(i.e., 4096 lines). Each Instruction is 32 bits (i.e., 4 lines, saved in little-endian mode). 
	
	Each line in the input file is stored as an unsigned char and is 1 byte 
	(each four lines are one Instruction). You need to read the file line by 
	line and store it into the memory. You may need a mechanism to convert these values 
	to bits so that you can read opcodes, operands, etc. 
	*/ 
	string instMem[4096] = {};	

	// Make an ifstream
	if (argc < 2)
	{
		cout << "Must enter file name." << endl;
		exit(EXIT_FAILURE);
	}
	
	// Example file: "./trace/debug/instMem.txt"

	// Read from text file and convert each line into padded 8 bit values
	ifstream infile(argv[1]);
	int cur_line_int;
	int instMem_len = 0;
	while (infile >> cur_line_int)
	{
		bitset<8> cur_line_bits(cur_line_int);
		instMem[instMem_len] = cur_line_bits.to_string();
		instMem_len++;
	}

	/* Instantiate your CPU object here.  CPU class is the main class in this project that 
	defines different components of the processor. 
	CPU class also has different functions for each stage (e.g., fetching an Instruction, decoding, etc.). 
	*/
    CPU myCPU;  // call the approriate constructor here to initialize the processor...  
	// make sure to create a variable for PC and resets it to zero (e.g., unsigned int PC = 0); 

	/* Instatiate your CPUStat object here. CPUStat class is responsible to keep track of all 
	the required statistics. */
    CPUStat cpu_stats;


	/* OPTIONAL: Instantiate your Instruction object here. */
	Instruction cur_instruction; 

	bool to_continue = false;

	while (1) // processor's main loop. Each iteration is equal to one clock cycle.  
	{
		//fetch
		myCPU.Fetch(instMem, instMem_len); // fetching the Instruction
		// decode
		to_continue = myCPU.Decode(&cpu_stats, &cur_instruction); // decoding

		// we should break the loop if the current Instruction is BREAK Instruction (i.e., if opcode == 0)
		if (!to_continue)
		{
			break;
		}
		// Read from the registers
		// Explicitly set RegWrite to 0 so that we don't write at this stage
		myCPU.RegisterFile(cur_instruction.getRs1(), cur_instruction.getRs2(), cur_instruction.getRd(), bitset<32>(0b0), bitset<1>(0b0));

	}

	// clean up the memory (if any)

	// print the stats
	cpu_stats.print();

	return 0; 
	
}


