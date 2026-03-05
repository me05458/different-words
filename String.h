#include "List.h"
#ifndef STRING_H
#define STRING_H
class String {
private:
    List<char> m_word;
public:
    String(List<char> word);
    String(const char *word, int size);
    ~String();
    bool operator==(const String &s);
    bool operator<(const String &s);
    bool operator>(const String &s);
    bool operator<=(const String &s);
    bool operator>=(const String &s);
    bool operator!=(const String &s);


    int size() const;
    bool isEmpty() const;
    char charAt(int i) const;
    void append(char c);
    void addAt(char c, int i);
    void set(List<char> word);

};

#endif
