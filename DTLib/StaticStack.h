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
    T m_space[N];   //������ʱ������N�η�ָ���͵Ĺ��캯����ʹ��������ʱ��Ӱ��Ч�ʡ� ����ʹ��LinkStack�ֲ�������ȱ��
    int m_top;      //��ʶ����m_top
    int m_size;     //��ʾջ������Ԫ�صĸ���
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity()  //����ջ��ǰ�Ĵ洢�����Ĵ�С
    {
        return N;
    }

    void push(const T& e)   //ѹջ������������ѹ��ջ��
    {
        if(m_size < N)
        {
            m_space[m_top+1] = e;   //e����Ϊ�����ͣ������׳��쳣��Ϊ���쳣��ȫ�����Ƚ�e��ֵ��m_space[m_top+1].
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()          //��ջ
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
