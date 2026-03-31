#include "w_String.h"
#include <cstdio>
#include "w_List.h"
w_String::w_String(w_List<char>& word) //constructor from a list
: m_word(word) //just equate the word to the list
{
   m_word.add(0); //add the compatibility null character at the end
}


w_String::w_String(const char* word, int size) //constructor from array given its size
{
    if(word == nullptr) //array was bad
    {
        return;
    }
    for(int i = 0; i<size; i++) //run until size
    {
        m_word.add(word[i]); //add the corresponding character
    }
    m_word.add(0); //add the null character
}

w_String::w_String(const char* word) //constructor from null-terminated array
{
    if(word == nullptr) //bad array
    {
        return;
    }
    //at least 1 character exists in array
    char tmp = word[0]; //this will store the current read character
    int i = 0; //position in array we're reading from
    while(tmp != 0) //until we hit the null character
    {
        m_word.add(tmp); //add the character to our word
        i++; //increase position read
        tmp = word[i]; //udpate character
    }
    m_word.add(0); //add our null character
}

w_String::~w_String() //destructor (doesn't need to do anything)
{
}

void w_String::printString() //was used for testing, prints out the whole string. Strings are compatible with char* so this isn't necessary, but may still be handy
{
    for(int i = 0; i<this->size(); i++) //just print out each character
    {
        printf("%c",this->charAt(i));
    } //does not add newline
}

w_String& w_String::operator=(const w_String &s) //equate to another string
{
    m_word = s.m_word; //sets words equal
    return *this; //returns itself
}

bool w_String::operator==(const w_String &s) //strings are compared alphabetically
{
    if(this->size() != s.size()) //different sizes means not equal for sure
    {
        return false;
    }
    for(int i = 0; i<m_word.size(); i++) //run through whole word
    {
        if(charAt(i) != s.charAt(i)) //if any two characters aren't the same
        {
            return false; //not equal
        }
    }
    return true; //otherwise, all good
}

int w_String::size() const //get size
{
    return m_word.size()-1; //size of internal list ignoring the null character
}

w_String::operator char*() const //conversion to character array
{
    return m_word.get(0); //just return the address of the first element of the list
}

bool w_String::isEmpty() const //checks emptiness of list
{
    return m_word.isEmpty();
}
char w_String::charAt(int i) const
{
    if(m_word.get(i) == nullptr) //if getting didn't work
    {
        return NULL; //null characters are a real thing
    }
    return *m_word.get(i); //otherwise return the contents of the address get gave
}
bool w_String::addAt(char c, int i)
{
    int a = m_word.add(i, c); //call the list's method
    if(a == -1) //exit code
    {
        return false; //false means faliure
    }
    return true; //success
}
void w_String::append(char c)
{
    m_word.add(this->size(),c); //just add to end
}
void w_String::set(w_List<char> &word) //set to a list (also used for equating things)
{
    m_word = word; //set the words
    m_word.add(0); //add the null character
}

void w_String::set(char* arr) //set from null-terminated array
{
    if(arr == nullptr) //bad array
    {
        return;
    }
    m_word.clear(); //get rid of existing list contents
    char tmp = arr[0]; //this will be the character currently read from arr
    int counter = 0; //this will be the position in arr read from
    while(tmp != 0) //until the null character is reached
    {
        m_word.add(tmp); //add arr's character
        counter++; //increase position
        tmp = arr[counter]; //update tmp
    }
    m_word.add(0); //add the null character

}


bool w_String::operator<(const w_String &s)
{
    if(*this == s)//this is strictly less tahn
    {
        return false;
    }
    //this code is to find out the smaller size
    int new_size = this->size();
    if(this->size() > s.size())
    {
        new_size = s.size();
    }
    //index to run through the lists
    int i = 0;
    while(i<new_size && this->charAt(i) == s.charAt(i)) //until end of size and as long as the characters are equal
    {
        i++; //keep going nothing is known
    }
    if(i == new_size) //if we've reached the end of the word and all characters are equal
    {
        return new_size != s.size(); //true if the other word's bigger, otherwise they're equal!
    }
    return this->charAt(i) < s.charAt(i); //check which character is bigger

}
bool w_String::operator>(const w_String &s) //same as < but opposite sign
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
    if(*this == s || *this < s) //either equal or <
    {
        return true;
    }
    return false; //otherwise no
}
bool w_String::operator>=(const w_String &s) //same as >= but with different sign
{
    if(*this == s || *this > s)
    {
        return true;
    }
    return false;
}
bool w_String::operator!=(const w_String &s) //returns opposite of ==
{
    return !(*this == s);
}
