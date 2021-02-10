// CPUStat.cpp

#include "CPUStat.h"
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;

/*
CPUStat Class
- Track with function getters and setters
	1.Total number of fetched instructions
	2.Total number of instructions for each type (i.e., R-type, I-type,S,B, U, and J)
	3.Number of SW, LW, and ADD instructions.
- Print these values into terminal with this format
	#fetch_instr
	#R, #I, #S, #B, U, #J
	#SW, #LW, #ADD
- optional detailed mode with flag -d
*/

CPUStat::CPUStat()
{
        m_fetch_instr = m_r = m_i = m_s = m_b = m_u = m_j = m_sw = m_lw = m_add = 0; 
        detailed_mode = false;
}

void CPUStat::printStats()
{
	cout << m_fetch_instr << endl;
    cout << m_r << "," << m_i << "," << m_s << "," << m_b << "," << m_u << "," << m_j << endl;
    cout << m_sw << "," << m_lw << "," << m_add << endl;
}

void CPUStat::printRegisters(bitset<32>* registers)
{
	// TODO: Print in signed decimal
	cout << "// Register file:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << "x" << i << ": " << registers[i].to_ulong() << "\t";
		i++;
		cout << "x" << i << ": " << registers[i].to_ulong() << endl;
	}
	cout << "// END of Register file" << endl;
}

void CPUStat::printDataMemory(bitset<8>* data_memory) {
	cout << "// Data Memory:" << endl;
	for (int i = 0; i < 32; i++) {
		cout << "0x" << hex << i << ": " << data_memory[i] << endl;
	}
	cout << "// END of Data Memory" << endl;
}