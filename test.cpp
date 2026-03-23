#include "w_String.h"
#include "w_List.h"
#include <cstdio>
#include "w_file.h"
#include "test.h"

void w_Test::eANDs(bool empty, int size, bool want_empty, int want_size)
{
    if(empty)
    {
        printf("empty: true");
    }
    else
    {
        printf("empty: false");
    }
    printf(" size: %d\n",size);
    if(empty != want_empty)
    {
        printf("\033[1;31mFALIURE (empty)\033[0m\n");
    }
    if(size != want_size)
    {
        printf("\033[1;31mFALIURE (size)\033[0m\n");
    }
}

void w_Test::testFile2()
{
    //testing file:
    /*
     * apple,5,5
     * bear,4,9
     * cauliflower,11,1
     * dog,3,11``
     *
     *
     *
     */
    printf("TESTING FILE 2\n");
    printf("------\n------\n");
    w_String name("data.txt",8);
    w_String insertstr("author",6);
    w_String updatestr("bear",4);
    w_String updatestr2("cauliflower",11);
    w_File f(name);
     //doesn't work
    //printf("%s\n",(char*)insertstr);
    //int q = f.insert(10,insertstr,6,7);
    //printf("q: %d\n",q);
    //seg faults
    printf("update?\n");
    f.update(10,updatestr,4,10);
    printf("update!!\n");
    // seg faults
    f.update(20,updatestr2,11,2);

    int q = f.update(200,updatestr2,11,2);
    printf("q: %d\n",q);

    //yay this works !!
    w_String getWord("meh",3);
    int getsize = 0;
    int getdup = 0;
    long int ten = 10;
    int a = f.get(&ten,&getWord,&getsize,&getdup);
    getWord.printString();
    printf("\nsize: %d, duplicate: %d, counter: %d, a: %d\n",getsize,getdup,ten,a);

    ten = 90;
    a = f.get(&ten,&getWord,&getsize,&getdup);
    printf("a: %d\n",getsize,getdup,ten,a);

    w_String startword("aaa",3);
    f.insert(0,startword,3,1);

    w_String name2("data2.txt",9);
    w_File f2(name2);
    w_String emptyword("hello",5);
    int l = f2.insert(0,emptyword,5,1);
    printf("l: %d\n",l);

}

void w_Test::testFile()
{

    //testing file:
    /*
     * ffluffy,7,8
     * fluffy,6,7
     * fluffyyy,8,9
     *
     *
     *
     */
    printf("TESTING FILE:\n");
    printf("------\n------\n");
    w_String name("data.txt",8);
    w_String w("fluffy",6);
    printf("Made it past string inits\n");
    w_File f(name);
    printf("Made it past file open\n");
    long int thing;
    char buff[100];

    bool tmp = f.findWord(w, &thing);
    printf("Made it past findword\n");
    printf("%b %s %d\n", tmp, (char*)w, thing);
    if(tmp != true || thing != 12)
    {
        printf("\033[1;31mFALIURE 50\033[0m\n");
    }
    printf("tmp: %d, thing: %d\n",tmp,thing);

    buff[0] = 'c';
    buff[1] = 'a';
    buff[2] = 't';
    buff[3] = 0;
    w.set(buff);

    tmp = f.findWord(w, &thing);
    if(tmp == true)
    {
        printf("\033[1;31mFALIURE 62\033[0m\n");
    }
    printf("tmp: %d, thing: %d\n",tmp,thing);

    buff[0] = 'f';
    buff[1] = 'f';
    buff[2] = 'y';
    buff[3] = 0;
    w.set(buff);

    tmp = f.findWord(w, &thing);
    if(tmp == true)
    {
        printf("\033[1;31mFALIURE 62\033[0m\n");
    }
    printf("tmp: %d, thing: %d\n",tmp,thing);

}

