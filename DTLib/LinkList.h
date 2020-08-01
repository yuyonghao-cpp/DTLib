/*  find�������Լ�==���ŵ�����
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

//����ʱ����ɱ���
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

    /*mutable struct : public Object  // ��ֹ�ͻ�ʹ�û��׳��쳣����,��ֹ��������T���캯���ĵ��á�
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
    int m_step;  //�����α�ÿ���ƶ��ڵ����Ŀ
    Node* m_current;    //�α�

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

    bool insert(const T& e) //�����Ա�β������һ��Ԫ��
    {
        return insert(m_length, e);
    }

//        0. ��header->next = NULL
//        1. �ѿռ�����һ��Node�ռ䣬Node* node = new Node()
//        2. ����һ��currentָ��ָ��m_header�ĵ�ַ��Node* current = &m_header
//                                                    ��ʱcurrent->next��m_header.next��ΪNULL��
//        3.  ��һ��forѭ�� p��i��Ϊ0ʱ����ִ��forѭ�����
//            {
//                ��current->next�ĵ�ַ��ֵ��current��current = current->next
//            }
//        4. ����node��ֵvalue��node->value = e
//        5. ��current->next��ֵ��node->next��node->next = current->next
//        6. �ٽ�node��ֵ��current->next�� current->next = node


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
        Node* node = m_header.next;  //node��ʼ��ʱ�����ָ������ĵ�0��λ�ô�������Ԫ��

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

    //iΪĿ��λ�ã�stepΪ�α��ƶ��ڵ����Ŀ�����α궨λ��Ŀ��λ��
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

    //�ж��Ƿ񵽴�β��
    virtual bool end()
    {
        return (m_current == NULL);
    }

    //��ȡ�α���ָ�������Ԫ��
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



