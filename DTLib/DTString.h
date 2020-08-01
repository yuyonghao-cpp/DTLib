#ifndef DTSTRING_H
#define DTSTRING_H
#include "Object.h"

namespace DTLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void  init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    String& inset(int i, const char* s);
    String& inset(int i, const String& s);

    String& trim();

    bool operator == (const String& s) const;
    bool operator == (const char* s) const; //必须兼容字符串对象与C语言里面char*指针所自带的字符串之间的互操作

    bool operator != (const String& s) const;
    bool operator != (const char* s) const;

    bool operator > (const String& s) const;
    bool operator > (const char* s) const;

    bool operator < (const String& s) const;
    bool operator < (const char* s) const;

    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;

    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String operator += (const String& s);
    String operator += (const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    char& operator [] (int i);
    char operator [] (int i) const;

    ~String();
};

}

#endif // DTSTRING_H
