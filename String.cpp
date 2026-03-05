#include "String.h"
#include "List.h"
String::String(List<char> word)
{
    m_word = word;
}

String::String(const char* word, int size)
{
    m_word = List<char>();
    if(word == nullptr)
    {
        return;
    }
    for(int i = 0; i<size; i++)
    {
        m_word.add(word[i]);
    }
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

int String::size() const
{
    return m_word.size();
}
bool String::isEmpty() const
{
    return m_word.isEmpty();
}
char String::charAt(int i) const
{
    return m_word.get(i);
}
void String::addAt(char c, int i)
{
    m_word.add(c, i);
}
void String::append(char c)
{
    m_word.add(c);
}
void String::set(List<char> word)
{
    m_word = word;
}


bool String::operator<(const String &s)
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
bool String::operator>(const String &s)
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
bool String::operator<=(const String &s)
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
bool String::operator>=(const String &s)
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
bool String::operator!=(const String &s)
{
    return !(*this == s);
}
