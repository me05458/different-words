#ifndef w_LIST_H
#define w_LIST_H
#include <cstddef>
#include <cstdlib>

template <typename T> //it's a template
class w_List { //array list, specifically
public:
    w_List(int arraySize = 10, int maxSize=1000); //constructor (with default parameters)
    //arraySize is size of starting array, maxSize is how big it can get (all in elements)
    w_List(const w_List<T> &list); //overloaded constructor to make a new list out of another one
    ~w_List(); //destructor
    int add(int spot, T item); //add an item into spot spot
    int add(T item); //add an item to end (overloaded)
    bool remove(int spot); //get rid of the item at spot (returns true if succeeded, false otherwise)
    T* get(int spot) const; //get the address of the item at a spot
    bool isEmpty() const; //is it empty?
    int size() const; //amount of items in list
    void clear(); //get rid of everything in list (important: sets size to 0, does not wipe elements as security is not a pirpority for vocabular storage)
    void sort(); //sort from smallest to biggest
    w_List<T>& operator=(const w_List<T> &list); //set the list equal to another list

protected:
    int m_arrSize; //current size of internal array
    int m_maxSize; //maximum size of internal array
    int m_addSize; //amount to increase array size on resize

private:
    T *m_arr; //array itself
    int m_size; //amount of elements
    int resize(); //helper to make bigger array when this one gets too small
};

template <typename T>
w_List<T>::w_List(const w_List<T> &list)
{
    m_arrSize = list.m_arrSize; //set all of these protected variables equal
    m_addSize = list.m_addSize;
    m_maxSize = list.m_maxSize;
    m_arr = new T[m_arrSize]; //make a new array of same size as list's array was
    m_size = list.size(); //set size to list's size
    for(int i = 0; i<m_size; i++) //run through size and populate new array with list's items
    {
        m_arr[i] = *list.get(i);
    }
}

template <typename T>
w_List<T>::w_List(int arraySize, int maxSize)
{
    m_addSize = arraySize; //set from parameters
    m_arrSize = arraySize; //starts out at initial array size
    m_maxSize = maxSize; //set from parameters
    m_size = 0; //initially nothing in it
    m_arr = new T[arraySize]; //allocate the array
}
template <typename T>
w_List<T>::~w_List()
{
    delete m_arr; //deallocate the array
}
template <typename T>
int w_List<T>::resize() //change to a bigger array
{
    if(m_arrSize+m_addSize <= m_maxSize) //only if the new array will not be over the size limit
    {
        m_arrSize += m_addSize; //change array size
        T *a = new T[m_arrSize]; //allocate a new array
        if(a == nullptr) //this means that there wasn't enough memory to allocate
        { //return exit code 2
            return 2;
        }
        for(int i = 0; i<m_size; i++) //run through this new array and populate from old array
        {
            a[i] = m_arr[i];
        }
        delete m_arr; //get rid of old array (avoid memory leaks)
        m_arr = a; //set instance variable to new array
        return 0; //all good! return
    }
    else //array cannot resize, return exit code 1
    {
        return 1;
    }
}

template <typename T>
w_List<T>& w_List<T>::operator=(const w_List<T> &list) //equate arrays
{
    delete m_arr; //get rid of internal array
    m_arrSize = list.m_arrSize; //equate protected variables
    m_maxSize = list.m_maxSize;
    m_addSize = list.m_addSize;
    m_arr = new T[m_arrSize]; //make a new array of size of list's array
    m_size = list.size(); //update size
    for(int i = 0; i<m_size; i++) //populate new array from list's array
    {
        m_arr[i] = *list.get(i);
    }
    return *this; //return a pointer to this, modified, element
}

template <typename T>
int w_List<T>::add(int spot, T item) //add a new item
{
    if(spot < 0 || spot > m_size) //invalid spot
    {
        return -1;
    }
    m_size++; //one more item has been added, thus increment
    if(m_size > m_arrSize) //this would make the array bigger than current array
    {
        int a = resize(); //resize
        if(a == 1|| a==2) //if resize had an exit code
        {
            m_size --; //keep size what it was originally and return
            return -1;
        }
    }
    T tmp = m_arr[spot]; //this stores the element originally at spot for a bit
    T tmp2; //this will be used to store elements as they get swapped
    m_arr[spot] = item; //set the element at spot to the new one
    for(int i = spot+1; i<m_size; i++) //from the next spot to the end...
    {
        tmp2 = m_arr[i]; //keep track of current contents of that spot
        m_arr[i] = tmp; //write it to the contents of the last spot
        tmp = tmp2; //old contents of current spot are now contents of last spot when for loop keeps going

    }
    return 1; //success
}
template <typename T>
int w_List<T>::add(T item)
{
    return add(m_size, item); //call other add, but just to the end
}
template <typename T>
bool w_List<T>::remove(int spot) //get rid of an item
{
    if(spot >= m_size || spot<0) //bad stot, cannot remove
    {
        return false;
    }
    for(int i = spot; i<m_size; i++) //starting at the spot
    {
        m_arr[i] = m_arr[i+1]; //make the array at that spot the one at the next spot (move them all over one)
    }
    m_size--;
    return true; //succeeded

}

template <typename T>
void w_List<T>::sort() //a bubble sort
{
    if(this->size()<2) // list is 0 or 1 long, and therefore sorted
    {
        return;
    }
    bool sorted = false; //keep going until this ends up true
    T tmp = 0; //this is used to hohld elements when they're being swapped
    while(!sorted) //as long as it's not sorted
    {
        sorted = true; //start off as sorted for each new run
        for(int i = 0; i<this->size()-1; i++) //go through entire array
        {
            if(m_arr[i] < m_arr[i+1]) //if the current element and the next one around of order, swap them
            {
                tmp = m_arr[i];
                m_arr[i] = m_arr[i+1];
                m_arr[i+1] = tmp;
                sorted = false; //a swap means the list was not sorted on this run
            }

        }
    }
    //list is now sorted
}

template <typename T>
T* w_List<T>::get (int spot) const //get the contents of a spot
{
    if(spot >= m_size || spot<0) //invalid spot
    {
        return nullptr;
    }
    return &m_arr[spot]; //return its address
}
template <typename T>
int w_List<T>::size () const
{
    return m_size; //just returns size
}
template <typename T>
bool w_List<T>::isEmpty () const
{
    return m_size==0; //just returns if it's empty
}
template <typename T>
void w_List<T>::clear()
{
    m_size =0; //clears the size to 0
}
#endif
