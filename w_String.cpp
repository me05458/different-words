#include "w_String.h"
#include "w_List.h"
w_String::w_String(w_List<char> word)
{
    m_word = word;
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
}

w_String::~w_String()
{
}

bool w_String::operator==(const w_String &s)
{
    if(m_word.size() != s.size())
    {
        return false;
    }
    for(int i = 0; i<m_word.size(); i++)
    {
        if(*m_word.get(i) != s.charAt(i))
        {
            return false;
        }
    }
    return true;
}

int w_String::size() const
{
    return m_word.size();
}
bool w_String::isEmpty() const
{
    return m_word.isEmpty();
}
char w_String::charAt(int i) const
{
    return *m_word.get(i);
}
void w_String::addAt(char c, int i)
{
    m_word.add(c, i);
}
void w_String::append(char c)
{
    m_word.add(c);
}
void w_String::set(w_List<char> word)
{
    m_word = word;
}


bool w_String::operator<(const w_String &s)
{
    if(this == &s)
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
    if(this == &s)
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
    if(this == &s)
    {
        return true;
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
    return this->charAt(i) <= s.charAt(i);
}
bool w_String::operator>=(const w_String &s)
{
    if(this == &s)
    {
        return true;
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
    return this->charAt(i) >= s.charAt(i);
}
bool w_String::operator!=(const w_String &s)
{
    return !(*this == s);
}
