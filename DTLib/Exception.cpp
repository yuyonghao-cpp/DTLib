#include "Exception.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line)
{
    /*
        strdup���ȵ���malloc��̬Ϊһ��δ��ʼ����ָ������ڴ棬Ȼ������strcpy���ַ������ƽ����ָ���У�malloc+strcpy��

        strcpy�ǽ�һ���ַ����Ž��Ѿ������ڴ��ָ����

        strdupҪ����free��strcpy����Ҫ����free
    */
    m_message = ( message ? strdup(message) : NULL);  //�����ַ��������Ƶ��ѿռ䣻
    if( file != NULL )
    {
        /*
            itoa()������3����������һ��������Ҫת�������֣��ڶ���������Ҫд��ת�������Ŀ���ַ�����
            ������������ת������ʱ���� �Ļ������������У�ת������Ϊ10��10��ʮ���ƣ�2��������...
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
