#include "stats.h"
#include <iostream>
#define MAXDUP 10 //this is how many duplicate words are printed

Stats::Stats(w_File *file)
:m_most_dup(MAXDUP,MAXDUP)
{
    //variables
    m_file = file;
    m_word_num = 0;
    m_max_length = 0;
    //this initializes the arrays with new -> sets all items to 0
    m_num_by_lett = new long int[26];
    m_num_by_len = new long int[50];
    m_pos_of_lett = new long int[26];
    m_dup_by_len = new dupStat*[50];
    m_dup_by_lett = new dupStat*[26];
    m_len_by_lett = new long int[26];
    for(int i = 0; i<26; i++)
    {
        m_dup_by_lett[i]=new dupStat; //need to populate dupStat arrays with dupStats
    }
    for(int i = 0; i<50; i++)
    {
        m_dup_by_len[i]=new dupStat;
    }
}
Stats::~Stats() //destructor to clean everything up
{
    for(int i = 0; i<m_most_dup.size(); i++) //go through the duplicate list
    {
        delete *m_most_dup.get(i);
    }
    for(int i = 0; i<26; i++) //these two fors are for the two duplicate arrays
    {
        delete m_dup_by_lett[i];
    }
    for(int i = 0; i<50; i++)
    {
        delete m_dup_by_len[i];
    }
    //all the other arrays
    delete m_num_by_lett;
    delete m_num_by_len;
    delete m_pos_of_lett;
    delete m_dup_by_len;
    delete m_dup_by_lett;
    delete m_len_by_lett;
}

int Stats::mostCommonLen(char letter) //most common length per letter
{
    int *lenCounter = new int[50]; //array to count amount each length is used
    long int pos = 0; //position in file for moving along
    char tmpLett = 'a'-1; //temporary letter that gets read from file
    int tmpLen = 0; //temporary length that gets read from file
    int foo = 0; //dummy variable used to get write unneeded duplicate value from file into
    w_String tmpWord("",0); //temporary word that gets read from file
    while(tmpLett<letter) //read until the letter of interest (letters are in order)
    {
        if(m_file->get(&pos,&tmpWord,&tmpLen,&foo) != 0) //error occured!
        {
            m_file->clear();
            return 0;
        }
        tmpLett=tmpWord.charAt(0); //otherwise, change tmpLett and keep going to next one
    }
    if(tmpLett>letter) //this happens if the letter doesn't exist in file
    {
        return 0;
    }

    while(tmpLett==letter) //run through all of the words with the letter of interst
    {
        if(m_file->get(&pos,&tmpWord,&tmpLen,&foo) != 0) //error occured (exit while)
            break;
        tmpLett=tmpWord.charAt(0); //update letter
        lenCounter[tmpLen]++; //increment the correct spot in the counter array
    }

    int mostCommon = 0; //single most common length per letter
    for(int i = 0; i<50; i++) //run through the counter array and find most common length
    {
        if(lenCounter[i] > mostCommon)
        {
            mostCommon = i;
        }
    }
    return mostCommon; //return it
}

void Stats::basicStats() //simple stats
{
    prepStats(); //load all of the data arrays
    char mostLett = 'a'; //this will be the most common letter, default = 'a'
    int maxOccur = m_num_by_lett[0]; //maximum amount the letter occurs
    for(int i=0; i<26; i++) //run through all of the letters
    {
        if(m_num_by_lett[i] > maxOccur) //if the ith letter occurs more than current max occurence...
        {
            maxOccur = m_num_by_lett[i]; //update max occurence
            mostLett = i+'a'; //update letter itself
        }
    }
    int mostLen = 3; //now it's time for most common length, default = 3
    maxOccur = m_num_by_len[3]; //maximum amount the length occurs
    for(int i=0; i<50; i++) //same as for letter, except run through lengths array
    {
        if(m_num_by_len[i] > maxOccur)
        {
            maxOccur = m_num_by_len[i];
            mostLen = i;
        }
    }
    printf("Number of words: %d\n"
        "Most duplicated word: ",m_word_num); //display number of words (made in prepStats())
    //find most duplicated word:
    if((m_most_dup.size())==0) //no duplicated words
    {
        printf ("none\n");
    }
    else //duplicate words are sorted, so simply get the first one and print its word
    {
        printf("%s\n",(char*)(*m_most_dup.get(0))->m_first_word);
    }
    //display first letter/word length here
    printf("Most common first letter: %c\n",mostLett);
    printf("Most common word length: %d\n",mostLen);
}

