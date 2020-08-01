/*
int main()
{

    SharedPointer<Test> sp0 = new Test();
    SharedPointer<Test> sp1 = sp0;
    SharedPointer<Test> sp2;
    SharedPointer<Test> sp3 = new Test();

    sp2 = sp0;

    sp2->value = 100;
    cout << sp0->value << endl;
    cout << sp1->value << endl;
    cout << sp2->value << endl;

    cout << sp0.get() << endl;
    cout << sp1.get() << endl;
    cout << sp2.get() << endl;

    cout << sp3.get() << endl;

    sp2.clear();
    cout << (sp0 == sp2) << endl;


    return 0;
}
*/

#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Exception.h"
#include "Pointer.h"

namespace DTLib
{

template < typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;
    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if( this->m_ref)
        {
            *(this->m_ref)++;
        }
    }
public:
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
            if( this->m_ref)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if( this != &obj )
        {
            clear();
            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if(ref)
        {
            (*ref)--;
            if( *ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }
};

template < typename T >
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template < typename T >
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l.get() == r.get());
}

}

#endif // SHAREDPOINTER_H
