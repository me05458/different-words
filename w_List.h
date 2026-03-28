#ifndef w_LIST_H
#define w_LIST_H
#include <cstddef>
#include <cstdlib>

template <typename T>
class w_List { //array list, specifically
public:
    w_List(int arraySize = 10, int maxSize=1000);
    w_List(const w_List<T> &list);
    ~w_List();
    int add(int spot, T item);
    int add(T item);
    bool remove(int spot);
    T* get(int spot) const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void sort();
    w_List<T>& operator=(const w_List<T> &list);

protected:
    int m_arrSize;
    int m_maxSize;
    int m_addSize;

private:
    T *m_arr;
    int m_size;
    int resize();
};

template <typename T>
w_List<T>::w_List(const w_List<T> &list)
{
    m_arrSize = list.m_arrSize;
    m_addSize = list.m_addSize;
    m_maxSize = list.m_maxSize;
    m_arr = new T[m_arrSize];
    m_size = list.size();
    for(int i = 0; i<m_size; i++)
    {
        m_arr[i] = *list.get(i);
    }
}

template <typename T>
w_List<T>::w_List(int arraySize, int maxSize)
{
    m_addSize = arraySize;
    m_arrSize = arraySize;
    m_maxSize = maxSize;
    m_size = 0;
    m_arr = new T[arraySize];
}
template <typename T>
w_List<T>::~w_List()
{
    delete m_arr;
}
template <typename T>
int w_List<T>::resize()
{
    if(m_arrSize+m_addSize <= m_maxSize)
    {
        m_arrSize += m_addSize;
        T *a = new T[m_arrSize];
        if(a == nullptr)
        {
            return 2;
        }
        for(int i = 0; i<m_size; i++)
        {
            a[i] = m_arr[i];
        }
        delete m_arr;
        m_arr = a;
        return 0;
    }
    else
    {
        return 1;
    }
}

template <typename T>
w_List<T>& w_List<T>::operator=(const w_List<T> &list)
{
    delete m_arr;
    m_arrSize = list.m_arrSize;
    m_maxSize = list.m_maxSize;
    m_addSize = list.m_addSize;
    m_arr = new T[m_arrSize];
    m_size = list.size();
    for(int i = 0; i<m_size; i++)
    {
        m_arr[i] = *list.get(i);
    }
    return *this;
}

template <typename T>
int w_List<T>::add(int spot, T item)
{
    if(spot < 0 || spot > m_size)
    {
        return -1;
    }
    m_size++;
    if(m_size > m_arrSize)
    {
        int a = resize();
        if(a == 1|| a==2)
        {
            m_size --;
            return -1;
        }
    }
    T tmp = m_arr[spot];
    T tmp2;
    m_arr[spot] = item;
    for(int i = spot+1; i<m_size; i++)
    {
        tmp2 = m_arr[i];
        m_arr[i] = tmp;
        tmp = tmp2;

    }
    return 1;
}
template <typename T>
int w_List<T>::add(T item)
{
    return add(m_size, item);
}
template <typename T>
bool w_List<T>::remove(int spot)
{
    if(spot >= m_size || spot<0)
    {
        return false;
    }
   // T result = m_arr[spot];
    for(int i = spot; i<m_size; i++)
    {
        m_arr[i] = m_arr[i+1];
    }
    m_size--;
    return true;

}

template <typename T>
void w_List<T>::sort()
{
    if(this->size()<2)
    {
        return;
    }
    bool sorted = false;
    int tmp = 0;
    while(!sorted)
    {
        sorted = true;
        for(int i = 0; i<this->size()-1; i++)
        {
            if(m_arr[i] < m_arr[i+1])
            {
                tmp = m_arr[i];
                m_arr[i] = m_arr[i+1];
                m_arr[i+1] = tmp;
                sorted = false;
            }

        }
    }
}

template <typename T>
T* w_List<T>::get (int spot) const
{
    if(spot >= m_size || spot<0)
    {
        return nullptr;
    }
    return &m_arr[spot];
}
template <typename T>
int w_List<T>::size () const
{
    return m_size;
}
template <typename T>
bool w_List<T>::isEmpty () const
{
    return m_size==0;
}
template <typename T>
void w_List<T>::clear()
{
    m_size =0;
}
#endif
