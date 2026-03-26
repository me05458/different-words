#ifndef FILE_H
#define FILE_H
#include "w_String.h"
#include <fstream>

using namespace std;
class w_File { //array list, specifically
public:
    w_File(w_String name);
    ~w_File();
    bool findWord(w_String word, long int* pos);
    bool eof();
    int update(long int pos, w_String word, int size, int duplicate);
    int insert(long int pos, w_String word, int size, int duplicate);
    int get(long int *pos, w_String *word, int *size, int *duplicate);

private:
    int shift(long int pos, long int shift);
    fstream m_file;

};
#endif
