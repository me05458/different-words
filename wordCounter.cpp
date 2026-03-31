#include <iostream>
#include "w_String.h"
#include "test.h"
#include "w_file.h"
#include "stats.h"
#include <cstddef>
#include <fstream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

using namespace std;


int main() {
    w_String filename("data.txt",8); //this is where the file is defined
    w_File dataArea(filename); //file is created
    Stats s(&dataArea); //statistics handler is created

    printf("enter word(s) separated by spaces\n"
        "or enter command (ex. '-help')\n"); //initial instruction

    char a_char = 0; //this is the character read in as words are being read
    bool keepgo = true; //continue with loop?
    bool allgood = true; //need to print "all good" (no duplicates)
    bool reporttime = false; //need to state if all good or not
    char* buff = new char[100]; //buffer for reading characters

    while(true) //runs forever
    {
        whilestart: //start of while, used by gotos
        if(cin.peek()=='\n') //show help prompt if user pressed enter
        {
            printf("Type word(s) separated by spaces or any of the following commands (CASE MATTERS):\n"
            "-h Help (this list)\n"
            "-q Quit\n"
            "-s get quick Stats\n"
            "-l get 5 most common word Lengths\n"
            "-L get graph of words per Length\n"
            "-d get 10 most Duplicated words\n"
            "-t get 5 most common first leTters\n"
            "-T get graph of words per leTter\n"
            "-g get most common lenGth by first letter\n"
            "-f get most common First letter by length\n"
            "-w get most common duplicate Word per letter\n"
            "-W get most common duplicate Word per length\n"
            );
            cin.get(); //get rid of the \n that's in cin or it will loop forever
        }
        else if(cin.peek()=='-') //a command is written
        {

            cin.get(); //get rid of the '-'
            if(reporttime && allgood && cin.peek() != 'q') //if we've been waiting to report that it's good, do so now
            {
                printf("All good!\n");
            }
            allgood = true; //set them back to initial values
            reporttime = false;
            switch(cin.get()) //switch for the next character
            {
                case 'h': //help
                    printf("Type word(s) separated by spaces or any of the following commands (CASE MATTERS):\n"
                    "-h Help (this list)\n"
                    "-q Quit\n"
                    "-s get quick Stats\n"
                    "-l get 5 most common word Lengths\n"
                    "-L get graph of words per Length\n"
                    "-d get 10 most Duplicated words\n"
                    "-t get 5 most common first leTters\n"
                    "-T get graph of words per leTter\n"
                    "-g get most common lenGth by first letter\n"
                    "-w get most common duplicate Word per letter\n"
                    "-W get most common duplicate Word per length\n"
                    );
                    break;
                case 'q': //quit
                    printf("Good luck with your words!\n");
                    keepgo = false; //time to stop going
                    break;
                case 'd': //most duplicated
                    printf("Most duplicated words:\n");
                    s.topDup();
                    break;
                case 's': //quick stats
                    printf("Fast stats:\n");
                    s.basicStats();
                    break;
                case 'l': //most common word length
                    printf("Most common word lengths:\n");
                    s.topLengths();
                    break;
                case 'L': //graph of lengths
                    printf("Graph of lengths:\n");
                    s.lengthGraph();
                    break;
                case 't': //most common letters
                    printf("Most common letters:\n");
                    s.topLetters();
                    break;
                case 'T': //graph of letters
                    printf("Graph of letters:\n");
                    s.letterGraph();
                    break;
                case 'g': //length by letter
                    printf("Length by letter:\n");
                    s.lengthPerLetter();
                    break;
                case 'w': //duplicate by letter
                    printf("Duplicate per letter:\n");
                    s.dupPerLetter();
                    break;
                case 'W': //duplicate by length
                    printf("Duplicate per length:\n");
                    s.dupPerLength();
                    break;

                case '\n':  //weird case of "-\n"
                        cin.putback('\n'); //we need cin to have a '\n' now, so put it back
                        //proceed to default
                default:
                        printf("uncknown command; will ignore\n"); //warn
                        break;
            }
            if(!keepgo) //if we don't want to keep going anymore
            {
                break; //break the while
            }
            cin.ignore(100,'\n'); //at end of command, ignore the rest of anything written until next newline
        }
        else //words!
        {
            w_String entry("",0); //this will be the word
            a_char = cin.get(); //read the first character of the word
            while(a_char!= ' ' && a_char!='\n') //keep going while in the word
            {
                if(a_char>='a' && a_char<='z') //valid character
                {
                    entry.append(a_char); //add the letter to the word
                }
                else if(a_char>='A' && a_char<='Z') //only lowercase are allowed
                {
                    printf("use all lowercase!\n");
                    cin.ignore(100,'\n');
                    goto whilestart; //stop collecting words, repeat while
                }
                else //not a letter was used
                {
                    printf("invalid word; will ignore\n");
                    cin.ignore(100,'\n');
                    goto whilestart; //stop collecting words, repeat while
                }
                a_char=cin.get(); //get the next letter
            }
            long int foundpos = 0; //place where this word exists or should go
            int oldduplicate = -1; //amount word was duplicated before this one showed up
            bool foundWord = dataArea.findWord(entry,&foundpos); //find word, see if it exists or not
            long int tmpfoundpos = foundpos; //temporary position to use with gets that does not mess up foundpos
            if(foundWord) //duplicate
            {
                printf("Duplicate word: %s\n",(char*)entry); //display it as duplicate

                allgood = false; //not all not duplicate

                //get the current entry from the file. Oldduplicate is used twice because we don't care about length for this, so might as well reuse it.
                int a = dataArea.get(&tmpfoundpos, &entry, &oldduplicate,&oldduplicate);
                if(a!=0) //check for exit codes of get
                {
                    printf("Get error occured\n");
                    goto whilestart; //stop trying to do things here
                }

                dataArea.update(foundpos,entry,entry.size(),oldduplicate+1); //update it with the duplicate number being one mroe
            }
            else //not duplicate
            {
                reporttime = true; //in the case that a command comes next, report that all's good
                if(foundpos == -1) //this means file has nothing in it
                {
                    dataArea.insert(0,entry,entry.size(),1); //write to 0th position
                }
                else //otherwise
                {
                    dataArea.insert(foundpos,entry,entry.size(),1); //just write at foundposition to insert entry
                }

            }

            if(a_char == '\n') //at end of line of words
            {
                if(allgood) //if no duplicates observed print so
                {
                    printf("All good!\n");
                }
                allgood = true; //back to original value
            }

        }
    }
    return 0;
}
