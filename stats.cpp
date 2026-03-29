#include "stats.h"
#include <iostream>
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
    m_dup_by_len = new dupStat*[50];
    m_dup_by_lett = new dupStat*[26];
    m_len_by_lett = new long int[26];
    m_lett_by_len = new long int[50];
    for(int i = 0; i<26; i++)
    {
        m_dup_by_lett[i]=new dupStat;
    }
    for(int i = 0; i<50; i++)
    {
        m_dup_by_len[i]=new dupStat;
    }
}
/*
void Stats::cleanLists()
{
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        delete *m_most_dup.get(i);
    }
    for(int i = 0; i<m_dup_by_len.size(); i++)
    {
        delete *m_dup_by_len.get(i);
    }
    for(int i = 0; i<m_dup_by_lett.size(); i++)
    {
        delete *m_dup_by_lett.get(i);
    }
}
*/
Stats::~Stats()
{
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        delete *m_most_dup.get(i);
    }
    for(int i = 0; i<26; i++)
    {
        delete m_dup_by_lett[i];
    }
    for(int i = 0; i<50; i++)
    {
        delete m_dup_by_len[i];
    }
    //printf("Start destruct\n");
    delete m_num_by_lett;
    //printf("Part 1\n");
    delete m_num_by_len;
    //printf("Part 2\n");
    delete m_pos_of_lett;
    delete m_dup_by_len;
    delete m_dup_by_lett;
    delete m_len_by_lett;
    delete m_lett_by_len;
   // printf("end destruct\n");
}

int Stats::mostCommonLen(char letter)
{
    int *mostLen = new int[50];
    long int pos = 0;
    char tmpLett = 'a'-1;
    int tmpLen = 0;
    int foo = 0;
    w_String tmpWord("",0);
    while(tmpLett<letter)
    {
        //printf("aaa- 1\n");
        m_file->get(&pos,&tmpWord,&tmpLen,&foo);
        tmpLett=tmpWord.charAt(0);
    }
    if(tmpLett>letter)
    {
        return 0;
    }

    while(tmpLett==letter)
    {
        //printf("aaa- 2\n");
        m_file->get(&pos,&tmpWord,&tmpLen,&foo);
        tmpLett=tmpWord.charAt(0);
        mostLen[tmpLen]++;
    }
    int mostCommon = 0;
    for(int i = 0; i<50; i++)
    {
        if(mostLen[i] > mostCommon)
        {
            printf("aaa- 1\n");

            mostCommon = mostLen[i];
        }
    }
    return mostCommon;

}

void Stats::basicStats()
{
    prepStats();
    char mostLett = 'a';
    int maxVal = m_num_by_lett[0];
    for(int i=0; i<26; i++)
    {
        if(m_num_by_lett[i] > maxVal)
        {
            maxVal = m_num_by_lett[i];
            mostLett = i+'a';
        }
    }
    int mostLen = 3;
    maxVal = m_num_by_len[3];
    for(int i=0; i<50; i++)
    {
        if(m_num_by_len[i] > maxVal)
        {
            maxVal = m_num_by_len[i];
            mostLen = i;
        }
    }
    printf("Number of words: %d\n"
        "Most duplicated word: ",m_word_num);
    if((m_most_dup.size())==0)
    {
        printf ("none\n");
    }
    else
    {
        printf("%s\n",(char*)(*m_most_dup.get(0))->m_first_word);
    }
    printf("Most common first letter: %c\n",mostLett);
    printf("Most common word length: %d\n",mostLen);
}

