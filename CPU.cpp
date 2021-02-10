// CPU.cpp

#include "CPU.h"
#include "Instruction.h"
#include "CPUStat.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
CPU Class
- function fetch
	- access instMem by using address stored in program counter
	- store the value in a 32-bit unsigned variable
	- to read instructions, you need to access four lines of memory: PC to PC+3 and do the proper shifting
	in order to create a 32 bit value
	- return the final value or store it in an internal variable in the cpu class
	- create the next value of the PC (PC + 4) 
- function decode
	- use the 32 bit value from function fetch and assign proper values for each variable in the Instruction class
	- check the opcode and return FALSE if opcode is equal to 0. We call this Instruction 'end'.
	This return value will be ised to break the while loop in the main function.
	- update CPU stats based on opcode and other relevant values for each Instruction
- constructor
- program counter
*/

CPU::CPU()
{
    // 0 out everything
    m_PC = 0; 
    m_32bit_instruction.reset();
    for (int i = 0; i < 31; i++) {
        x[i].reset();
    }
    RegWrite.reset();
    AluSrc.reset();
    Branch.reset();
    MemRe.reset();
    MemWr.reset();
    MemtoReg.reset();
    ALUOp.reset();
}

void CPU::Fetch(string instMem[], int instMem_len) 
{
    // Load 4 bytes
    int i = m_PC;
    string d = instMem[i++];
    string c = instMem[i++];
    string b = instMem[i++];
    string a = instMem[i++];
    // Reverse order since it is stored in little endian
    m_32bit_instruction = bitset<32>(string(a + b + c + d));
    // cout << m_32bit_instruction.to_string() << endl;
    // Increment PC
    m_PC += 4;
}

bool CPU::Decode(CPUStat* cpu_stats, Instruction* cur_instruction)
{
    // Binary opcodes for comparison
    bitset<7> rtype("0110011");
    bitset<7> itype("0010011");
    bitset<7> lw("0000011");
    bitset<7> sw("0100011");
    bitset<7> beq("1100011");
    bitset<7> nop("0000000");

    // Create bitmasks to extract sections of the instruction
    bitset<32> ext_opcode (0b1111111);
    bitset<32> ext_rd (0b11111 << 7);
    bitset<32> ext_func3 (0b111 << 12);
    bitset<32> ext_rs1 (0b11111 << 15);
    bitset<32> ext_rs2 (0b11111 << 20);
    bitset<32> ext_func7 (0b1111111 << 25);
    // Extract sections of the instruction
    cur_instruction->setOpcode(bitset<7>((ext_opcode & m_32bit_instruction).to_ulong()));
    cur_instruction->setRd(bitset<5>(((ext_rd & m_32bit_instruction) >> 7).to_ulong()));
    cur_instruction->setFunc3(bitset<3>(((ext_func3 & m_32bit_instruction) >> 12).to_ulong()));
    cur_instruction->setRs1(bitset<5>(((ext_rs1 & m_32bit_instruction) >> 15).to_ulong()));
    cur_instruction->setRs2(bitset<5>(((ext_rs2 & m_32bit_instruction) >> 20).to_ulong()));
    cur_instruction->setFunc7(bitset<7>(((ext_func7 & m_32bit_instruction) >> 25).to_ulong()));

    // Update Stats, Control Signal, and Calculate Immediate
    if (cur_instruction->getOpcode() != nop) {
        // Update Stats
        cpu_stats->m_fetch_instr++;
    }

    // Zero Out Control Signals
    RegWrite.reset();
    AluSrc.reset();
    Branch.reset();
    MemRe.reset();
    MemWr.reset();
    MemtoReg.reset();
    ALUOp.reset();

    if (cur_instruction->getOpcode() == rtype) { 
        // cout << "rtype" << endl;
        // Update Stats
        cpu_stats->m_r++;
        // Set Control Signals
        RegWrite[0] = 1;
        if (cur_instruction->getFunc3() == bitset<3>(0b000) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "add" << endl;
            cpu_stats->m_add++;
            ALUOp = bitset<4>(0b0010);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b000) && cur_instruction->getFunc7() == bitset<7>(0b0100000)) {
            // cout << "sub" << endl;
            ALUOp = bitset<4>(0b0110);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b111) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "and" << endl;
            ALUOp = bitset<4>(0b0000);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b110) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "or" << endl;
            ALUOp = bitset<4>(0b0001);
        }
        }
    else if (cur_instruction->getOpcode() == itype) { 
        // cout << "itype" << endl; 
        // Update Stats
        cpu_stats->m_i++;
        // Set Immediate
        cur_instruction->setImm(bitset<20>(cur_instruction->getFunc7().to_string() + cur_instruction->getRs2().to_string()));
        // Set Control Signals
        RegWrite[0] = 1;
        AluSrc[0] = 1;
        if (cur_instruction->getFunc3() == bitset<3>(0b000) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "addi" << endl;
            cpu_stats->m_add++;
            ALUOp = bitset<4>(0b0010);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b000) && cur_instruction->getFunc7() == bitset<7>(0b0100000)) {
            // cout << "subi" << endl;
            ALUOp = bitset<4>(0b0110);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b111) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "andi" << endl;
            ALUOp = bitset<4>(0b0000);
        }
        else if (cur_instruction->getFunc3() == bitset<3>(0b110) && cur_instruction->getFunc7() == bitset<7>(0b0)) {
            // cout << "ori" << endl;
            ALUOp = bitset<4>(0b0001);
        }
        }
    else if (cur_instruction->getOpcode() == lw) { 
        // cout << "lw" << endl; 
        // Update Stats
        cpu_stats->m_i++;
        cpu_stats->m_lw++;
        // Set Immediate
        cur_instruction->setImm(bitset<20>(cur_instruction->getFunc7().to_string() + cur_instruction->getRs2().to_string()));
        // Set Control Signals
        RegWrite[0] = 1;
        AluSrc[0] = 1;
        MemRe[0] = 1;
        MemtoReg[0] = 1;
        ALUOp = bitset<4>(0b0010);
        }
    else if (cur_instruction->getOpcode() == sw) { 
        // cout << "sw" << endl; 
        // Update Stats
        cpu_stats->m_s++;
        cpu_stats->m_sw++;
        // Set Immediate
        cur_instruction->setImm(bitset<20>(cur_instruction->getFunc7().to_string() + cur_instruction->getRd().to_string()));
        // Set Control Signals
        AluSrc[0] = 1;
        MemWr[0] = 1;
        ALUOp = bitset<4>(0b0010);
        }
    else if (cur_instruction->getOpcode() == beq) { 
        // cout << "beq" << endl; 
        // Update Stats
        cpu_stats->m_b++;
        // Set Immediate
        cur_instruction->setImm(bitset<20>(cur_instruction->getFunc7().to_string() + cur_instruction->getRs2().to_string() + cur_instruction->getRs1().to_string() + cur_instruction->getFunc3().to_string()));
        // Set Control Signals
        Branch[0] = 1;
        ALUOp = bitset<4>(0b0110);
        }

    // return false if opcode is equal to 0
    return cur_instruction->getOpcode() != nop;
}

