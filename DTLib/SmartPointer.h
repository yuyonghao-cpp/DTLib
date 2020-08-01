/*
    ����ָ����ģ�壬
*/

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"
namespace DTLib
{

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {

    }

    //�������캯����
    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = 0;
    }

    //��ֵ���������أ�
    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if( this != &obj )  //�ж��Ƿ�Ϊ�Ը�ֵ
        {
            T* p = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = 0;

            delete p;

        }

            return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
