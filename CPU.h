// CPU.h

#ifndef CPU_INCLUDED
#define CPU_INCLUDED

#include <string>
#include <tuple>
#include <bits/stdc++.h>
#include "Instruction.h"
using namespace std;

class CPUStat;

class CPU
{
  public:
      // Constructor
      CPU();

      // Functions
      void Fetch(string instMem[], int instMem_len);
      bool Decode(CPUStat* cpu_stats, Instruction* cur_instruction);
      tuple<bitset<32>, bitset<32>> RegisterFile(bitset<5> readReg1, bitset<5> readReg2,bitset<5> writeReg, bitset<32> writeData, bitset<1> RegWrite);
      tuple<bitset<1>, bitset<32>> Execute(bitset<32> readData1, bitset<32> readData2, bitset<32> immediate);
      void Mem(bitset<5> rd, bitset<5> rs2, bitset<32> ALUresult, bitset<8> dataMem[]);
      void WriteBack(bitset<5> writeReg, bitset<32> ALUresult);
      void PCAddr(bitset<1> Zero, bitset<32> immediate);
      //   // Getters
      //   bitset<1> getRegWrite();
      //   bitset<1> getAluSrc();
      //   bitset<1> getBranch();
      //   bitset<1> getMemRe();
      //   bitset<1> getMemWr();
      //   bitset<1> getMemtoReg();
      //   bitset<4> getALUOp();
      bitset<32>* getRegisters();
      //   // Setters
      //   void setRegWrite(bitset<1> regwrite);
      //   void setAluSrc(bitset<1> alusrc);
      //   void setBranch(bitset<1> branch);
      //   void setMemRe(bitset<1> memre);
      //   void setMemWr(bitset<1> memwr);
      //   void setMemtoReg(bitset<1> memtoreg);
      //   void setAluOp(bitset<4> aluop);

  private:
      int m_PC;
      bitset<32> m_32bit_instruction; // 32 bit instruction in binary
      bitset<32> x[32]; // Registers
      // Control Signals
      bitset<1> RegWrite;
      bitset<1> AluSrc;
      bitset<1> Branch;
      bitset<1> MemRe;
      bitset<1> MemWr;
      bitset<1> MemtoReg;
      bitset<4> ALUOp;
};

#endif // CPU_INCLUDED
