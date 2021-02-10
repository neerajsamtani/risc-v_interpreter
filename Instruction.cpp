// Instruction.cpp

#include "Instruction.h"
#include <bits/stdc++.h>
using namespace std;

/*
Instruction Class
- member variables
	- opcode
	- rd
	- rs1
	- rs2
	- imm
	- func3
	- func7
	- type (r-type, i-type, etc from the opcode). Can store a character "R", "I", etc.
- function getter and setters for these variables (from the decode function especially)
*/

Instruction::Instruction()
{
    m_opcode.reset();
    m_rd.reset();
    m_func3.reset();
    m_rs1.reset();
    m_rs2.reset();
    m_func7.reset();
    m_imm.reset();
    m_type = ' ';
}

void Instruction::print() {
    cout << "###" << endl;
    cout << "opcode: " << m_opcode.to_string() << endl;
    cout << "rd: " << m_rd.to_ulong() << endl;
    cout << "func3: " << m_func3.to_string() << endl;
    cout << "rs1: " << m_rs1.to_string() << endl;
    cout << "rs2: " << m_rs2.to_string() << endl;
    cout << "func7: " << m_func7.to_string() << endl;
    cout << "imm: " << m_imm.to_ulong() << endl;
    cout << "###" << endl;
}

// Accessors and Mutators

bitset<7> Instruction::getOpcode()
{
    return m_opcode;
}

void Instruction::setOpcode(bitset<7> opcode)
{
    m_opcode = opcode;
}

bitset<5> Instruction::getRd()
{
    return m_rd;
}

void Instruction::setRd(bitset<5> rd)
{
    m_rd = rd;
}

bitset<3> Instruction::getFunc3()
{
    return m_func3;
}

void Instruction::setFunc3(bitset<3> func3)
{
    m_func3 = func3;
}

bitset<5> Instruction::getRs1()
{
    return m_rs1;
}

void Instruction::setRs1(bitset<5> rs1)
{
    m_rs1 = rs1;
}

bitset<5> Instruction::getRs2()
{
    return m_rs2;
}

void Instruction::setRs2(bitset<5> rs2)
{
    m_rs2 = rs2;
}

bitset<7> Instruction::getFunc7()
{
    return m_func7;
}

void Instruction::setFunc7(bitset<7> func7)
{
    m_func7 = func7;
}

bitset<20> Instruction::getImm()
{
    return m_imm;
}

void Instruction::setImm(bitset<20> imm)
{
    m_imm = imm;
}

char Instruction::getType()
{
    return m_type;
}

void Instruction::setType(char type)
{
    m_type = type;
}
