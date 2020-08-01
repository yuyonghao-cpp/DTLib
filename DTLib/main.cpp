#include <iostream>
#include <cstring>
#include <cstdlib>
#include "DTString.h"

using namespace std;
using namespace DTLib;

int* make_pmt(const char* p)    //建立一个部分匹配表，返回值为部分匹配表
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int) * len));

    if(ret != NULL)
    {
        int ll = 0; //前缀后缀中交集元素的最大长度
        ret[0] = 0;

        for(int i=1; i<len; i++)
        {
            while((ll>0) && (p[ll] != p[i]))
            {
                ll = ret[ll - 1];
            }

            if(p[ll] == p[i])
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int main()
{
    const int& j = 1;
    int& k = const_cast<int&>(j);

    const int x = 2;
    int& y = const_cast<int&>(x);

    //int z = const_cast<int>(x);

    k = 5;

    printf("k = %d\n", k);
    printf("j = %d\n", j);

    y = 8;

    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("&x = %p\n", &x);
    printf("&y = %p\n", &y);

