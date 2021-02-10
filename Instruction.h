// Instruction.h

#ifndef INSTRUCTION_INCLUDED
#define INSTRUCTION_INCLUDED

#include <bits/stdc++.h>
using namespace std;

class Instruction
{
    public:
        // Constructor
        Instruction();

        // Print
        void print();

        // Accessors and Mutators
        bitset<7> getOpcode();
        void setOpcode(bitset<7> opcode);

        bitset<5> getRd();
        void setRd(bitset<5> rd);

        bitset<3> getFunc3();
        void setFunc3(bitset<3> func3);

        bitset<5> getRs1();
        void setRs1(bitset<5> rs1);

        bitset<5> getRs2();
        void setRs2(bitset<5> rs2);

        bitset<7> getFunc7();
        void setFunc7(bitset<7> func7);

        bitset<12> getImm();
        void setImm(bitset<12> imm);

        char getType();
        void setType(char type);

    private:
        // Member variables
        bitset<7> m_opcode;
        bitset<5> m_rd;
        bitset<3> m_func3;
        bitset<5> m_rs1;
        bitset<5> m_rs2;
        bitset<7> m_func7;
        bitset<12> m_imm;
        char m_type;
};

#endif // INSTRUCTION_INCLUDED
