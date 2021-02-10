// CPUStat.h

#ifndef CPUSTAT_INCLUDED
#define CPUSTAT_INCLUDED
#include <bits/stdc++.h>

using namespace std;

class CPUStat
{
    public:
        // Constructor
        CPUStat();
        // Print Stats
        void printStats();
        // Print Registers
        void printRegisters(bitset<32>* registers);
        // Print Data Memory
        void printDataMemory(bitset<8>* data_memory);
        // Member Variables
        int m_fetch_instr;
        int m_r;
        int m_i;
        int m_s;
        int m_b;
        int m_u;
        int m_j;
        int m_sw;
        int m_lw;
        int m_add;
        int m_beq;
        int m_taken;

};

#endif // CPUSTAT_INCLUDED
