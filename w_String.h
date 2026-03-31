#include "w_List.h"
#ifndef w_STRING_H
#define w_STRING_H
class w_String { //stores null-terminated character list
protected:
    w_List<char> m_word; //list of characters
public:
    w_String(w_List<char>& word); //constructors (a whole bunch):
    w_String();
    w_String(const char *word="", int size=0);
    w_String(const char *word);
    ~w_String(); //destructor
    bool operator==(const w_String &s); //a whole bunch of comparison operators
    bool operator<(const w_String &s);
    bool operator>(const w_String &s);
    bool operator<=(const w_String &s);
    bool operator>=(const w_String &s);
    bool operator!=(const w_String &s);
    w_String& operator=(const w_String &s); //equating operator
    operator char*() const; //conversion to char*


    int size() const; //gets the size (number of characters)
    bool isEmpty() const; //is it empty?
    char charAt(int i) const; //gets a char from the given position
    void append(char c); //adds a char to the end
    bool addAt(char c, int i); //adds a cahr to specified position
    void set(w_List<char> &word); //changes the string to use the given list
    void set(char* arr); //changes the string ot use the given array for its list

    void printString(); //function for testing to print out all characters, not really needed but potentially useful for testing

};

#endif
