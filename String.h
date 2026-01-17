#include "List.h"
class String {
public:
    String(List<char> word);
    ~String();
    bool operator==(const String &s);
    bool operator<(const String &s);
    bool operator>(const String &s);
    bool operator<=(const String &s);
    bool operator>=(const String &s);
    bool operator!=(const String &s);


    int size();
    bool isEmpty();
    char charAt(int i);
    void append(char c);
    void addAt(char c, int i);
    void set(List<char> word);
private:
    List<char> m_word;
};
