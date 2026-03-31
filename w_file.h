#ifndef FILE_H
#define FILE_H
#include "w_String.h"
#include <fstream>

using namespace std; //use things like cin without std::cin
class w_File { //manages files
public:
    w_File(w_String name); //constructor
    ~w_File(); //destructor
    bool findWord(w_String word, long int* pos); //locate a word, pos returns either position of word or position where word should be added, the bool return value is true if found and false otherwise
    bool eof(); //used to check if the stream's at the end of the file

    //these return values of int are 0 if it worked, and some exit code otherwise:
    int update(long int pos, w_String word, int size, int duplicate); //change an entry
    int insert(long int pos, w_String word, int size, int duplicate); //add an entry
    int get(long int *pos, w_String *word, int *size, int *duplicate); //get the data of an entry and move pos to the next entry
    void clear(); //uesd to run stream's clear()

private:
    int shift(long int pos, long int shift); //helper method to shift characters in a file along
    fstream m_file; //the stream of the file itself

};
#endif
