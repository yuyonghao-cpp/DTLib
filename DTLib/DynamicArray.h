/*  DynamicArray 二维数组使用
int main()
{
    DynamicArray< DynamicArray<int> > d;

    d.resize(3);

    for(int i=0; i<d.length(); i++)
    {
        //d[i].resize(3);
        d[i].resize(i+1);
    }

    for(int i=0; i<d.length(); i++)
    {
        for(int j=0; j<d[i].length(); j++)
        {
            d[i][j] = i * j;
        }
    }

    for(int i=0; i<d.length(); i++)
    {
        for(int j=0; j<d[i].length(); j++)
        {
            cout << d[i][j] << " ";
        }
         cout << endl;
    }

    return 0;
}
*/

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template
<typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* arry, int len, int newlen)
    {
        T* ret = new T[newlen];

        if(ret)
        {
            int size = (len < newlen ? len : newlen);

            for(int i=0; i<size; i++)
            {
                ret[i] = arry[i];
            }
        }

        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;
            //为了异常安全
            // temp局部的指针，指向当前成员指针m_array所指向的堆空间
            this->m_array = array;
            this->m_length = length;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object...");
        }
    }

    void init(T* array, int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray object...");
        }
    }
public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {

        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length)
    {
        if(length != m_length)
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICARRAY_H
