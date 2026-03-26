#include "w_String.h"
#include <cstdio>
#include "w_List.h"
w_String::w_String(w_List<char>& word)
: m_word(word)
{
   m_word.add(0);
}


w_String::w_String(const char* word, int size)
{
    if(word == nullptr)
    {
        return;
    }
    for(int i = 0; i<size; i++)
    {
        m_word.add(word[i]);
    }
    m_word.add(0);
}

w_String::w_String(const char* word)
{
    if(word == nullptr)
    {
        return;
    }
    char tmp = word[0];
    int i = 0;
    while(tmp != 0)
    {
        m_word.add(tmp);
        i++;
        tmp = word[i];
    }
    m_word.add(0);
}

w_String::~w_String()
{
}

void w_String::printString()
{
    for(int i = 0; i<this->size(); i++)
    {
        printf("%c",this->charAt(i));
    }
}

bool w_String::operator==(const w_String &s)
{
    if(this->size() != s.size())
    {
        return false;
    }
    for(int i = 0; i<m_word.size(); i++)
    {
        if(charAt(i) != s.charAt(i))
        {
            return false;
        }
    }
    return true;
}

int w_String::size() const
{
    return m_word.size()-1;
}

w_String::operator char*() const
{
    return m_word.get(0);
}

bool w_String::isEmpty() const
{
    return m_word.isEmpty();
}
char w_String::charAt(int i) const
{
    if(m_word.get(i) == nullptr)
    {
        return NULL;
    }
    return *m_word.get(i);
}
bool w_String::addAt(char c, int i)
{
    int a = m_word.add(i, c);
    if(a == -1)
    {
        return false;
    }
    return true;
}
void w_String::append(char c)
{
    m_word.add(this->size(),c);
}
void w_String::set(w_List<char> &word)
{
    m_word = word;
    m_word.add(0);
}

void w_String::set(char* arr)
{
    if(arr == nullptr)
    {
        return;
    }
    m_word.clear();
    char tmp = arr[0];
    int counter = 0;
    while(tmp != 0)
    {
        m_word.add(tmp);
        counter++;
        tmp = arr[counter];
    }
    m_word.add(0);

}


bool w_String::operator<(const w_String &s)
{
    if(*this == s)
    {
        return false;
    }
    int new_size = this->size();
    if(this->size() > s.size())
    {
        new_size = s.size();
    }
    int i = 0;
    while(i<new_size && this->charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size != s.size();
    }
    return this->charAt(i) < s.charAt(i);

}
bool w_String::operator>(const w_String &s)
{
    if(*this == s)
    {
        return false;
    }
    int new_size = this->size();
    if(this->size() > s.size())
    {
        new_size = s.size();
    }
    int i = 0;
    while(i<new_size && this->charAt(i) == s.charAt(i))
    {
        i++;
    }
    if(i == new_size)
    {
        return new_size == s.size();
    }
    return this->charAt(i) > s.charAt(i);
}
bool w_String::operator<=(const w_String &s)
{
    if(*this == s || *this < s)
    {
        return true;
    }
    return false;
}
bool w_String::operator>=(const w_String &s)
{
    if(*this == s || *this > s)
    {
        return true;
    }
    return false;
}
bool w_String::operator!=(const w_String &s)
{
    return !(*this == s);
}
