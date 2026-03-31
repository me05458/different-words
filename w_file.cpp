#include "w_file.h"
#include <cerrno> //for error handling
#include <iostream>
#include <fstream>
#include <filesystem>

w_File::w_File(w_String name) //constructor
:m_file(name) //initialize the stream
{

    if(!m_file.is_open()) //file did not correctly load; warn user
    {
        printf("w_File error occured\n");
    }
}
w_File::~w_File() //destructor
{
    m_file.close(); //gracefully close file
}
bool w_File::findWord(w_String word, long int* pos) //locate a word, returns false if no word exists, true if it's found
{
    //identify begining and end of file for checking
    m_file.seekp(0,m_file.beg);
    long int beg_pos = m_file.tellp();
    m_file.seekp(0,m_file.end);
    long int end_pos = m_file.tellp();

    //this is the position that iterates through teh file, start it at the begining
    long int postmp = beg_pos;
    char* buff = new char[100]; //buffer for reading from file
    w_String tmpword("a",1); //word used to read from file
    int i = get(&postmp,&tmpword,nullptr,nullptr); //get first entry, postmp moves to next entry
    long int postmp1 = beg_pos; //stores old postmp (stores begining of entry just gotten)
    if(i != 0) //get failed
    {
        return false;
    }
    while(tmpword<=word) //we haven't gone past word yet
    {
        if(tmpword == word) //we are at the word
        {
            *pos = postmp1; //update position parameter to begining of this entry
            return true; //return true because found it
        }
        if(postmp == end_pos) //already at end of file
        {
            *pos = postmp; //update position to where the next entry (aka the sought one) would write
            return false; //did not find it
        }
        postmp1 = postmp; //move on to the next entry
        i = get(&postmp,&tmpword,nullptr,nullptr); //read it and move postmp along
        if(i != 0) //get faliure
        {
            return false;
        }
    }
    //overran where word should be without finding it, return where it should be inserted
    *pos = postmp1;
    return false; //did not find


}
bool w_File::eof() //used to check if at end of file
{
    return m_file.eof(); //just call the same thing on stream
}

int w_File::update(long int pos, w_String word, int size, int duplicate) //changes an entry
{
    long int tmp = pos; //temporary position to use in following get without messing up real pos
    int i = get(&tmp, nullptr, nullptr,nullptr); //move tmp to the end of the entry at possition pos
    if(i != 0) //get error
    {
        printf("get error occured\n");
        return 1;
    }
    int length = tmp-pos; //this is the size of the entry in characters
    char* buff = new char[100]; //buffer for reading
    sprintf(buff, ",%d,%d\n", size,duplicate); //put size and duplicate from file into buffer
    char tmpc = buff[0]; //this is the character that gets read from the buffer
    int counter = 0; //this is where in the buffer we're reading
    while(tmpc != 0) //run until null character (end of string) is found
    {
        counter++; //increment this
        tmpc = buff[counter]; //updadate temporary character
    }
    //counter now has length of the ",#,#\n" sequence at end of entry
    int entrySize = word.size()+counter; //use this to determine size of whole entry
    m_file.seekp(pos, m_file.beg); //start at position
    if(m_file.bad()) //something's wrong with the file
    {
        perror("seek to end"); //handy utility to show us the error in a nice way
        return 2;
    }
    if(entrySize == length) //no length update/moving of characters around needed
    {
        m_file<<word<<','<<size<<','<<duplicate<<'\n'; //just write that line in, it will overwrite old line
    }
    else if(entrySize > length) //length update/moving needed
    {
        shift(pos, entrySize-length); //shift over by this extra amount
        m_file.seekp(pos, m_file.beg); //go to the position to write
        m_file<<word<<','<<size<<','<<duplicate<<'\n'; //write into file
    }
    else //this will never happen in actual use of program, where duplicate number either has same number of digits or gets more digitis. Will never decrease.
    {
        printf("Mysterious length error occured\n");
        return 3;
    }
    m_file.flush(); //this makes the file update
    return 0;

}

void w_File::clear() //used to clear file
{
    m_file.clear(); //just calls stream's method
}

