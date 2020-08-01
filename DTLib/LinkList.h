/*  find函数，以及==符号的重载
class Test : public Object
{
    int i;
public:
    Test(int v = 0)
    {
        i = v;
    }
    bool operator == (const Test& e)
    {
        return (i == e.i);
    }
};
int main()
{
    Test t1(1);
    Test t2(2);
    Test t3(3);

    LinkList<Test> list;

    list.insert(t1);
    list.insert(t2);
    list.insert(t3);

    cout << list.find(t1) << endl;

    return 0;
}

//线性时间完成遍历
int main()
{
    LinkList<int> list;

    for(int i=0; i<1; i++)
    {
        list.insert(0, i);
    }

    for(list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }

    return 0;
}
*/


#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template< typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    /*mutable struct : public Object  // 防止客户使用会抛出异常的类,防止泛型类型T构造函数的调用。
    {
        char reserved[sizeof(T)];
        Node* next;
    } m_header;
*/
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    } m_header;

    //mutable Node m_header;
    int m_length;
    int m_step;  //保存游标每次移动节点的数目
    Node* m_current;    //游标

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(const T& e) //从线性表尾部插入一个元素
    {
        return insert(m_length, e);
    }

//        0. 将header->next = NULL
//        1. 堆空间申请一个Node空间，Node* node = new Node()
//        2. 声明一个current指针指向m_header的地址，Node* current = &m_header
//                                                    此时current->next与m_header.next都为NULL。
//        3.  第一次for循环 p和i都为0时，不执行for循环语句
//            {
//                将current->next的地址赋值给current，current = current->next
//            }
//        4. 设置node的值value，node->value = e
//        5. 将current->next赋值给node->next，node->next = current->next
//        6. 再将node赋值给current->next， current->next = node


    bool insert(int i, const T& e)
    {
        bool ret = ( (0 <= i)&&(i<= m_length) );

        if(ret)
        {
            Node* node = create();

            if(node != NULL)
            {
                Node* current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
            }
        }

        return ret;
    }
    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            Node* current = position(i);

            Node* toDel = current->next;

            if( m_current == toDel )
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;

            m_length--;

            destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            e = position(i)->next->value;
        }

        return ret;
    }

    virtual T get(int i) const
    {
        T ret;

        if(get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalied parameter i to get element...");
        }

        return ret;

    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        Node* node = m_header.next;  //node初始的时候就是指向单链表的第0号位置处的数据元素

        while( node)
        {
            if( node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;

    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while( m_header.next)
        {
            Node* toDel = m_header.next;

            m_header.next =toDel->next;

            m_length--;

            destroy(toDel);
        }

        m_length = 0;
    }

    //i为目标位置，step为游标移动节点的数目。将游标定位到目标位置
    virtual bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    //判断是否到达尾部
    virtual bool end()
    {
        return (m_current == NULL);
    }

    //获取游标所指向的数据元素
    virtual T current()
    {
        if( !end() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    virtual bool next()
    {
        int i = 0;

        while( (i < m_step) && !end() )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    ~LinkList()
    {
        clear();
    }
};

}

#endif // LINKLIST_H



