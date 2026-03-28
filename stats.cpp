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
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        delete *m_most_dup.get(i);
    }
    //printf("Start destruct\n");
    delete m_num_by_lett;
    //printf("Part 1\n");
    delete m_num_by_len;
    //printf("Part 2\n");
    delete m_pos_of_lett;
   // printf("end destruct\n");
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
        printf ("none");
    }
    else
    {
        (*m_most_dup.get(0))->m_first_word.printString();
    }
    printf("\nMost common first letter: %c\n",mostLett);
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
        printf("%d: ",i+1);
        (*m_most_dup.get(i))->m_first_word.printString();
        printf("\n");
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
void lengthPerLetter();
void letterPerLength();
void dupPerLength();

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
    while(!m_file->eof())
    {
        whilestart:

        m_file->get(&currentpos,&readWord,&readLen,&readDup);
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

        if(readDup>=2)
        {
            dupStat* tmp = new dupStat();
            tmp->m_dup = readDup;
            tmp->m_num = 1;
            tmp->m_first_word = readWord;
            if(m_most_dup.isEmpty())
            {
                m_most_dup.add(tmp);
            }
            else
            {
                int i = 0;
                for(i; i<m_most_dup.size(); i++)
                {
                    if(readDup == (*m_most_dup.get(i))->m_dup)
                    {
                        (*m_most_dup.get(i))->m_num++;
                        delete tmp;
                        goto whilestart;
                    }
                    if(readDup > (*m_most_dup.get(i))->m_dup)
                    {
                        if(m_most_dup.size() == MAXDUP)
                        {
                            delete (*m_most_dup.get(MAXDUP-1));
                            m_most_dup.remove(MAXDUP-1);
                        }
                        m_most_dup.add(i, tmp);
                        goto whilestart;
                    }
                }
                if(i < MAXDUP)
                {
                    m_most_dup.add(i, tmp);
                }
            }
        }
    }
    m_file->clear();
}
