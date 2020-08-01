#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line)
{
    /*
        strdup是先调用malloc动态为一个未初始化的指针分配内存，然后再用strcpy将字符串复制进这个指针中（malloc+strcpy）

        strcpy是将一个字符串放进已经分配内存的指针中

        strdup要进行free。strcpy不需要进行free
    */
    m_message = ( message ? strdup(message) : NULL);  //拷贝字符串，复制到堆空间；
    if( file != NULL )
    {
        /*
            itoa()函数有3个参数：第一个参数是要转换的数字，第二个参数是要写入转换结果的目标字符串，
            第三个参数是转移数字时所用 的基数。在上例中，转换基数为10。10：十进制；2：二进制...
        */
        char sl[16] = {0};
        itoa(line, sl, 10);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));

        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file , line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file ,line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator = (const Exception& e)
{
    if( this != &e )
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}
