/* DynamicList ���Ҫ��

  -��ģ��

  . ���������ѿռ���Ϊ˳��洢�ռ�

  . ��̬����˳��洢�ռ�Ĵ�С

  . ��֤��ֵ˳��洢�ռ�ʱ���쳣��ȫ��
  -�����쳣��ȫ�ĸ���
    . ��й¶�κ���Դ
    . �������ƻ�����
  -�����쳣��ȫ�Ļ�����֤
    . ����쳣���׳�
        )�����ڵ��κγ�Ա��Ȼ�ܱ�����Ч״̬
        )û�����ݵ��ƻ�����Դй©
*/

#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib
{
/*
  *���������ռ���Ϊ˳��洢�ռ�

  *��̬����˳��洢�ռ�Ĵ�С

  *��֤����˳��洢�ռ�ʱ���쳣��ȫ��

    -�����쳣��ȫ�ĸ���
        ��й¶�κ���Դ
        �������ƻ�����
    -�����쳣��ȫ�Ļ�����֤
        ����쳣���׳��������ڵ��κγ�Ա��Ȼ�ܱ�����Ч״̬
        û�����ݵ��ƻ��Լ���Դй¶
*/
template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;  //˳��洢�ռ�Ĵ�С
public:
    DynamicList(int capacity) // ����ռ�
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

    //��������˳��洢�ռ�Ĵ�С
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

    ~DynamicList()  //�黹�ռ�
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICLIST_H
