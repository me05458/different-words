#include <iostream>
#include "w_String.h"
#include <cstddef>

using namespace std;

void eANDs(bool empty, int size, bool want_empty, int want_size)
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

int main() {
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
    if(tmp1 == NULL)
    {
        printf("\033[1;31mFALIURE 232\033[0m\n");
    }
    else
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

    tmp = l.remove(2);
    if(tmp == NULL)
    {
        printf("\033[1;31mFALIURE 251 033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 2)
        {
            printf("\033[1;31mFALIURE 258 033[0m\n");
        }
    }
    eANDs(l.isEmpty(),l.size(),false,1);
    if(*l.get(0) != 1)
    {
        printf("\033[1;31mFALIURE 264 033[0m\n");
    }

    tmp = l.remove(0);
    if(tmp == NULL)
    {
        printf("\033[1;31mFALIURE 270 033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 1)
        {
            printf("\033[1;31mFALIURE 277 033[0m\n");
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
        printf("\033[1;31mFALIURE 290 033[0m\n");
    }
    else
    {
        printf("remove: %d\n",tmp);
        if(tmp != 80)
        {
            printf("\033[1;31mFALIURE 297 033[0m\n");
        }
    }
    if(*l.get(0) != 90 || *l.get(1) != 70)
    {
        printf("\033[1;31mFALIURE 302 033[0m\n");
    }
    eANDs(l.isEmpty(),l.size(),false,2);

    printf("testing out of bounds removes:\n");
    tmp = l.remove(100);
    if(tmp != NULL)
    {
        printf("\033[1;31mFALIURE 310 033[0m\n");
    }
    tmp = l.remove(-100);
    if(tmp != NULL)
    {
        printf("\033[1;31mFALIURE 315 033[0m\n");
    }





    return 0;
}
