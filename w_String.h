#include "w_List.h"
#ifndef w_STRING_H
#define w_STRING_H
class w_String {
private:
    w_List<char> m_word;
public:
    w_String(w_List<char>& word);
    w_String(const char *word, int size);
    ~w_String();
    bool operator==(const w_String &s);
    bool operator<(const w_String &s);
    bool operator>(const w_String &s);
    bool operator<=(const w_String &s);
    bool operator>=(const w_String &s);
    bool operator!=(const w_String &s);


    int size() const;
    bool isEmpty() const;
    char charAt(int i) const;
    void append(char c);
    bool addAt(char c, int i);
    void set(w_List<char> &word);

    void printString();

};

#endif
