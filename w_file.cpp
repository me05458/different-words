#include "w_file.h"
#include <cerrno>
#include <iostream>
#include <fstream>
#include <filesystem>

w_File::w_File(w_String name)
:m_file(name)
{
    char* p = name;
    const char* cp = p;
    cout<<cp<<endl;

    //m_file.open("test1.txt", ios::in | ios::out);
    if(!m_file.is_open())
    {
        printf("w_File error occured\n");
    }
}
w_File::~w_File()
{
    m_file.close();
}
bool w_File::findWord(w_String word, long int* pos)
{
  //  printf("aaa- looking for: %s\n", (char*)word);
    m_file.seekp(0,m_file.beg);
    long int beg_pos = m_file.tellp();
    m_file.seekp(0,m_file.end);
    long int end_pos = m_file.tellp();
    //printf("aaa- beg=%d, end=%d\n", beg_pos, end_pos);

    long int postmp = beg_pos;
    char* buff = new char[100];
    w_String tmpword("a",1);
    //printf("aaa pre get\n");
    int i = get(&postmp,&tmpword,nullptr,nullptr);
    //printf("aaa get returned %d\n", i);
    long int postmp1 = beg_pos;
    //printf("aaa- got: %d, %s, next pos=%d\n", i, (char*)tmpword, postmp);
    if(i != 0)
    {
        //printf("get error occured\n");

        return false;
    }
    while(tmpword<=word)
    {
        if(tmpword == word)
        {
         //   printf("*** 1\n");
            *pos = postmp1;
            return true;
        }
        if(postmp == end_pos)
        {
           // printf("*** 2\n");
            *pos = postmp;
            return false;
        }
        postmp1 = postmp;
        i = get(&postmp,&tmpword,nullptr,nullptr);
       // printf("*** 3\n");
        if(i != 0)
        {
           // printf("get error occured\n");
            return false;
        }
    }
   // printf("*** 4\n");
    *pos = postmp1;
    return false;


}
bool w_File::eof()
{
    return m_file.eof();
}
int w_File::update(long int pos, w_String word, int size, int duplicate)
{
  //  printf("   %d, %s, %d, %d\n",pos, (char*)word, size, duplicate);
    long int tmp = pos;
    int i = get(&tmp, nullptr, nullptr,nullptr);
    if(i != 0)
    {
        printf("get error occured\n");
        return 1;
    }
    int length = tmp-pos;
    char* buff = new char[100];
    sprintf(buff, ",%d,%d\n", size,duplicate);
    char tmpc = buff[0];
    int counter = 0;
    while(tmpc != 0)
    {
        counter++;
        tmpc = buff[counter];
    }
    int entrySize = word.size()+counter;
    m_file.seekp(pos, m_file.beg);
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    if(entrySize == length)
    {
        m_file<<word<<','<<size<<','<<duplicate<<'\n';
    }
    else if(entrySize > length)
    {
        shift(pos, entrySize-length);
        m_file.seekp(pos, m_file.beg);
        m_file<<word<<','<<size<<','<<duplicate<<'\n';
    }
    else
    {
        printf("Mysterious length error occured\n");
        return 3;
    }
    m_file.flush();
    return 0;

}

void w_File::clear()
{
    m_file.clear();
}

int w_File::insert(long int pos, w_String word, int size, int duplicate)
{
    //printf("aaa- insert: %d, %s, %d, %d\n",pos, (char*)word, size, duplicate);
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();
    //printf("aaa- endpos= %d",endpos);
    //aaa if((pos > endpos)&&endpos!=-1 || pos < 0)
    if((pos > endpos&&endpos!=-1)  || pos < 0)
    {
     //   printf("--- pos: %d, endpos: %d || %d\n",pos, endpos, (pos<0));
        printf("(insert )Invalid position: %d\n",pos);
        return 1;
    }
    char* buff = new char[100];
    sprintf(buff, ",%d,%d\n", size,duplicate);
    char tmp = buff[0];
    int counter = 0;
    while(tmp != 0)
    {
        counter++;
        tmp = buff[counter];
    }
    long int entrySize = word.size()+counter; //+1;
   // printf("%d\n",entrySize);
    m_file.seekp(pos, m_file.beg);
    shift(pos, entrySize);
    m_file.seekp(pos, m_file.beg);
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    m_file<<word<<','<<size<<','<<duplicate<<'\n';
    m_file.flush();
    return 0;
}
int w_File::get(long int *pos, w_String *word, int *size, int *duplicate)
{
    printf("aaa inside get: pos=%d\n", *pos);
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();
    if((*pos > endpos&&endpos!=-1)  ||* pos < 0)
    {
        printf("(get)Invalid position: %d\n",*pos);
        return 1;
    }
    m_file.seekp(*pos, m_file.beg);
    printf("aaa- get after seekp %d\n",m_file.tellp());
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    printf("aaa- get 1\n");
    char* buff = new char[100];
    m_file.getline(buff, 100, ',');

    printf("aaa- get 2\n");
    if(m_file.eof())
    {
        //printf("aaa- eof\n");
        *pos = 0;
        return 3;
    }
    if(word == nullptr)
    {
       // printf("...word null\n");
        m_file.getline(buff,100,'\n');
        *pos = m_file.tellp();
        return 0;
    }
    word->set(buff);
    if(size == nullptr || duplicate == nullptr)
    {
        m_file.getline(buff,100,'\n');
        *pos = m_file.tellp();
        return 0;
    }
    m_file>>*size;
    m_file.get();
    m_file>>*duplicate;
    m_file.get();
    *pos = m_file.tellp();
    return 0;

}

int w_File::shift(long int pos, long int shift)
{
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();
    if((pos > endpos&&endpos!=-1) || pos < 0)
    {
        printf("(shift)Invalid position: %d\n",pos);
        return 1;
    }
    if(pos==endpos) //aaa: all good, no need for shifting
        return 0;

    char* buff = new char[shift];
    m_file.seekp(0,m_file.end);
    if(m_file.bad())
    {
        perror("seek to end");
    }
    m_file.write(buff, shift);
    if(m_file.bad())
    {
        perror("append");
    }

    long int c_pos = m_file.tellp() - shift*2;
    int runTimes = (endpos-pos)/shift;
    int remainderBytes = (endpos-pos)%shift;
    for(int i = 0; i<runTimes; i++)
    {
        m_file.seekp(c_pos);
        m_file.read(buff, shift);
        m_file.write(buff, shift);
        c_pos -= shift;
    }

    if(remainderBytes!=0)
    {
        m_file.seekp(pos);
        m_file.read(buff,remainderBytes);
        m_file.seekp(pos+shift);
        m_file.write(buff,remainderBytes);
    }
    // one more shift, this time from 'pos'
   /* m_file.seekp(pos);
    m_file.read(buff, shift);
    m_file.write(buff, shift);*/

    delete buff;
    if(m_file.bad())
    {
        return 2;
    }
    return 0;
}
