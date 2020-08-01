/* DynamicList 设计要点

  -类模板

  . 申请连续堆空间作为顺序存储空间

  . 动态设置顺序存储空间的大小

  . 保证充值顺序存储空间时的异常安全性
  -函数异常安全的概念
    . 不泄露任何资源
    . 不允许破坏数据
  -函数异常安全的基本保证
    . 如果异常被抛出
        )对象内的任何成员仍然能保持有效状态
        )没有数据的破坏及资源泄漏
*/

#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib
{
/*
  *申请连续空间作为顺序存储空间

  *动态设置顺序存储空间的大小

  *保证重置顺序存储空间时的异常安全性

    -函数异常安全的概念
        不泄露任何资源
        不允许破坏数据
    -函数异常安全的基本保证
        如果异常被抛出，对象内的任何成员仍然能保持有效状态
        没有数据的破坏以及资源泄露
*/
template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;  //顺序存储空间的大小
public:
    DynamicList(int capacity) // 申请空间
    {
        this->m_array = new T(capacity);

        if( this->m_array != NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
           THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicList object");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    //重新设置顺序存储空间的大小
    void resize(int capacity)
    {
        if( capacity != m_capacity)
        {
            T* array = new T[capacity];

            if(array != NULL)
            {
                int length = (this->m_length < capacity ? this->m_length : capacity);
                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicList object");
            }
        }
    }

    ~DynamicList()  //归还空间
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICLIST_H
