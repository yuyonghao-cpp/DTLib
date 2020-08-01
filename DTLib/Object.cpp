#include "object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DTLib
{

void* Object::operator new (unsigned int size) throw()//��֤����ռ�ʧ�ܺ󷵻�һ����ֵ��������һ���쳣��
{
    //cout << "void* Object::operator new" << endl;
    return malloc(size);
}

void Object::operator delete (void* p)
{
    //cout << "void Object::operator delete " << endl;
    free(p);
}

void* Object::operator new[] (unsigned int size) throw()//��֤����ռ�ʧ�ܺ󷵻�һ����ֵ��������һ���쳣��
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{

}

}
