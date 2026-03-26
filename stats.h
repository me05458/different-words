#ifndef W_STATS_H
#define W_STATS_H
#include <fstream>
#include "w_file.h"

struct dupStat
{
    dupStat():m_first_word("",0), m_dup(0), m_num(0) {;}
    int m_dup;
    int m_num;
    w_String m_first_word;
    bool operator<(const dupStat &s)
    {
        return(m_dup<s.m_dup);
    };
    void printout()
    {
        m_first_word.printString();
        printf(",%d,%d",m_dup,m_num);
    }
};

class Stats {
public:
    Stats(w_File *file);
    ~Stats();
    void prepStats();
    void printStuff();

protected:
    w_File *m_file;
    long int m_word_num;
    int m_max_length;
    long int* m_num_by_lett;
    long int* m_num_by_len;
    long int* m_pos_of_lett;
    w_List<dupStat> m_most_dup;
};
#endif