void Stats::topLengths()
{
    prepStats();
    int length[5] = {0,0,0,0,0};
    int num[5] = {0,0,0,0,0};
    for(int i = 0; i<50; i++)
    {
        if(m_num_by_len[i]>num[0])
        {
            num[0]=m_num_by_len[i];
            length[0] = i;
        }
        else if(m_num_by_len[i]>num[1])
        {
            num[1]=m_num_by_len[i];
            length[1] = i;
        }
        else if(m_num_by_len[i]>num[2])
        {
            num[2]=m_num_by_len[i];
            length[2] = i;
        }
        else if(m_num_by_len[i]>num[3])
        {
            num[3]=m_num_by_len[i];
            length[3] = i;
        }
        else if(m_num_by_len[i]>num[4])
        {
            num[4]=m_num_by_len[i];
            length[4] = i;
        }
    }
    for(int i = 1; i<=5; i++)
    {
        if(num[i-1] == 0)
        {
            printf("%d: N/A\n",i);
        }
        else
        {
            printf("%d: %d\n",i,length[i-1]);
        }
    }
}
void Stats::lengthGraph()
{
    prepStats();
    int length = 0;
    int num = 0;
    for(int i = 0; i<50; i++)
    {
        if(m_num_by_len[i]>num)
        {
            num=m_num_by_len[i];
            length = i;
        }
    }

    printf("length | number of words \n");
    for(int i = 0; i<50; i++)
    {
        if(m_num_by_len[i] != 0)
        {
            printf("   %d ",i);
            if(i/10 == 0)
            {
                printf(" ");
            }
            printf(" | ");
            int runNum = int(double(50)*double(m_num_by_len[i])/double(num));
            for(int j = 0; j<runNum; j++)
            {
                printf("_");
            }
            printf(" %d\n",m_num_by_len[i]);
        }
    }


}
void Stats::topDup()
{
    prepStats();
    if(m_most_dup.size() == 0)
    {
        printf("none\n");
        return;
    }
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        if(i<m_most_dup.size())
        {
            printf("%d: %s\n",i+1,(char*)(*m_most_dup.get(i))->m_first_word);
        }
        else
        {
            printf("%d: N/A",i+1);
        }
    }
}
void Stats::topLetters()
{
    prepStats();
    int lett[5] = {0,0,0,0,0};
    int num[5] = {0,0,0,0,0};
    for(int i = 0; i<26; i++)
    {
        if(m_num_by_lett[i]>num[0])
        {
            num[0]=m_num_by_lett[i];
            lett[0] = i;
        }
        else if(m_num_by_lett[i]>num[1])
        {
            num[1]=m_num_by_lett[i];
            lett[1] = i;
        }
        else if(m_num_by_lett[i]>num[2])
        {
            num[2]=m_num_by_lett[i];
            lett[2] = i;
        }
        else if(m_num_by_lett[i]>num[3])
        {
            num[3]=m_num_by_lett[i];
            lett[3] = i;
        }
        else if(m_num_by_lett[i]>num[4])
        {
            num[4]=m_num_by_lett[i];
            lett[4] = i;
        }
    }
    for(int i = 1; i<=5; i++)
    {
        if(num[i-1] == 0)
        {
            printf("%d: N/A\n",i);
        }
        else
        {
            printf("%d: %c\n",i,lett[i-1]+'a');
        }
    }
}
void Stats::letterGraph()
{
    prepStats();
    int length = 0;
    int num = 0;
    for(int i = 0; i<26; i++)
    {
        if(m_num_by_lett[i]>num)
        {
            num=m_num_by_lett[i];
            length = i;
        }
    }

    printf("length | number of words \n");
    for(int i = 0; i<25; i++)
    {
        if(m_num_by_lett[i] != 0)
        {
            printf("   %c ",i+'a');
            printf(" | ");
            int runNum = int(double(50)*double(m_num_by_lett[i])/double(num));
            //printf("runNum: %d\n",runNum);
            for(int j = 0; j<runNum; j++)
            {
                printf("_");
            }
            printf(" %d\n",m_num_by_lett[i]);
        }
    }
}
void Stats::lengthPerLetter()
{
    int tmp = 0;
    for(int i = 0; i<26; i++)
    {
        tmp = mostCommonLen(i+'a');
        if(tmp != 0 )
        {
            printf("%c: %d\n",i+'a',tmp);
        }
    }
}
void Stats::letterPerLength()
{

}
void Stats::dupPerLength()
{
    prepStats();
    for(int i = 0; i<50; i++)
    {
        if(m_dup_by_len[i]->m_dup != 0)
        {
            printf("%d: %s\n",i,(char*)m_dup_by_len[i]->m_first_word);
        }
    }
}
void Stats::dupPerLetter()
{
    prepStats();
    for(int i = 0; i<26; i++)
    {
        if(m_dup_by_lett[i]->m_dup != 0)
        {
            printf("%c: %s\n",i+'a',(char*)m_dup_by_lett[i]->m_first_word);
        }
    }
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
    printf("size: %d\n",m_most_dup.size());
    printf("most duplicated:\n");
    if(m_most_dup.size() == 0)
    {
        printf("No duplicates\n");
        return;
    }
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        (*m_most_dup.get(i))->printout();
        printf("\n");
    }

}

void Stats::prepStats()
{
    //printf("aaa- 0\n");
    for(int i = 0; i<26; i++)
    {
        delete m_dup_by_lett[i];
        m_dup_by_lett[i]=new dupStat;
    }
    for(int i = 0; i<50; i++)
    {
        delete m_dup_by_len[i];
        m_dup_by_len[i]=new dupStat;
    }
    m_most_dup.clear();
    //printf("aaa- 1\n");
    m_word_num = 0;
    if(m_file == nullptr)
        return;

    for(int i = 0; i<50; i++)
    {
        m_num_by_len[i] = 0;
    }
    for(int i = 0; i<25; i++)
    {
        m_num_by_lett[i] = 0;
    }
    long int currentpos = 0;
    w_String readWord("",0);
    int readLen = 0;
    int readDup = 0;
    //printf("aaa- 2\n");
    while(!m_file->eof())
    {
        whilestart:
            //printf("aaa- 2.1\n");

        m_file->get(&currentpos,&readWord,&readLen,&readDup);
        //printf("aaa- 2.2\n");

        if(m_file->eof())
        {
            break;
        }
        m_word_num++;
        if(readLen>m_max_length)
        {
            m_max_length = readLen;
        }
        char letter = readWord.charAt(0);
        int index = letter - 'a';
        m_num_by_lett[index]++;
        m_num_by_len[readLen]++;

        //printf("aaa- 3\n");

        if(readDup>=2)
        {
            dupStat* tmp = new dupStat();
            tmp->m_dup = readDup;
            tmp->m_first_word = readWord;
            int i = 0;
            for(i; i<m_most_dup.size(); i++)
            {
                if(readDup > (*m_most_dup.get(i))->m_dup)
                {
                    break;
                }
            }
            if(i < MAXDUP)
            {
                if(m_most_dup.size() == MAXDUP)
                {
                    delete (*m_most_dup.get(MAXDUP-1));
                    m_most_dup.remove(MAXDUP-1);
                }
                m_most_dup.add(i, tmp);
            }

            //--------
            //printf("aaa- 4\n");

            int pos = readWord.charAt(0)-'a';
            if(m_dup_by_lett[pos]->m_dup < readDup)
            {
                *m_dup_by_lett[pos] = *tmp;
            }
            //printf("aaa- 5\n");

            pos = readLen;
            if(m_dup_by_len[pos]->m_dup < readDup)
            {
                *m_dup_by_len[pos] = *tmp;
            }
        }
    }
        m_file->clear();
}
