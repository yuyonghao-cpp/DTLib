/* 链式栈
#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int i;
    Test(int v = 0)
    {
        i = v;
        //cout << "Test()" << endl;
    }

    bool operator == (const Test& e)
    {
        return (i == e.i);
    }

    int getI()
    {
        return i;
    }

    ~Test()
    {
        //cout << "~Test()" << endl;
    }
};

int main()
{
    LinkStack<Test> stack;

    Test t0(0);
    Test t1(1);
    Test t2(2);
    Test t3(3);
    Test t4(4);

    cout << "before push: " << stack.size() << endl;

    stack.push(t0);
    stack.push(t1);
    stack.push(t2);
    stack.push(t3);
    stack.push(t4);

    cout << "after push: " << stack.size() << endl;

    while(stack.size() > 0)
    {
        cout << stack.top().i << endl;
        stack.pop();
    }

    cout << "after pop: " << stack.size() << endl;

    return 0;
}
*/
////////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace DTLib;

bool is_left(char c)
{
    return (c == '(' || (c == '{') || (c == '[') || (c == '<'));
}

bool is_right(char c)
{
    return (c == ')' || (c == '}') || (c == '[') || (c == '>'));
}

bool is_quot(char c)
{
    return ((c == '\'') || (c == '\"'));
}

bool is_match(char l, char r)
{
    return  ((l == '(') && (r == ')'))||
            ((l == '{') && (r == '}'))||
            ((l == '[') && (r == ']'))||
            ((l == '<') && (r == '>'))||
            ((l == '\'') && (r == '\''))||
            ((l == '\"') && (r == '\"'));
}

bool scan(const char* code)
{
    LinkStack<char> stack;
    int i = 0;
    bool ret = true;

    code = (code == NULL) ? "" : code;

    while(ret && (code[i] != '\0'))
    {
        if(is_left(code[i]))
        {
            stack.push(code[i]);
        }
        else if(is_right(code[i]))
        {
            if((stack.size() > 0) && is_match(stack.top(), code[i]))
            {
                stack.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if( is_quot(code[i]))
        {
            if( (stack.size() == 0) || !is_match(stack.top(), code[i]) )
            {
                stack.push(code[i]);
            }
            else if( is_match(stack.top(), code[i]))
            {
                stack.pop();
            }
        }

        i++;
    }

    return ret && (stack.size() == 0);
}

int main()
{
    cout << scan("<a{\'\'\"\"bc}d>") << endl;

    return 0;
}
*/
#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"
#include "Exception.h"

namespace DTLib
{

template<typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    void push(const T& e)       //入栈
    {
        m_list.insert(0, e);
    }

    void pop()                  //出栈
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const      //栈顶top值
    {
        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()       //清空栈
    {
        m_list.clear();
    }

    int size() const   //取出栈的大小
    {
        return m_list.length();
    }
};

}

#endif // LINKSTACK_H
