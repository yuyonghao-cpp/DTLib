/*
    智能指针类模板，
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

    //拷贝构造函数，
    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = 0;
    }

    //赋值操作符重载，
    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if( this != &obj )  //判断是否为自赋值
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