void Stats::topLengths() //top 5 most common letters
{
    prepStats();
    int length[5] = {0,0,0,0,0}; //will store top five lengths
    int num[5] = {0,0,0,0,0}; //will store occurence frequency of those lengths
    for(int i = 0; i<50; i++) //run through all of the lengths
    {
        if(m_num_by_len[i]>num[0]) //if it's the biggest one, update length[0] and num[0]
        {
            num[0]=m_num_by_len[i];
            length[0] = i;
        }
        else if(m_num_by_len[i]>num[1]) //otherwise it could be the 2nd biggest one
        {
            num[1]=m_num_by_len[i];
            length[1] = i;
        }
        else if(m_num_by_len[i]>num[2])
        {
            num[2]=m_num_by_len[i];
            length[2] = i;
        }
        else if(m_num_by_len[i]>num[3])
        {
            num[3]=m_num_by_len[i];
            length[3] = i;
        }
        else if(m_num_by_len[i]>num[4]) //all the way through the fifth biggest one
        {
            num[4]=m_num_by_len[i];
            length[4] = i;
        }
    }
    for(int i = 1; i<=5; i++) //print them out in order
    {
        if(num[i-1] == 0) //there might be less than 5 length, so print N/A
        {
            printf("%d: N/A\n",i);
        }
        else
        {
            printf("%d: %d\n",i,length[i-1]); //print the length
        }
    }
}
void Stats::lengthGraph() //visually show different length frequencies
{
    prepStats();
    int maxLength = 0; //this is the most common length (to scale graph)
    int maxNum = 0; //this is how much that length occurs
    for(int i = 0; i<50; i++) //run through all lengths and find the longest one
    {
        if(m_num_by_len[i]>maxNum)
        {
            maxNum=m_num_by_len[i];
            maxLength = i;
        }
    }

    printf("length | number of words \n"); //pretty formatting stuff
    for(int i = 0; i<50; i++) //run through all lengths
    {
        if(m_num_by_len[i] != 0) //only applies if length has words
        {
            printf("   %d ",i); //the length itself (stored by length)
            if(i/10 == 0) //formatting to make single digits look nice
            {
                printf(" ");
            }
            printf(" | ");
            //Following line finds the amount of characters to print for traph as a percentage of maxium frequency of length
            //50 is the size to scale to
            //everything is in double math until the end to reduce error
            int runNum = int(double(50)*double(m_num_by_len[i])/double(maxNum));
            for(int j = 0; j<runNum; j++) //print the graph's line'
            {
                printf("_");
            }
            printf(" %d\n",m_num_by_len[i]); //print the exact number the graph is showing
        }
    }


}
void Stats::topDup() //most duplicated words
{
    prepStats();
    if(m_most_dup.size() == 0) //no words are duplicated
    {
        printf("none\n");
        return;
    }
    //run through list of duplicates
    for(int i = 0; i<m_most_dup.size(); i++)
    {
        printf("%d: %s\n",i+1,(char*)(*m_most_dup.get(i))->m_first_word); //print that duplicate
    }
}
void Stats::topLetters() //top 5 letters, very similar to top 5 lengths
{
    prepStats();
    int lett[5] = {0,0,0,0,0};
    int num[5] = {0,0,0,0,0};
    for(int i = 0; i<26; i++) //26 instead of 50 because there are 26 letters
    {
        if(m_num_by_lett[i]>num[0])
        {
            num[0]=m_num_by_lett[i];
            lett[0] = i;
        }
        else if(m_num_by_lett[i]>num[1])
        {
            num[1]=m_num_by_lett[i];
            lett[1] = i;
        }
        else if(m_num_by_lett[i]>num[2])
        {
            num[2]=m_num_by_lett[i];
            lett[2] = i;
        }
        else if(m_num_by_lett[i]>num[3])
        {
            num[3]=m_num_by_lett[i];
            lett[3] = i;
        }
        else if(m_num_by_lett[i]>num[4])
        {
            num[4]=m_num_by_lett[i];
            lett[4] = i;
        }
    }
    for(int i = 1; i<=5; i++)
    {
        if(num[i-1] == 0)
        {
            printf("%d: N/A\n",i);
        }
        else
        {
            printf("%d: %c\n",i,lett[i-1]+'a'); //letter adjustment here is needed because 'a' is not zero (as stored in the list of letters) so must add the value of 'a' to it. Letters are in order.
        }
    }
}
void Stats::letterGraph() //very similar to length graph
{
    prepStats();
    int length = 0;
    int num = 0;
    for(int i = 0; i<26; i++)
    {
        if(m_num_by_lett[i]>num)
        {
            num=m_num_by_lett[i];
            length = i;
        }
    }

    printf("letter | number of words \n");
    for(int i = 0; i<26; i++) //again, there are 26 letters
    {
        if(m_num_by_lett[i] != 0)
        {
            printf("   %c ",i+'a'); //this shifting of the character is again needed
            printf(" | ");
            int runNum = int(double(50)*double(m_num_by_lett[i])/double(num));
            for(int j = 0; j<runNum; j++)
            {
                printf("_");
            }
            printf(" %d\n",m_num_by_lett[i]);
        }
    }
}
void Stats::lengthPerLetter() //display most common length per each letter
{
    int tmp = 0; //this is to track mostCommonLen's output
    for(int i = 0; i<26; i++) //for all letters
    {
        tmp = mostCommonLen(i+'a'); //call helper to find most common length for that letter
        if(tmp != 0 ) //only if there is a legitimate length for that letter
        {
            printf("%c: %d\n",i+'a',tmp); //display it
        }
    }
}
void Stats::dupPerLength() //displays most duplicated word by length
{
    prepStats();
    for(int i = 0; i<50; i++) //for all lengths
    {
        if(m_dup_by_len[i]->m_dup != 0) //as long as it has a duplicate...
        {
            printf("%d: %s\n",i,(char*)m_dup_by_len[i]->m_first_word); //display that word
        }
    }
}
void Stats::dupPerLetter() //like dupPerLength but for letter instead of length
{
    prepStats();
    for(int i = 0; i<26; i++) //there are 26 letters
    {
        if(m_dup_by_lett[i]->m_dup != 0)
        {
            printf("%c: %s\n",i+'a',(char*)m_dup_by_lett[i]->m_first_word);
        }
    }
}

