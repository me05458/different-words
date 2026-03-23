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
    printf("looking for: %s\n", (char*)word);
    m_file.seekp(0,m_file.beg);
    long int beg_pos = m_file.tellp();
    m_file.seekp(0,m_file.end);
    long int end_pos = m_file.tellp();

    //long int postmp = m_file.beg;
    long int postmp = beg_pos;
    char* buff = new char[100];
    w_String tmpword("a",1);
    printf("postmp before get: %d\n", postmp);
    int i = get(&postmp,&tmpword,nullptr,nullptr);
    long int postmp1 = beg_pos;
    printf("got: %d, %s\n", i, (char*)tmpword);
    if(i != 0)
    {
        printf("get error occured\n");
        return false;
    }
    while(tmpword<=word)
    {
        if(tmpword == word)
        {
            printf("*** 1\n");
            *pos = postmp1;
            return true;
        }
        //if(postmp == m_file.end)
        if(postmp == end_pos)
        {
            printf("*** 2\n");
            *pos = postmp1;
            return false;
        }
        postmp1 = postmp;
        i = get(&postmp,&tmpword,nullptr,nullptr);
        printf("*** 3\n");
        if(i != 0)
        {
            printf("get error occured\n");
            return false;
        }
    }
    printf("*** 4\n");
    *pos = postmp1;
    return false;


}
int w_File::update(long int pos, w_String word, int size, int duplicate)
{
    printf("---update start\n");
    printf("   %d, %s, %d, %d\n",pos, (char*)word, size, duplicate);
    long int tmp = pos;
    printf("---tmp created: %d\n",tmp);
    int i = get(&tmp, nullptr, nullptr,nullptr);
    printf("---get done, tmp= %d\n", tmp);
    if(i != 0)
    {
        printf("get error occured\n");
        return 1;
    }
    int length = tmp-pos;
    printf(" ---length= %d\n",length);
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
    printf("---size done: %d+%d=%d\n",word.size(), counter, entrySize);
    m_file.seekp(pos, m_file.beg);
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    if(entrySize == length)
    {
        printf("---size==length\n");
        m_file<<word<<','<<size<<','<<duplicate<<'\n';
        printf("---wrote to file\n");
    }
    else if(entrySize > length)
    {
        printf("---size!=length\n");
        shift(pos, entrySize-length);
        printf("---shifted\n");
        m_file.seekp(pos, m_file.beg);
        m_file<<word<<','<<size<<','<<duplicate<<'\n';
        printf("---wrote to file\n");
    }
    else
    {
        printf("Mysterious length error occured\n");
        return 3;
    }
    printf("---end update\n");
    return 0;

}
int w_File::insert(long int pos, w_String word, int size, int duplicate)
{
    printf("insert: %d, %s, %d, %d\n",pos, (char*)word, size, duplicate);
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();
    if(pos > endpos || pos < 0)
    {
        printf("--- pos: %d, endpos: %d || %d\n",pos, endpos, (pos<0));
        printf("Invalid position: %d\n",pos);
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
    printf("%d\n",entrySize);
    shift(pos, entrySize);
    m_file.seekp(pos, m_file.beg);
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    m_file<<word<<','<<size<<','<<duplicate<<'\n';
    return 0;
}
int w_File::get(long int *pos, w_String *word, int *size, int *duplicate)
{
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();
    if(*pos > endpos ||* pos < 0)
    {
        printf("Invalid position: %d\n",*pos);
        return 1;
    }
    m_file.seekp(*pos, m_file.beg);
    if(m_file.bad())
    {
        perror("seek to end");
        return 2;
    }
    char* buff = new char[100];
    m_file.getline(buff, 100, ',');
    if(word == nullptr)
    {
        printf("...word null\n");
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
    if(pos > endpos || pos < 0)
    {
        printf("Invalid position: %d\n",pos);
        return 1;
    }
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
    while(c_pos>pos)
    {
        m_file.seekp(c_pos);
        m_file.read(buff, shift);
        m_file.write(buff, shift);
        c_pos -= shift;
    }
    // one more shift, this time from 'pos'
    m_file.seekp(pos);
    m_file.read(buff, shift);
    m_file.write(buff, shift);

    delete buff;
    if(m_file.bad())
    {
        return 2;
    }
    return 0;
}
