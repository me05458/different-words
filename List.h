template <typename T>
class List { //array list, specifically
public:
    List(int arraySize = 10, int maxSize=1000);
    ~List();
    int add(T item, int spot);
    int add(T item);
    T remove(int spot);
    T get(int spot);
    bool isEmpty();
    int size();
    void clear();

private:
    T *m_arr;
    int m_size;
    int m_arrSize;
    int m_maxSize;
    void resize();
};
