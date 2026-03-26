#include "stats.h"
#define MAXDUP 10

Stats::Stats(w_File *file)
:m_most_dup(MAXDUP,MAXDUP)
{
    m_file = file;
    m_word_num = 0;
    m_max_length = 0;
    m_num_by_lett = new long int[26];
    m_num_by_len = new long int[50];
    m_pos_of_lett = new long int[26];
}

Stats::~Stats()
{
    delete m_num_by_lett;
    delete m_num_by_len;
    delete m_pos_of_lett;
}

void Stats::printStuff()
{
    printf("Word num: %d\n"
        "Max length: %d\n",m_word_num,m_max_length);
    printf("number by letter:\n");
    for(int i = 0; i<26; i++)
    {
        printf("%c:%d\n",i+'a',m_num_by_lett[i]);
    }
    printf("number by length:\n");
    for(int i = 0; i<50; i++)
    {
        if(m_num_by_len[i]!=0)
        {
            printf("%c:%d\n",i+'a',m_num_by_len[i]);
        }
    }
    printf("most duplicated:\n");
    for(int i = 0; i<10; i++)
    {
        m_most_dup.get(i)->printout();
        printf("\n");
    }

}

void Stats::prepStats()
{
    if(m_file == nullptr)
        return;

    long int currentpos = 0;
    w_String readWord("",0);
    int readLen = 0;
    int readDup = 0;
    while(!m_file->eof())
    {
        m_file->get(&currentpos,&readWord,&readLen,&readDup);
        m_word_num++;
        if(readLen>m_max_length)
        {
            m_max_length = readLen;
        }
        char letter = readWord.charAt(0);
        int index = letter - 'a';
        m_num_by_lett[index]++;
        m_num_by_len[readLen]++;

        if(readDup>=2)
        {
            dupStat tmp;
            tmp.m_dup = readDup;
            tmp.m_num = 1;
            tmp.m_first_word = readWord;
            if(m_most_dup.isEmpty())
            {
                m_most_dup.add(tmp);
            }
            else
            {
                for(int i = 0; i<m_most_dup.size(); i++)
                {
                    if(readDup == m_most_dup.get(i)->m_dup)
                    {
                        m_most_dup.get(i)->m_num++;
                        break;
                    }
                    if(readDup > m_most_dup.get(i)->m_dup)
                    {
                        if(m_most_dup.size() == MAXDUP)
                        {
                            m_most_dup.remove(MAXDUP-1);
                        }
                        m_most_dup.add(i, tmp);
                        break;
                    }
                }
            }
        }
    }
}
