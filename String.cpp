#include "String.h"
String::String(List<char> word)
{
    m_word = word;
}

String::~String()
{
    m_word.~List();
}

bool String::operator==(const String &s)
{
    if(m_word.size() != s.size())
    {
        return false;
    }
    for(int i = 0; i<m_word.size(); i++)
    {
        if(m_word.get(i) != s.charAt(i))
        {
            return false;
        }
    }
    return true;
}

int size()
{
    return m_word.size();
}
bool isEmpty()
{
    return m_word.isEmpty();
}
char charAt(int i)
{
    return m_word.get(i);
}
void addAt(char c, int i)
{
    m_word.add(c, i);
}
void append(char c)
{
    m_word.add(c);
}
void set(List<char> word)
{
    m_word = word;
}


bool String::operator<(const String &s)
{
    if(s == this)
    {
        return false;
    }
    int new_size = this.size;
    if(this.size > s.size)
    {
        new_size = s.size;
    }
    int i = 0;
    while(i<new_size && this.charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size != s.size;
    }
    return this.charAt(i) < s.charAt(i);

}
bool String::operator>(const String &s)
{
    if(s == this)
    {
        return false;
    }
    int new_size = this.size;
    if(this.size > s.size)
    {
        new_size = s.size;
    }
    int i = 0;
    while(i<new_size && this.charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size == s.size;
    }
    return this.charAt(i) > s.charAt(i);
}
bool String::operator<=(const String &s)
{
    if(s == this)
    {
        return true;
    }
    int new_size = this.size;
    if(this.size > s.size)
    {
        new_size = s.size;
    }
    int i = 0;
    while(i<new_size && this.charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size != s.size;
    }
    return this.charAt(i) <= s.charAt(i);
}
bool String::operator>=(const String &s)
{
    if(s == this)
    {
        return true;
    }
    int new_size = this.size;
    if(this.size > s.size)
    {
        new_size = s.size;
    }
    int i = 0;
    while(i<new_size && this.charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size == s.size;
    }
    return this.charAt(i) >= s.charAt(i);
}
bool String::operator!=(const String &s)
{
    return !(this == s);
}
