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

  //  w_Test::testStats();
    //return 0;
/*    fstream vocabulary{"data.txt", ios::in | ios::out};
    if(!vocabulary.is_open())
    {
        cout<<"File opening error occured"<<endl;
        return 0;
    }*/
    w_String filename("data.txt",8);
    w_File dataArea(filename);
    Stats s(&dataArea);

    printf("enter word(s) separated by spaces\n"
        "or enter command (ex. '-help')\n");

    char a_char = 0;
    bool keepgo = true;
    bool allgood = true;
    bool reporttime = false;
    char* buff = new char[100];

    while(true)
    {
        whilestart:
        printf("\n");
        if(cin.peek()=='\n')
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
            );
            cin.get();
        }
        else if(cin.peek()=='-')
        {
            if(reporttime && allgood)
            {
                printf("All good!\n");
            }
            allgood = true;
            reporttime = false;
            cin.get();
            switch(cin.get())
            {
                case 'h':
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
                    );
                    break;
                case 'q':
                    printf("need to go! bye!\n");
                    keepgo = false;
                    break;
                case 'd':
                    printf("Most duplicated words:\n");
                    s.topDup();
                    break;
                    /* other commands here*/
                case 's':
                    printf("Fast stats:\n");
                    s.basicStats();
                    break;
                case 'l':
                    printf("Most common word lengths:\n");
                    s.topLengths();
                    break;
                case 'L':
                    printf("Graph of lengths:\n");
                    s.lengthGraph();
                    break;
                case 't':
                    printf("Most common letters:\n");
                    s.topLetters();
                    break;
                case 'T':
                    printf("Graph of letters:\n");
                    s.letterGraph();
                    break;
                case 'g':
                    printf("length by letter\n");
                    break;
                case 'f':
                    printf("letter by length\n");
                    break;
                case 'w':
                    printf("duplicate per letter\n");
                    break;

                case '\n':  //weird case of "-\n"
                        cin.putback('\n');
                default:
                        printf("uncknown command; will ignore\n");
                        break;
            }
            if(!keepgo)
            {
                break;
            }
            cin.ignore(100,'\n');
        }
        else
        {
            w_String entry("",0);
            a_char = cin.get();
            while(a_char!= ' ' && a_char!='\n')
            {
                if(a_char>='a' && a_char<='z')
                {
                    entry.append(a_char);
                }
                else if(a_char>='A' && a_char<='Z')
                {
                    printf("use all lowercase!\n");
                    cin.ignore(100,'\n');
                    goto whilestart;
                }
                else
                {
                    printf("invalid word; will ignore\n");
                    cin.ignore(100,'\n');
                    goto whilestart;
                }
                a_char=cin.get();
            }
            long int foundpos = 0;
            int oldduplicate = -1;
            //printf("pre find\n");
            bool foundWord = dataArea.findWord(entry,&foundpos);
            //printf("post find\n");
            long int tmpfoundpos = foundpos;
            if(foundWord)
            {
                printf("Duplicate word: ");
                entry.printString();
                printf("\n");

                allgood = false;

                int a = dataArea.get(&tmpfoundpos, &entry, &oldduplicate,&oldduplicate);
                if(a!=0)
                {
                    printf("Get error occured\n");
                    goto whilestart;
                }

                dataArea.update(foundpos,entry,entry.size(),oldduplicate+1);
            }
            else
            {
                reporttime = true;
             //   printf("NOT duplicate word: ");
               // entry.printString();
                //printf("\n");
                if(foundpos == -1)
                {
                    //printf("wow -1\n");
                    dataArea.insert(0,entry,entry.size(),1);
                }
                else
                {
                    dataArea.insert(foundpos,entry,entry.size(),1);
                }

            }

            if(a_char == '\n')
            {
                if(allgood)
                {
                    printf("All good!\n");
                }
                allgood = true;
            }

        }
    }


   // printf("at the very end\n");



    return 0;
}
