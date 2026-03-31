#ifndef W_STATS_H
#define W_STATS_H
#include <fstream>
#include "w_file.h"

struct dupStat //used to store word and amount duplicated
{
    dupStat():m_dup(0), m_first_word("",0){;} //constructor, zeroes everything
    int m_dup; //amount duplicated
    w_String m_first_word; //word
    dupStat(const dupStat &d) //can be made out of another dupStat
    :m_first_word(d.m_first_word) //equate the variables over
    {
        m_dup = d.m_dup;
    }
    bool operator<(const dupStat &s) //check <
    {
        return(m_dup<s.m_dup); //this is done by amount duplicated
    }

    bool operator==(const dupStat &s) //check  ==
    {
        return(m_dup == s.m_dup);
    }
    dupStat& operator=(const dupStat &s) //used to set dupStat equal to other dupStat
    {
        //set all instance data equal
        m_dup = s.m_dup;
        m_first_word = s.m_first_word;
        return *this; //return reference to this object
    }
};

class Stats { //used to display statistics to user
public:
    Stats(w_File *file); //constructor
    ~Stats(); //destructor
    void prepStats(); //used to set up data/arrays for later use
    void basicStats(); //simple information
    void topLengths(); //top 5 most common lengths
    void lengthGraph(); //graph of all nonzero lengths
    void topDup(); //top 10 most duplicated words
    void topLetters(); //top 5 mist common letters
    void letterGraph(); //graph of letters
    void lengthPerLetter(); //displays most common length for each letter
    void dupPerLength(); //most duplicated per length
    void dupPerLetter(); //must duplicated per letter

protected:
    w_File *m_file; //file to read
    long int m_word_num; //total amount of words
    int m_max_length; //longest word length
    long int* m_num_by_lett; //amount of words per letter
    long int* m_len_by_lett; //most common length of word per letter
    long int* m_num_by_len; //amount of words per length
    long int* m_pos_of_lett; //possition where each letter block starts in file
    dupStat** m_dup_by_len; //duplicates by length
    dupStat** m_dup_by_lett; //duplicates by letter
    w_List<dupStat*> m_most_dup; //up to top 10 most duplicated of all time list
    int mostCommonLen(char letter); //helper method to find most common length per given letter and return it. Returns zero if no words available for this letter or something went wrong.
};
#endif