void w_Test::testList()
{
    printf("TESTING LIST:\n");
    printf("------\n------\n");
    w_List<int> l(10,20);
    eANDs(l.isEmpty(),l.size(),true,0);
    int tmp = l.add(1);
    printf("adding value: %d\n",tmp);
    if(tmp != 1)
    {
        printf("\033[1;31mFALIURE 35\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,1);
    l.add(2);
    l.add(3);
    eANDs(l.isEmpty(),l.size(),false,3);
    int *tmp1 = l.get(0);
    if(tmp1 == nullptr)
    {
        printf("\033[1;31mFALIURE 44\033[0m\n");
    }
    else
    {
        printf("getting 0: %d\n",*tmp1);
        if(*tmp1 != 1)
        {
            printf("\033[1;31mFALIURE 51\033[0m\n");
        }
    }
    eANDs(l.isEmpty(),l.size(),false,3);
    tmp1 = l.get(0);
    if(tmp1 == nullptr)
    {
        printf("\033[1;31mFALIURE 58\033[0m\n");
    }
    else
    {
        printf("getting 0: %d\n",*tmp1);
        if(*tmp1 != 1)
        {
            printf("\033[1;31mFALIURE 65\033[0m\n");
        }
    }
    tmp1 = l.get(1);
    if(tmp1 == nullptr)
    {
        printf("\033[1;31mFALIURE 71\033[0m\n");
    }
    else
    {
        printf("getting 1: %d\n",*tmp1);
        if(*tmp1 != 2)
        {
            printf("\033[1;31mFALIURE 78\033[0m\n");
        }
    }
    tmp1 = l.get(2);
    if(tmp1 == nullptr)
    {
        printf("\033[1;31mFALIURE 84\033[0m\n");
    }
    else
    {
        printf("getting 2: %d\n",*tmp1);
        if(*tmp1 != 3)
        {
            printf("\033[1;31mFALIURE 91\033[0m\n");
        }
    }
    printf("checking out of bounds getting:\n");
    tmp1 = l.get(100);
    if(tmp1 != nullptr)
    {
        printf("\033[1;31mFALIURE 98\033[0m\n");
    }
    tmp1 = l.get(-100);
    if(tmp1 != nullptr)
    {
        printf("\033[1;31mFALIURE 103\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,3);

    //getting and basic adding works! (as do size and empty)

    //list: 1,2,3

    tmp = l.add(0,8);
    printf("adding at 0: %d\n",tmp);
    if(tmp != 1)
    {
        printf("\033[1;31mFALIURE 115\033[0m\n");
    }
    if(*l.get(0) != 8)
    {
        printf("\033[1;31mFALIURE 119\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,4);
    printf("list: %d,%d,%d,%d\n",*l.get(0),*l.get(1),*l.get(2),*l.get(3));

    //8,1,2,3
    tmp = l.add(2,9);
    printf("adding at 2: %d\n",tmp);
    if(tmp != 1)
    {
        printf("\033[1;31mFALIURE 129\033[0m\n");
    }
    if(*l.get(2) != 9)
    {
        printf("\033[1;31mFALIURE 133\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,5);
    printf("list: %d,%d,%d,%d,%d\n",*l.get(0),*l.get(1),*l.get(2),*l.get(3),*l.get(4));

    //8,1,9,2,3
    tmp = l.add(5,11);
    printf("adding at 5: %d\n",tmp);
    if(tmp != 1)
    {
        printf("\033[1;31mFALIURE 143\033[0m\n");
    }
    if(*l.get(2) != 9)
    {
        printf("\033[1;31mFALIURE 147\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,6);
    printf("list: %d,%d,%d,%d,%d,%d\n",*l.get(0),*l.get(1),*l.get(2),*l.get(3),*l.get(4),*l.get(5));


    //8,1,9,2,3
    tmp = l.add(100,11);
    printf("adding at 100: %d\n",tmp);
    if(tmp != -1)
    {
        printf("\033[1;31mFALIURE 158\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,6);
    printf("list: %d,%d,%d,%d,%d,%d\n",*l.get(0),*l.get(1),*l.get(2),*l.get(3),*l.get(4),*l.get(5));

    //8,1,9,2,3
    tmp = l.add(-100,11);
    printf("adding at -100: %d\n",tmp);
    if(tmp != -1)
    {
        printf("\033[1;31mFALIURE 168\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,6);
    printf("list: %d,%d,%d,%d,%d,%d\n",*l.get(0),*l.get(1),*l.get(2),*l.get(3),*l.get(4),*l.get(5));

    printf("clear:\n");
    l.clear();
    eANDs(l.isEmpty(),l.size(),true,0);

    printf("add with resize:\n");
    for(int i = 0; i<10; i++)
    {
        l.add(i);
    }
    tmp = l.add(10);
    printf("adding one more: %d\n",tmp);
    if(tmp != 1)
    {
        printf("\033[1;31mFALIURE 186\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,11);
    if(*l.get(10) != 10)
    {
        printf("\033[1;31mFALIURE 191\033[0m\n");
    }
    for(int i = 11; i<20; i++)
    {
        l.add(i);
    }
    eANDs(l.isEmpty(),l.size(),false,20);
    printf("list: %d",*l.get(0));
    for(int i = 1; i<l.size();i++)
    {
        printf(",%d",*l.get(i));
    }
    printf("\n");
    tmp = l.add(20);
    printf("adding one more: %d\n",tmp);
    if(tmp != -1)
    {
        printf("\033[1;31mFALIURE 208\033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,20);
    if(l.get(21) != nullptr)
    {
        printf("\033[1;31mFALIURE 213\033[0m\n");
    }

    printf("list: %d",*l.get(0));
    for(int i = 1; i<l.size();i++)
    {
        printf(",%d",*l.get(i));
    }
    printf("\n");
    l.clear();
    eANDs(l.isEmpty(),l.size(),true,0);
    printf("remove:\n");
    l.add(0);
    l.add(1);
    l.add(2);
    //0,1,2
    tmp = l.remove(0);
    {
        printf("remove: %d\n",tmp);
        if(tmp != 0)
        {
            printf("\033[1;31mFALIURE 239\033[0m\n");
        }
    }
    eANDs(l.isEmpty(),l.size(),false,2);
    if(*l.get(0) != 1)
    {
        printf("\033[1;31mFALIURE 245\033[0m\n");
    }

    tmp = l.remove(1);
    if(tmp == NULL)
    {
        printf("\033[1;31mFALIURE 251 \033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 2)
        {
            printf("\033[1;31mFALIURE 258 \033[0m\n");
        }
    }
    eANDs(l.isEmpty(),l.size(),false,1);
    if(*l.get(0) != 1)
    {
        printf("\033[1;31mFALIURE 264 \033[0m\n");
    }

    tmp = l.remove(0);
    if(tmp == NULL)
    {
        printf("\033[1;31mFALIURE 270 \033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 1)
        {
            printf("\033[1;31mFALIURE 277 \033[0m\n");
        }
    }
    eANDs(l.isEmpty(),l.size(),true,0);

    l.add(90);
    l.add(80);
    l.add(70);
    eANDs(l.isEmpty(),l.size(),false,3);

    tmp = l.remove(1);
    if(tmp == NULL)
    {
        printf("\033[1;31mFALIURE 290 \033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 80)
        {
            printf("\033[1;31mFALIURE 297 \033[0m\n");
        }
    }
    if(*l.get(0) != 90 || *l.get(1) != 70)
    {
        printf("\033[1;31mFALIURE 302 \033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,2);

    printf("testing out of bounds removes:\n");
    tmp = l.remove(100);
    if(tmp != NULL)
    {
        printf("\033[1;31mFALIURE 310 \033[0m\n");
    }
    tmp = l.remove(-100);
    if(tmp != NULL)
    {
        printf("\033[1;31mFALIURE 315 \033[0m\n");
    }
}

void w_Test::testString()
{
    printf("TESTING STRING:\n");
    printf("------\n------\n");
    w_List<char> l;
    l.add('c');
    l.add('a');
    l.add('t');
    printf("from list:\n");
    w_String s(l);
    int tmp = s.size();
    printf("string: ");
    s.printString();
    printf("\n");
    printf("size: %d\n",tmp);
    if(tmp != 3)
    {
        printf("\033[1;31mFALIURE 329 \033[0m\n");
    }
    if(s.isEmpty())
    {
        printf("\033[1;31mFALIURE (EMPTY) 334 \033[0m\n");
    }
    else
    {
        printf("Is not empty\n");
    }


    char tmp1 = s.charAt(0);
    if(tmp1 != 'c')
    {
        printf("\033[1;31mFALIURE 345 \033[0m\n");
    }
    printf("%c",tmp1);
    tmp1 = s.charAt(1);
    if(tmp1 != 'a')
    {
        printf("\033[1;31mFALIURE 351 \033[0m\n");
    }
    printf("%c",tmp1);
    tmp1 = s.charAt(2);
    if(tmp1 != 't')
    {
        printf("\033[1;31mFALIURE 357 \033[0m\n");
    }
    printf("%c\n",tmp1);

    printf("appends: \n");
    s.append('s');
    tmp1 = s.charAt(3);
    for(int i = 0; i<4; i++)
    {
        printf("%c",s.charAt(i));
    }
    printf("\n");
    if(tmp1 != 's')
    {
        printf("\033[1;31mFALIURE 371 \033[0m\n");
    }
    tmp1 = s.charAt(3);
    if(tmp1 != 's')
    {
        printf("\033[1;31mFALIURE 376 \033[0m\n");
    }
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 4)
    {
        printf("\033[1;31mFALIURE 382 \033[0m\n");
    }

    printf("get out of bounds: \n");
    tmp1 = s.charAt(100);
    if(tmp1 != NULL)
    {
        printf("\033[1;31mFALIURE 389 \033[0m\n");
    }
    tmp1 = s.charAt(-100);
    if(tmp1 != NULL)
    {
        printf("\033[1;31mFALIURE 394 \033[0m\n");
    }
    printf("end out of bounds\n");

    printf("add at: ");
    bool tmp2 = s.addAt('i',0);
    if(!tmp2)
    {
        printf("\033[1;31mFALIURE 402 \033[0m\n");
    }
    s.printString();
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 5)
    {
        printf("\033[1;31mFALIURE 412 \033[0m\n");
    }
    if(s.charAt(0) != 'i')
    {
        printf("\033[1;31mFALIURE 416 -> %c \033[0m\n",s.charAt(0));
    }
    tmp2 = s.addAt('j',1);
    if(!tmp2)
    {
        printf("\033[1;31mFALIURE 421 \033[0m\n");
    }
    s.printString();
    if(s.charAt(1) != 'j')
    {
        printf("\033[1;31mFALIURE 426 -> %c \033[0m\n",s.charAt(1));
    }
    tmp2 = s.addAt('l',s.size());
    if(!tmp2)
    {
        printf("\033[1;31mFALIURE 431 \033[0m\n");
    }
    s.printString();
    if(s.charAt(s.size()-1) != 'l')
    {
        printf("\033[1;31mFALIURE 436 -> %c \033[0m\n",s.charAt(1));
    }
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 7)
    {
        printf("\033[1;31mFALIURE 441 \033[0m\n");
    }
    printf("adding at invalid location:\n");
    tmp2 = s.addAt('q', 100);
    if(tmp2)
    {
        printf("\033[1;31mFALIURE 447 \033[0m\n");
    }
    tmp2 = s.addAt('q', -100);
    if(tmp2)
    {
        printf("\033[1;31mFALIURE 447 \033[0m\n");
    }
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 7)
    {
        printf("\033[1;31mFALIURE 441 \033[0m\n");
    }

    printf("testing set:\n");
    w_List<char> l2;
    l2.add('f');
    l2.add('r');
    l2.add('o');
    l2.add('g');
    s.set(l2);
    tmp1 = s.charAt(0);
    if(tmp1 != 'f')
    {
        printf("\033[1;31mFALIURE 472 \033[0m\n");
    }
    printf("%c",tmp1);
    tmp1 = s.charAt(1);
    if(tmp1 != 'r')
    {
        printf("\033[1;31mFALIURE 478 \033[0m\n");
    }
    printf("%c",tmp1);
    tmp1 = s.charAt(2);
    if(tmp1 != 'o')
    {
        printf("\033[1;31mFALIURE 484 \033[0m\n");
    }
    printf("%c",tmp1);
    tmp1 = s.charAt(3);
    if(tmp1 != 'g')
    {
        printf("\033[1;31mFALIURE 490 \033[0m\n");
    }
    printf("%c\n",tmp1);
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 4)
    {
        printf("\033[1;31mFALIURE 497 \033[0m\n");
    }
    tmp1 = s.isEmpty();
    if(tmp1)
    {
        printf("\033[1;31mFALIURE (empty) 502 \033[0m\n");
    }

    l2.clear();
    printf("size: %d\n",tmp);
    if(tmp != 4)
    {
        printf("\033[1;31mFALIURE 509 \033[0m\n");
    }
    tmp1 = s.isEmpty();
    if(tmp1)
    {
        printf("\033[1;31mFALIURE (empty) 514 \033[0m\n");
    }

    s.set(l2);
    tmp = s.size();
    printf("size: %d\n",tmp);
    if(tmp != 0)
    {
        printf("\033[1;31mFALIURE 509 \033[0m\n");
    }
    tmp1 = s.isEmpty();
    if(!tmp1)
    {
        printf("\033[1;31mFALIURE (empty) 514 \033[0m\n");
    }

    printf("---------\nsetting with array:\n");
    w_String s2("ears",4);
    s2.printString();
    if(s2.charAt(0) != 'e' || s2.charAt(1) != 'a' || s2.charAt(2) != 'r' || s2.charAt(3) != 's' || s2.charAt(4) != NULL)
    {
        printf("\033[1;31mFALIURE 534 \033[0m\n");
    }
    tmp = s2.size();
    printf(" size: %d\n",tmp);
    if(tmp != 4)
    {
        printf("\033[1;31mFALIURE 541 \033[0m\n");
    }
    tmp1 = s2.isEmpty();
    if(tmp1)
    {
        printf("\033[1;31mFALIURE (empty) 546 \033[0m\n");
    }

    printf("again:\n");
    char ctmp[5] = {'r','o','c','k','s'};
    w_String s3(ctmp,5);
    s3.printString();
    if(s3.charAt(0) != 'r' || s3.charAt(1) != 'o' || s3.charAt(2) != 'c' || s3.charAt(3) != 'k' || s3.charAt(4) != 's'|| s3.charAt(5) != NULL)
    {
        printf("\033[1;31mFALIURE 555 \033[0m\n");
    }
    tmp = s3.size();
    printf("size: %d\n",tmp);
    if(tmp != 5)
    {
        printf("\033[1;31mFALIURE 561 \033[0m\n");
    }
    tmp1 = s3.isEmpty();
    if(tmp1)
    {
        printf("\033[1;31mFALIURE (empty) 566 \033[0m\n");
    }

    printf("---------\noperators:\n");
    char ctmp1[3] = {'a','b','c'};
    char ctmp2[3] = {'a','b','c'};
    w_String s4(ctmp1, 3);
    w_String s5(ctmp2, 3);
    s4.printString();
    printf(" == ");
    s5.printString();
    printf("\n");
    if(!(s4<=s5))
    {
        printf("\033[1;31mFALIURE 581 \033[0m\n");
    }
    if(!(s4==s5))
    {
        printf("\033[1;31mFALIURE 585 \033[0m\n");
    }
    if( s4 < s5 )
    {
        printf("\033[1;31mFALIURE 589 \033[0m\n");
    }
    if( s4>s5 )
    {
        printf("\033[1;31mFALIURE 593 \033[0m\n");
    }
    if(!(s4>=s5))
    {
        printf("\033[1;31mFALIURE 597 \033[0m\n");
    }
    if(s4!=s5)
    {
        printf("\033[1;31mFALIURE 601 \033[0m\n");
    }

    s4.append('d');
    s4.printString();
    printf(" != ");
    s5.printString();
    printf("\n");
    if(s4==s5 || s4 < s5 || !(s4>s5) || s4<=s5 || !(s4>=s5) || !(s4!=s5))
    {
        printf("\033[1;31mFALIURE 611 \033[0m\n");
    }

    s5.append('e');
    s4.printString();
    printf(" != ");
    s5.printString();
    printf("\n");
    if(s4==s5 || !(s4 < s5) ||s4>s5 || !(s4<=s5) || s4>=s5 || !(s4!=s5))
    {
        printf("\033[1;31mFALIURE 621 \033[0m\n");
    }

    s5.addAt('q',0);
    s4.printString();
    printf(" < ");
    s5.printString();
    printf("\n");
    if(s4==s5 || !(s4 < s5) || s4>s5 || !(s4<=s5) || s4>=s5 || !(s4!=s5))
    {
        printf("\033[1;31mFALIURE 631 \033[0m\n");
    }



}
