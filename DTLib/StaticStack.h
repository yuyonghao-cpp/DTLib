/*
#include <iostream>
#include "StaticStack.h"

using namespace std;
using namespace DTLib;

int main()
{
    StaticStack<int, 5> stack;

    for(int i=0; i<5; i++)
    {
        stack.push(i);
    }

    cout << stack.size() << endl;

    while(stack.size() > 0)
    {
        cout << stack.top() << endl;
        stack.pop();
    }
    cout << stack.size() << endl;

    return 0;
}
*/
#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template<typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];   //创建的时候会调用N次泛指类型的构造函数，使用类类型时会影响效率。 可以使用LinkStack弥补这样的缺陷
    int m_top;      //标识变量m_top
    int m_size;     //表示栈中数据元素的个数
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity()  //返回栈当前的存储容量的大小
    {
        return N;
    }

    void push(const T& e)   //压栈操作，将数据压入栈中
    {
        if(m_size < N)
        {
            m_space[m_top+1] = e;   //e可能为类类型，可能抛出异常，为了异常安全，首先将e赋值给m_space[m_top+1].
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()          //出栈
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
           return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }
};

}

#endif // STATICSTACK_H
