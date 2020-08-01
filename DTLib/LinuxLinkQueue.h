/*使用Linux内核双向循环链表实现高效率的链式队列
  效率： LinuxLinkQueue > LinkuQueue


#include <iostream>
#include "LinuxLinkQueue.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
    int i;
public:
    Test(int e = 0)
    {
       // cout << "Test()" << endl;

        i = e;
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

    LinuxLinkQueue<Test> queue;

    Test t0(0);
    Test t1(1);
    Test t2(2);
    Test t3(3);
    Test t4(4);

    queue.add(t0);
    queue.add(t1);
    queue.add(t2);
    queue.add(t3);
    queue.add(t4);

    while(queue.length() > 0)
    {
        cout << queue.front().getI() << endl;

        queue.remove();
    }

    return 0;
}

*/

#ifndef LINUXLINKQUEUE_H
#define LINUXLINKQUEUE_H

#include "Object.h"
#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinuxLinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
      list_head head;
      T value;
    };

    list_head m_header;
    int m_length;
public:
    LinuxLinkQueue()       //初始化成员变量
    {
        m_length = 0;

        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& e)    //O(1)
    {
        Node* node = new Node();

        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head, &m_header);
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No memory to add element ...");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            list_head* toDel = m_header.next;

            list_del(toDel);

            m_length--;

            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const
    {
        if(m_length > 0)
        {
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove();
        }
    }

    int length() const
    {
        return m_length;
    }

    ~LinuxLinkQueue()
    {
        clear();
    }
};

}


#endif // LINUXLINKQUEUE_H