//add a new entry:
int w_File::insert(long int pos, w_String word, int size, int duplicate)
{
    //determine end position
    m_file.seekp(0,m_file.end);
    long int endpos = m_file.tellp();

    if((pos > endpos&&endpos!=-1)  || pos < 0) //invalid position
    {
        printf("Invalid position: %d\n",pos);
        return 1;
    }
    char* buff = new char[100]; //character buffer
    sprintf(buff, ",%d,%d\n", size,duplicate); //read in the ",#,#\n" at the end of the entry from parameters

    //same thing as above to determine length of ^ sequence
    char tmp = buff[0];
    int counter = 0;
    while(tmp != 0)
    {
        counter++;
        tmp = buff[counter];
    }
    long int entrySize = word.size()+counter; //this is now used to find total size of entry

    m_file.seekp(pos, m_file.beg); //goto position pos
    shift(pos, entrySize); //shift file to make space for new entry
    m_file.seekp(pos, m_file.beg);
    if(m_file.bad()) //file problem
    {
        perror("seek to end");
        return 2;
    }
    m_file<<word<<','<<size<<','<<duplicate<<'\n'; //write line into file
    m_file.flush(); //update file
    return 0;
}

//get a line from file
int w_File::get(long int *pos, w_String *word, int *size, int *duplicate)
{
    m_file.seekp(0,m_file.end); //find end of file
    long int endpos = m_file.tellp();
    if((*pos > endpos&&endpos!=-1)  ||* pos < 0) //bad position (don't change parameters)
    {
        printf("Invalid position: %d\n",*pos);
        return 1;
    }

    //go to position
    m_file.seekp(*pos, m_file.beg);
    if(m_file.bad()) //file issue
    {
        perror("seek to end");
        return 2;
    }

    //buffer
    char* buff = new char[100];
    m_file.getline(buff, 100, ','); //put file line up to "," into buffer

    if(m_file.eof()) //if at the end of the file
    {
        *pos = 0;
        return 3;
    }
    if(word == nullptr) //if entered is nullptr, don't update it, but do move pos along.
    {
        m_file.getline(buff,100,'\n'); //this is the movign along
        *pos = m_file.tellp();
        return 0;
    }
    word->set(buff); //otherwise, update word
    if(size == nullptr || duplicate == nullptr) //if either of tehse is nullptr, just move posa long
    {
        m_file.getline(buff,100,'\n');
        *pos = m_file.tellp();
        return 0;
    }
    //update size and duplicate
    m_file>>*size;
    m_file.get();
    m_file>>*duplicate;
    m_file.get();
    *pos = m_file.tellp(); //update position
    return 0;

}

//helper method to move along parts of file
int w_File::shift(long int pos, long int shift)
{
    m_file.seekp(0,m_file.end); //get end of file
    long int endpos = m_file.tellp();
    if((pos > endpos&&endpos!=-1) || pos < 0) //bad position
    {
        printf("Invalid position: %d\n",pos);
        return 1;
    }
    if(pos==endpos) //already at the end, nothing to shift (not an error, all is well)
        return 0;

    char* buff = new char[shift];
    m_file.seekp(0,m_file.end); //go to end
    if(m_file.bad()) //file problem
    {
        perror("seek to end");
    }
    m_file.write(buff, shift); //append empty shift characters to file
    if(m_file.bad()) //file problem
    {
        perror("append");
    }

    long int c_pos = m_file.tellp() - shift*2; //this is current position, which is shift from the end of useful file data
    int runTimes = (endpos-pos)/shift; //whole number of times shift should be run
    int remainderBytes = (endpos-pos)%shift; //remainder of characters after ^ to shift
    for(int i = 0; i<runTimes; i++) //do the whole number of shifts
    {
        m_file.seekp(c_pos); //go to position
        m_file.read(buff, shift); //read into buffer (position moves forward by shift)
        m_file.write(buff, shift); //write out of buffer into the file (thereby shifting)
        c_pos -= shift; //update c_pos to do the next shift characters
    }

    if(remainderBytes!=0) //as long as some remainders need to be shifted
    {
        m_file.seekp(pos); //go to position
        m_file.read(buff,remainderBytes); //read those remainder characters
        m_file.seekp(pos+shift); //go to position + shift where they need to go
        m_file.write(buff,remainderBytes); //write thos characters
    }


    delete buff; //get rid of buffer array
    if(m_file.bad()) //file problem
    {
        return 2;
    }
    return 0;
}
