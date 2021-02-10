// CPUStat.cpp

#include "CPUStat.h"
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

/*
CPUStat (Class)
- Use the values in the "Instruction" and "CPU" classes to count the following:
	1. Total number of fetched instructions
	2. Number of SW, LW, ADD, and BEQ instructions.
	3. Number of Taken Branches
- The output should be in the following format:
	#fetch_instr
	#SW, #LW, #ADD, #BEQ
	#Taken
- Print the values in all the registers, which is activated with flag -d1. 
	The print should be in this format (values in signed decimal):
	“ // Register file:
	x0: (tab) x1:
	x2: (tab) x3:
	...
	// END of Register file”
- Should be able to print the values in data memory
- Response to -dVal (logic in CPU Class)
	-d0 : no print at all
	-d1 : print registers
	-d2 : print memory
	-d3 : print both registers and memory
*/

CPUStat::CPUStat()
{
        m_fetch_instr = m_r = m_i = m_s = m_b = m_u = m_j = m_sw = m_lw = m_add = m_beq = m_taken = 0; 
}

void CPUStat::printStats()
{
	cout << m_fetch_instr << endl;
    cout << m_sw << "," << m_lw << "," << m_add << "," << m_beq << endl;
	cout << m_taken << endl;
}

void CPUStat::printRegisters(bitset<32>* registers)
{
	cout << "// Register file:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << "x" << i << ": " << (int32_t)(registers[i].to_ulong()) << "\t";
		i++;
		cout << "x" << i << ": " << (int32_t)(registers[i].to_ulong()) << endl;
	}
	cout << "// END of Register file" << endl;
}

void CPUStat::printDataMemory(bitset<8>* data_memory) {
	cout << "// Data Memory:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << "0x" << hex << i << ": " << dec << data_memory[i] << endl;
	}
	cout << "// END of Data Memory" << endl;
}