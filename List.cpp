#include "List.h"

template <typename T>
List<T>::List(int m_arraySize, int maxSize)
{
    m_arrSize = m_arraySize;
    m_maxSize = maxSize;
    m_arr = new T[m_arrSize];
}
template <typename T>
List<T>::~List()
{
    delete m_arr;
}
template <typename T>
void List<T>::resize()
{
    m_arrSize += 10;
    T a = new T[m_arrSize];
    for(int i = 0; i<size; i++)
    {
        a[i] = m_arr[i];
    }
    delete m_arr;
    m_arr = a;
}
template <typename T>
int List<T>::add(T item, int spot)
{
    if(spot < 0 || spot > m_size)
    {
        return -1;
    }
    m_size++;
    if(m_size == m_arrSize)
    {
        resize();
    }
    int tmp = m_arr[spot];
    int tmp2 = 0;
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
int List<T>::add(T item)
{
    return add(item, m_size);
}
template <typename T>
T List<T>::remove(int spot)
{
    if(spot >= m_size || spot<0)
    {
        return nullptr;
    }
    T result = m_arr[spot];
    for(int i = spot; i<m_size; i++)
    {
        m_arr[i] = m_arr[i+1];
    }
    m_size--;

}
template <typename T>
T List<T>::get (int spot)
{
    if(spot >= m_size || spot<0)
    {
        return nullptr;
    }
    return m_arr[spot];
}
template <typename T>
int List<T>::size ()
{
    return m_size;
}
template <typename T>
bool List<T>::isEmpty ()
{
    return m_size==0;
}
template <typename T>
void List<T>::clear()
{
    size =0;
}
