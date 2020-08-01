#ifndef STACK_H
#define STACK_H

#include "Object.h"

namespace DTLib
{

template<typename T>
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0;  //��ջ
    virtual void pop() = 0;             //��ջ
    virtual T top() const = 0;          //ջ��topֵ
    virtual void clear() = 0;           //���ջ
    virtual int size() const = 0;       //ȡ��ջ�Ĵ�С
};

}

#endif // STACK_H
