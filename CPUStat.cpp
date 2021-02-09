// CPUStat.cpp

#include "CPUStat.h"
#include <iostream>
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

void CPUStat::print()
{
    cout << m_fetch_instr << endl;
    cout << m_r << "," << m_i << "," << m_s << "," << m_b << "," << m_u << "," << m_j << endl;
    cout << m_sw << "," << m_lw << "," << m_add << endl;
}