#ifndef STACK_H
#define STACK_H

#include "Object.h"

namespace DTLib
{

template<typename T>
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0;  //入栈
    virtual void pop() = 0;             //出栈
    virtual T top() const = 0;          //栈顶top值
    virtual void clear() = 0;           //清空栈
    virtual int size() const = 0;       //取出栈的大小
};

}

#endif // STACK_H
