#ifndef W_STATS_H
#define W_STATS_H
#include <fstream>
#include "w_file.h"

struct dupStat
{
    dupStat():m_dup(0), m_first_word("",0){;}
    int m_dup;
    w_String m_first_word;
    dupStat(const dupStat &d)
    :m_first_word(d.m_first_word)
    {
        //m_first_word = d.m_first_word;
        m_dup = d.m_dup;
    }
    bool operator<(const dupStat &s)
    {
        return(m_dup<s.m_dup);
    }

    bool operator==(const dupStat &s)
    {
        return(m_dup == s.m_dup);
    }
    dupStat& operator=(const dupStat &s)
    {
        m_dup = s.m_dup;
        m_first_word = s.m_first_word;
        return *this;
    }
    void printout()
    {
        m_first_word.printString();
        printf(",%d,%d",m_dup);
    }
};

class Stats {
public:
    Stats(w_File *file);
    ~Stats();
    void prepStats();
    void printStuff();
    void basicStats();
    void topLengths();
    void lengthGraph();
    void topDup();
    void topLetters();
    void letterGraph();
    void lengthPerLetter();
    void letterPerLength();
    void dupPerLength();
    void dupPerLetter();

protected:
    w_File *m_file;
    long int m_word_num;
    int m_max_length;
    long int* m_num_by_lett;
    long int* m_len_by_lett;
    long int* m_lett_by_len;
    long int* m_num_by_len;
    long int* m_pos_of_lett;
    dupStat** m_dup_by_len;
    dupStat** m_dup_by_lett;
    w_List<dupStat*> m_most_dup;
    int mostCommonLen(char letter);
};
#endif