void Stats::prepStats() //used to populate/update the arrays of data
{
    for(int i = 0; i<26; i++) //clear out the duplicate arrays so that old data doesn't interfere
    {
        delete m_dup_by_lett[i];
        m_dup_by_lett[i]=new dupStat;
    }
    for(int i = 0; i<50; i++)
    {
        delete m_dup_by_len[i];
        m_dup_by_len[i]=new dupStat;
    }
    //clear out the list
    m_most_dup.clear();
    m_word_num = 0; //set the word number to zero (will recount)
    if(m_file == nullptr) //if file doesn't exist, should not attempt to read it
        return;

    for(int i = 0; i<50; i++) //clear lengths
    {
        m_num_by_len[i] = 0;
    }
    for(int i = 0; i<26; i++) //clear letters
    {
        m_num_by_lett[i] = 0;
    }
    long int currentpos = 0; //current line beign read from file (start at begining)
    w_String readWord("",0); //word read from file
    int readLen = 0; //length read from file
    int readDup = 0; //duplicate read from file
    while(!m_file->eof()) //until the end of the file
    {
        whilestart: //this is used for gotos later

        m_file->get(&currentpos,&readWord,&readLen,&readDup); //read the line

        if(m_file->eof()) //if that's the end of the file, end the while (this means last entry was read and currentPos got moved to the end)
        {
            break;
        }
        m_word_num++; //add an extra word
        if(readLen>m_max_length) //the observed word is longer than current recorded longest word
        {
            m_max_length = readLen; //update maximum word length
        }
        char letter = readWord.charAt(0); //the first letter of the word that was read
        int index = letter - 'a'; //index in letter array calculated from letter
        m_num_by_lett[index]++; //increment correct letter aray counter
        m_num_by_len[readLen]++; //increment correct length array counter


        if(readDup>=2) //the word is a duplicate (done more than 1 time)
        {
            dupStat* tmp = new dupStat(); //creat e new dupStat to store in duplicate lists
            tmp->m_dup = readDup; //pupulate it with read data
            tmp->m_first_word = readWord;
            int i = 0; // i is tracked here for later use
            for(i; i<m_most_dup.size(); i++) //run through whole duplicate array
            {
                if(readDup > (*m_most_dup.get(i))->m_dup) //a smaller duplication value is detected than the read one, time to insert
                {
                    break; // loop is exited
                }
            }
            if(i < MAXDUP) //this means we exited in the middle of the duplicate list
            {
                if(m_most_dup.size() == MAXDUP) //this means it's already full
                {
                    delete (*m_most_dup.get(MAXDUP-1)); //delete the last one
                    m_most_dup.remove(MAXDUP-1); //remove it from the list
                }
                m_most_dup.add(i, tmp); //insert the new dupStat
            }


            //tracks most duplicated letter
            int pos = readWord.charAt(0)-'a'; //position corresponds to first letter, is the position in letter duplicate array
            if(m_dup_by_lett[pos]->m_dup < readDup) //this word is more duplicated than currently tracked one
            {
                *m_dup_by_lett[pos] = *tmp; //update current entry
            }

            //same process for length
            pos = readLen;
            if(m_dup_by_len[pos]->m_dup < readDup)
            {
                *m_dup_by_len[pos] = *tmp;
            }
        }
    }
        m_file->clear(); //needed to have file correctly update
}