tuple<bitset<32>, bitset<32>> CPU::RegisterFile(bitset<5> readReg1, bitset<5> readReg2,bitset<5> writeReg, bitset<32> writeData, bitset<1> RegWrite) {
    // Handle Reads from the registers
    bitset<32> readData1(x[(readReg1.to_ulong())]);
    bitset<32> readData2(x[(readReg2.to_ulong())]);
    // Only Write to a register if RegWrite is 1
    if (RegWrite[0] == 1) {
        x[writeReg.to_ulong()] = writeData;
    }
    return {readData1, readData2};
}

tuple<bitset<1>, bitset<32>> CPU::Execute(bitset<32> readData1, bitset<32> readData2, bitset<32> immediate) {
    // TODO: Remove this line
    cout << ALUOp.to_string() << " " << readData1.to_ulong() << " " << (AluSrc[0] == 1 ? immediate.to_ulong() : readData2.to_ulong()) << endl;

    bitset<1> Zero = readData1 == ((AluSrc[0] == 1 ? immediate : readData2));
    bitset<32> ALUresult;

    if (ALUOp == bitset<4>(0b0010)) {
        // cout << "add" << endl;
        ALUresult = bitset<32>(readData1.to_ulong() + (AluSrc[0] == 1 ? immediate.to_ulong() : readData2.to_ulong()));
    }
    else if (ALUOp == bitset<4>(0b0110)) {
        // cout << "sub" << endl;
        ALUresult = bitset<32>(readData1.to_ulong() - (AluSrc[0] == 1 ? immediate.to_ulong() : readData2.to_ulong()));
    }
    else if (ALUOp == bitset<4>(0b0000)) {
        // cout << "and" << endl;
        ALUresult = readData1 & (AluSrc[0] == 1 ? immediate : readData2);
    }
    else if (ALUOp == bitset<4>(0b0001)) {
        // cout << "or" << endl;
        ALUresult = readData1 | (AluSrc[0] == 1 ? immediate : readData2);
    }
    return {Zero, ALUresult};

}

void CPU::WriteBack(bitset<5> writeReg, bitset<32> ALUresult) {
    if (RegWrite[0] == 1) {
        RegisterFile(bitset<5>(0b0), bitset<5>(0b0), writeReg, ALUresult, bitset<1>(0b1));
    }
}

bitset<32>* CPU::getRegisters() {
    return x;
}