#include <iostream>
#include "w_String.h"
#include "test.h"
#include "w_file.h"
#include <cstddef>
#include <fstream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

using namespace std;


int main() {
/*    fstream vocabulary{"data.txt", ios::in | ios::out};
    if(!vocabulary.is_open())
    {
        cout<<"File opening error occured"<<endl;
        return 0;
    }*/

    w_String filename("data.txt",8);
    w_File dataArea(filename);

    printf("enter word(s) separated by spaces\n"
        "or enter command (ex. '-help')\n");

    char a_char = 0;
    bool keepgo = true;
    char* buff = new char[100];

    while(true)
    {
        whilestart:
        if(cin.peek()=='\n')
        {
            printf("imagine help here\n");
            cin.get();
        }
        else if(cin.peek()=='-')
        {
            cin.get();
            switch(cin.get())
            {
                case 'h':
                    printf("imagine useful info here\n");
                    break;
                case 'q':
                    printf("need to go! bye!\n");
                    keepgo = false;
                    break;
                case 'l':
                    printf("10 longest words displayed here\n");
                    break;
                case 'd':
                    printf("10 most duplicated words displayed here\n");
                    break;
                    /* other commands here*/

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
                if(a_char>='A' && a_char<='z')
                {
                    entry.append(a_char);
                }
                else
                {
                    printf("invalid word; will ignore\n");
                    goto whilestart;
                }
                a_char=cin.get();
            }
            printf("word: ");
            entry.printString();
            printf("\n");
            //int length = entry.size();
            //sprintf(buffer,"%s,%d,%d\n",entry,entry.size(),1);
            //entry.set(buffer);
            dataArea.insert(0,entry,entry.size(),1);
        }
    }





    return 0;
}
