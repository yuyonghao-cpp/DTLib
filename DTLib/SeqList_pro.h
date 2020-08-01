#ifndef SEQLIST_H
#define SEQLIST_H
#include "List.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class SeqList : public List<T>
{
protected:
    T* m_array; //˳��洢�ռ�
    int m_length;   //��ǰ���Ա���
public:
    bool insert(int i, const T& e);
    bool remove(int i);
    bool set(int i, const T& e);
    bool get(int i, T& e) const;
    int length() const;
    void clear();
    //˳��洢���Ա��������ʷ�ʽ
    T& operator [] (int i);
    T operator [] (int i) const;
    //˳��洢�ռ������
    virtual int capacity() const = 0;
};
template < typename T >
bool SeqList<T>::insert(int i, const T& e)
{
    bool ret = ( (0<=i)&&(i<=m_length) );

    ret = ret && (m_length < capacity());

    if(ret)
    {
        for(int p=m_length-1; p>=i; p--)
        {
            m_array[p+1] = m_array[p];
        }

        m_array[i] = e;

        m_length++;
    }
    return ret;
}
template < typename T >
bool SeqList<T>::remove(int i)
{
    bool ret = ( (0<=i) && (i<m_length) );

    if(ret)
    {
        for(int p=i; p<m_length; p++)
        {
            m_array[p] = m_array[p+1];
        }

        m_length--;
    }

    return ret;
}
template < typename T >
bool SeqList<T>::set(int i, const T& e)
{
    bool ret = ( (0<=i)&&(i<m_length) );

    if(ret)
    {
        m_array[i] = e;
    }

    return ret;
}
template < typename T >
bool SeqList<T>::get(int i, T& e) const
{
    bool ret = ( (0<=i)&&(i<m_length) );

    if(ret)
    {
        e = m_array[i];
    }

    return ret;
}
template < typename T >
int SeqList<T>::length() const
{
    return m_length;

}
template < typename T >
void SeqList<T>::clear()
{
    m_length = 0;
}

//˳��洢���Ա��������ʷ�ʽ
template < typename T >
T& SeqList<T>::operator [] (int i)
{
    if( (0<=i)&&(i<m_length) )
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid");
    }
}
template < typename T >
T SeqList<T>::operator [] (int i) const
{
    return (const_cast<SeqList<T>&>(*this))[i];
}

//˳��洢�ռ������
template < typename T >
int SeqList<T>::capacity() const = 0;

}

#endif // SEQLIST_H
