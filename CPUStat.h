// CPUStat.h

#ifndef CPUSTAT_INCLUDED
#define CPUSTAT_INCLUDED

class CPUStat
{
    public:
        // Constructor
        CPUStat();
        // Print Stats
        void print();
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
        bool detailed_mode;

};

#endif // CPUSTAT_INCLUDED
